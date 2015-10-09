#define F_OSC 16000000
#define F_CPU F_OSC

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>

#include "can_com.h"
#include "MCP2515.h"
#include "spi_control.h"


int main ()
{
can_init();
mcp2515_bit_modify(MCP_CANCTRL, 0xE0 , MODE_NORMAL);
/*	
	mcp2515_bit_modify(MCP_CANCTRL, 0xE0 , MODE_LOOPBACK);
	can_message_t msg1 = {'f', 0x8, "hallo123"};
	can_message_t msg2;
	
	can_message_send(&msg1);
	_delay_ms(40);
	can_message_receive(&msg2);
*/
	DDRB = 0xff;

		PORTB |= (1 << PB7);
		can_message_t msg1 = {0xdf, 0x8, "00000000"};
		can_message_send(&msg1);
		msg1.data[0] = 'Ø';
		msg1.data[7]+= 1;
		can_message_send(&msg1);
	

}
