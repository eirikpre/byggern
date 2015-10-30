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
#include "TWI_Master.h"





int main (void)
{
	can_init();
	servo_init();
	init_ADC();
	
	TWSR |= 0x02; // Prescaling TWI clock
	TWI_Master_Initialise();
	sei();
	
	DDRB = 0xff;
	PORTB |= (1 << PB7); // LED
	
	unsigned char test[3] = {0x50,0x00,100};

	

	while (1)
	{
		
		/*    TESTING    */

		check_and_report_goal();
		TWI_Start_Transceiver_With_Data(test,3);

		_delay_ms(10);
		
		/*
		if (val > 2050){
			val = 950;
		}
		
		servo_write(val);
		
		_delay_ms(5);
		
		can_get_message(&msg);
		val = msg.data[0]*5 + 1500;
		*/
	}
	

}
