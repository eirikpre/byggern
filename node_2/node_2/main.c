#define F_OSC 16000000
#define F_CPU F_OSC

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>

#include "servo.h"
#include "can_com.h"
#include "MCP2515.h"
#include "spi_control.h"


int main (void)
{
	can_init();
	servo_init();

	float val = 950;
	
	DDRB = 0xff;
	PORTB |= (1 << PB7);
	
	can_message_t msg;
	
	while (1)
	{

		
		if (val > 2050){
			val = 950;
		}
		
		servo_write(val);
		
		_delay_ms(5);
		
		can_get_message(&msg);
		val = msg.data[0]*5 + 1500;
	}


}
