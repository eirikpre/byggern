#include <string.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include "game.h"
#include "joystick.h"
#include "driver/can_com.h"
#include "driver/ADC.h"
#include "driver/oled.h"

volatile int TOUCH_JOY_MODE = 0;
volatile int DIFFICULTY_MODE = 1;

can_message_t joystick_msg = {'j',2,"00000000"};
can_message_t touch_msg = {'t',1,"0000000"};
	
void check_and_report_shot( void );
void game_update_highscore( int , uint16_t* );
void game_over_screen ( char* );

void game_play( void )
{
	uint16_t highscore[3];
	int i;
	int score = 0;
	int score_sub = 0;
	char* score_print = "000000000000000";
	joy_position_t joystick;
	
	can_message_t message = {'m',1,"00"};
	
	// Get highscores
	for(i=0; i<3; i++)
	{
		highscore[i] = eeprom_read_word((uint16_t*)(i*2));
	}
	
	//Setup OLED Screen
	oled_clear_all();
	oled_goto(0,0);
	oled_print("     GAME");
	oled_goto(3,0);
	oled_print("    Score: ");
	
	// Sending game mode to node 2
	message.data[0] = TOUCH_JOY_MODE;
	can_message_send(&message);
	
	while(1)
	{
		//Read input from multifunction card
		joystick =  joy_read();
		joystick_msg.data[0] = joystick.x_pos/DIFFICULTY_MODE;
		joystick_msg.data[1] = joystick.y_pos;
		can_message_send(&joystick_msg);
		if (TOUCH_JOY_MODE == 1){
			touch_msg.data[0] = ADC_read(2);
			can_message_send(&touch_msg);	
		}
		// Check for pressed shot button
		check_and_report_shot();
		
		// Handle game over
		if (can_get_message(&message) == 1)
		{
			if(message.id == 'g') break;	// Goal
		}
		
		// Check for quit
		if ( (ADC_read(2) > 180 && TOUCH_JOY_MODE == 0) || (ADC_read(0) > 200 && TOUCH_JOY_MODE == 1) ) break;
		
		// Print Score on oled
		oled_goto(4, 0);
		sprintf(score_print,"       %d     ",score);
		oled_print(score_print);
		
		// Increment score
		if(score_sub++ > 700)
		{
			score_sub = 0;
			score++;
		}
	}
	// Stop node 2 from running
	joystick_msg.data[0] = 0;
	joystick_msg.data[1] = 0;
	can_message_send(&joystick_msg);
	if (TOUCH_JOY_MODE == 1){
		touch_msg.data[0] = 128;
		can_message_send(&touch_msg);
	}

	game_update_highscore(score,highscore);
	game_over_screen(score_print);
	return;
}
		
void check_and_report_shot( void )
{
	can_message_t shot_msg = {'s',1};
	static int recent_shot = 0;
	if (recent_shot == 0)
	{
		if(ADC_read(3) > 100) //read input from multifunction card
		{
			can_message_send(&shot_msg);
			recent_shot = 1;
		}
	}
	else
	{
		if (ADC_read(3) < 100){
			recent_shot = 0;
		}
	}
}

void game_print_highscore( void )
{
	int i;
	char* temp = "000000000000000";

	oled_clear_all();
	oled_goto(0,0);
	oled_print("Highscores");
	for (i=0; i<3 ;i++)
	{
		oled_goto(i+2,8);
		sprintf(temp,"%d. %d    ",i+1,eeprom_read_word((uint16_t*)(i*2)));
		oled_print(temp);
	}
	return;
}

void game_update_highscore( int score, uint16_t* highscore )
{
	if (score > highscore[0])
	{
		eeprom_write_word((uint16_t*)4, highscore[1]);
		eeprom_write_word((uint16_t*)2, highscore[0]);
		eeprom_write_word((uint16_t*)0, score );
	}
	else if(score > highscore[1])
	{
		eeprom_write_word((uint16_t*)4, highscore[1]);
		eeprom_write_word((uint16_t*)2, score );
	}
	else if(score > highscore[2])
	{
		eeprom_write_word((uint16_t*)4, score );
	}
}

void game_reset_highscore ( void )
{
	eeprom_write_word((uint16_t*)0, 0 );	//	Reset the highscores
	eeprom_write_word((uint16_t*)2, 0 );
	eeprom_write_word((uint16_t*)4, 0 );
}

void game_over_screen ( char* score )
{
	
	oled_clear_all();
	oled_goto(2,8);
	oled_print("GAME OVER! :-(");
	oled_goto(3,0);
	oled_print("    Score: ");
	oled_goto(4, 0);
	oled_print(score);

	while( joy_get_direction() == NEUTRAL ) ;	
	
}

void game_change_mode( int mode )
{
	TOUCH_JOY_MODE = mode;
}

void game_change_difficulty( int diff)
{
	DIFFICULTY_MODE = diff;
}