#define F_CPU 4915200
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "USART_driver.h"



int main(void)
{	
	USART_init(MYUBRR);
	
	DDRA = 0x51;
	_delay_ms(2000);
    while(1)
    {
		PORTA = PORTA ^ 0x01;
		
		_delay_ms(1000);
		//USART_transmit(USART_receive());
		printf("hLLO");
		
    }
}
