#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"


char ADC_read(int channel)
{
	*ADC_START = 0x04 + channel;
	_delay_us(40);
	return *ADC_START;
}

