#include <avr/io.h>
#include <string.h>
#include <stdio.h>

#include "driver/can_com.h"
#include "driver/servo.h"
#include "driver/spi_control.h"
#include "driver/ADC.h"
#include "driver/USART_driver.h"
#include "driver/motor.h"
#include "driver/solenoid.h"
#include "goal.h"


can_message_t message;

void handle_message(can_message_t* message);

int main (void)
{
	can_init();
	servo_init();
	init_ADC();
	USART_init(MYUBRR);
	motor_init();
	init_solenoid();

	

	while (1)
	{
		if (can_get_message(&message) == 1)
		{
			handle_message(&message);
		}
		check_and_report_goal();
	}
}

 
void handle_message(can_message_t* message)
{
	static int TOUCH_JOY_MODE = 0;
	switch (message->id)
	{
		case 'p' :				// Print
			can_print(message);
			break;
		case 'j' :
			if(TOUCH_JOY_MODE == 0){
				servo_write( message->data[1] * 5.0 + 1450 );	//	Y - value
				motor_drive( message->data[0] );
			}
			else
			{
				servo_write( - message->data[0] * 5.0 + 1450 );	//	X - value
			}
			break;
		case 's' :
			solenoid_shoot();
			break;
		case 't' :	
			position_controller( -message->data[0] );				//	X - value
			break;
			
		case 'm' : 
			TOUCH_JOY_MODE = message->data[0];
			// Reset motor when new game with touch-slider
			motor_init();
			break;
			
		default:
			can_print(message);
			break;
	}
}

