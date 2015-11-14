#define F_CPU 4915200
#include "joystick.h"
#include "can_com.h"
#include "game.h"
#include "ADC.h"
#include <stdio.h>
#include <util/delay.h>
#include "oled.h"

int TOUCH_JOY_MODE = 1;

can_message_t joystick_msg = {'j',2,"00000000"};
can_message_t shot_msg = {'s',1};
can_message_t touch_msg = {'t',1,"0000000"};
	
void check_and_report_shot( void );

int play_game( void )
{
	char score = 0;
	
	can_message_t message = {'m',1,"00"};
	joy_position_t joystick;
	
	// Sending mode to node 2
	message.data[0] = TOUCH_JOY_MODE;
	can_message_send(&message);
	
	//Print Screen
	oled_clear_all();
	oled_goto(0,0);
	oled_print("     GAME");
	oled_goto(4,0);
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
				score++;
			}
		}
		
		// Check for shot button
		check_and_report_shot();
		
		// Check for quit
		if (ADC_read(2) > 180 && TOUCH_JOY_MODE == 0)
		{
			break;
		}
		else if (ADC_read(0) > 200 && TOUCH_JOY_MODE == 1)
		{
			break;
		}
		
		// Print Score
		oled_goto(3, 0);
		oled_print(&score);
			
		
		
	}
	return score;
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