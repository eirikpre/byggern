#include "USART_driver.h"

void USART_init(unsigned int ubrr){

	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char) ubrr;	
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	
	fdevopen(USART_transmit,USART_receive);
}

void USART_transmit(unsigned char data){
	
	while(!(UCSR0A & (1<<UDRE0)))
		;
	UDR0 = data;
	
}

unsigned char USART_receive (void){
	
	while( !(UCSR0A & (1<<RXC0)))
		;
	return UDR0;
	
}