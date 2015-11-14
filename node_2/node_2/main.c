#define F_OSC 16000000
#define F_CPU F_OSC

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "servo.h"
#include "can_com.h"
#include "MCP2515.h"
#include "spi_control.h"
#include "src\ADC.h"
#include "USART_driver.h"
#include "motor.h"


void solenoid_shoot(void);
void init_solenoid(void);
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

	DDRF = 0xFF; // MJ1 output
	

	while (1)
	{

		
		
		/*    TESTING    */
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

void init_solenoid(void)
{
	DDRC |= (1 << PC0);
	PORTC |= (1 << PC0);
}

void solenoid_shoot(void)
{
	PORTC &= ~(1 << PC0);
	_delay_ms(75);
	PORTC |= (1 << PC0);
}