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

		
		_delay_ms(20);
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
	switch (message->id)
	{
		case 'p' :				// Print
			can_print(message);
			break;
		case 'j' :
			motor_drive( message->data[0] );				//	X - value
			servo_write( message->data[1] * 5.0 + 1450 );	//	Y - value
			break;
		case 's' :
			solenoid_shoot();
			
		
		default:
			can_print(message);
			break;
	}
}

void init_solenoid(void)
{
	DDRB |= (1 << PB4);
	PORTB |= (1 << PB4);
}

void solenoid_shoot(void)
{
	PORTB &= ~(1 << PB4);
	_delay_ms(75);
	PORTB |= (1 << PB4);
}