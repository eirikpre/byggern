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

	can_message_t msg;

	
	//menu_init();
	
	while(1){
			if(can_get_message(&msg)==1){
				can_print(msg);
			}
			
			
			_delay_ms(40);

		
		
		
		
		//printf("X:%4d       ", ADC_read(1));
		//printf("Y:%4d \n", ADC_read(0)); 
		//printf("Touch:       Left: %4d           Right:%4d\n", ADC_read(3),ADC_read(2));
		//_delay_ms(400);
		//joy_position_t test;
		//test =  get_position();
		//printf("x_pos:%d         y_pos:%d\n",test.x_pos,test.y_pos);
		
	}
}

void can_print(can_message_t msg)
{
	printf("ID: %d ,Length: %d, ",msg.id,msg.length);
	int i ;
	for (i=0; i<8;i++)
	{
		printf("%c", msg.data[i]);
	}
	printf("\n");
}