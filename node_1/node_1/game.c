#define F_CPU 4915200
#include "joystick.h"
#include "can_com.h"
#include "game.h"
#include "ADC.h"
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include "oled.h"
#include <avr/eeprom.h>

int TOUCH_JOY_MODE = 1;


can_message_t joystick_msg = {'j',2,"00000000"};
can_message_t shot_msg = {'s',1};
can_message_t touch_msg = {'t',1,"0000000"};
char highscore_print[11] = "Highscores\n"; 
	
void check_and_report_shot( void );
void update_eeprom( int score, uint16_t* highscore );

void play_game( void )
{
	uint16_t highscore[3];
	int i;
	int score = 0;
	int score_sub = 0;
	char* score_print = "0000000000";
	
	can_message_t message = {'m',1,"00"};
	joy_position_t joystick;
	
	// Get highscores
	for(i=0; i<5; i+=2)
	{
		highscore[i/2] = eeprom_read_word((uint16_t*)(i));
	}
	
	// Sending mode to node 2
	message.data[0] = TOUCH_JOY_MODE;
	can_message_send(&message);
	
	//Print Screen
	oled_clear_all();
	oled_goto(0,0);
	oled_print("     GAME");
	oled_goto(3,0);
	oled_print("    Score: ");
	
	while(1)
	{
		//Joystick
		joystick =  get_position();
		joystick_msg.data[0] = joystick.x_pos;
		joystick_msg.data[1] = joystick.y_pos;
		can_message_send(&joystick_msg);
		
		if (TOUCH_JOY_MODE == 1){
			touch_msg.data[0] = ADC_read(2);
			can_message_send(&touch_msg);	
		}
		
		// Handle potential goals
		if (can_get_message(&message) == 1)
		{
			if(message.id == 'g')	// Goal
			{
				break;
			}
		}
		
		// Check for shot button
		check_and_report_shot();
		
		// Check for quit
		if ( (ADC_read(2) > 180 && TOUCH_JOY_MODE == 0) || (ADC_read(0) > 200 && TOUCH_JOY_MODE == 1) ) break;
		
		// Print Score
		oled_goto(4, 0);
		sprintf(score_print,"       %d",score);
		oled_print(score_print);
		
		// Add score
		if(score_sub++ > 700)
		{
			score_sub = 0;
			score++;
		}
	}
	update_eeprom(score,highscore);
	return;
}


		
void check_and_report_shot( void )
{
	
	static int recent_shot = 0;
	
	if (recent_shot == 0)
	{
		if(ADC_read(3) > 100)
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

void print_highscore( void )
{

	
	int i;
	char* temp = "00000000000000000";

	oled_clear_all();
	oled_goto(0,0);
	oled_print("Highscores");
	for (i=0; i<3 ;i++)
	{
		oled_goto(i+2,8);
		sprintf(temp,"%d. %d",i+1,eeprom_read_word((uint16_t*)(i*2)));
		oled_print(temp);
	}

	
	return;
}

void update_eeprom( int score, uint16_t* highscore )
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

void reset_eeprom ( void )
{
	eeprom_write_word((uint16_t*)0, 0 );	//	Reset the highscores
	eeprom_write_word((uint16_t*)2, 0 );
	eeprom_write_word((uint16_t*)4, 0 );
}
