#define F_CPU 4915200
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "USART_driver.h"
#include "ADC.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "spi_control.h"
#include "can_com.h"
#include "MCP2515.h"


int main(void)
{

	USART_init(MYUBRR);
	// Activate external memory
	MCUCR |= (1 << SRE);
	
		
	joy_init();
	
	oled_init();


	

	
	
	can_init();
	mcp2515_bit_modify(MCP_CANCTRL, 0xE0 , MODE_LOOPBACK);
	can_message_t msg1 = {'f', 0x8, "hallo123"}; 
	can_message_t msg2;
	
	can_message_send(&msg1);
	_delay_ms(40);
	can_message_receive(&msg2);
	printf("ID: %d ,Length: %d, ",msg2.id,msg2.length);
	int i ;
	for (i=0; i<8;i++)
	{
		printf("%c", msg2.data[i]);
	}
	printf("\n");
	
	
	menu_init();
	
	while(1){
		
		
		
		
		
		
		
		//printf("X:%4d       ", ADC_read(1));
		//printf("Y:%4d \n", ADC_read(0)); 
		//printf("Touch:       Left: %4d           Right:%4d\n", ADC_read(3),ADC_read(2));
		//_delay_ms(400);
		//joy_position_t test;
		//test =  get_position();
		//printf("x_pos:%d         y_pos:%d\n",test.x_pos,test.y_pos);
		
	}
}
