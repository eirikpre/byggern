#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "solenoid.h"

void init_solenoid(void)
{
	DDRC |= (1 << PC0);
	PORTC |= (1 << PC0);
}

void solenoid_shoot(void)
{
	PORTC &= ~(1 << PC0);
	_delay_ms(75);
	PORTC |= (1 << PC0);
}