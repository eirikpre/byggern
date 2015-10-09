#define F_CPU 4915200
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC.h"
#include "USART_driver.h"

int adc_channels[2];


char ADC_read(int channel){
	
	*ADC_START = 0x04 + channel;
	_delay_us(40);
	return *ADC_START;
	 
}

