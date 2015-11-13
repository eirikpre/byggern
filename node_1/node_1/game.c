#include "joystick.h"
#include "can_com.h"
#include "game.h"
#include "ADC.h"
#include <stdio.h>

can_message_t joystick_msg = {'j',2,"00000000"};
can_message_t shot_msg = {'s',1};

void check_and_report_shot( void );

int play_game( void )
{
	int score = 0;
	can_message_t message;
	joy_position_t joystick;
	
	
	while(1)
	{
		//Joystick
		joystick =  get_position();
		joystick_msg.data[0] = joystick.x_pos;
		joystick_msg.data[1] = joystick.y_pos;
		can_message_send(&joystick_msg);
			
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
		if (ADC_read(2) > 100)
		{
			break;
		}
			
		
	}
	
	return score;
}


		
void check_and_report_shot( void )
{
	
	static int recent_shot = 0;
	static int recent_shot_counter = 0;
	
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
		recent_shot_counter += 1;
		if (recent_shot_counter > 1000/40)
		{
			recent_shot_counter = 0;
			if (ADC_read(3) < 100){
				recent_shot = 0;
			}
		}
	}
}