#ifndef DRIVER 
#define DRIVER

#include <avr/io.h>

#define BAUD 9600
#define FOSC 16000000
#define MYUBRR FOSC/16/BAUD-1

void USART_init(unsigned int ubrr);

void USART_transmit(unsigned char data);

unsigned char USART_receive (void);

#endif