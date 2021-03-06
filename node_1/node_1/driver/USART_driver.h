#ifndef DRIVER 
#define DRIVER

#define BAUD 9600
#define FOSC 4915200
#define MYUBRR FOSC/16/BAUD-1

void USART_init(unsigned int ubrr);

int USART_transmit(unsigned char data);

unsigned char USART_receive (void);

#endif