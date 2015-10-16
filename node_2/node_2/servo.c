#include "servo.h"
#include <avr/io.h>

#define F_CPU 16000000 
#define PRESCALED_CLK F_CPU/8
#define TOP_VALUE PRESCALED_CLK/50

int us_to_compare(float us);

void servo_init(void)
{

	// Fast PWM mode		
	TCCR1A |=  (1 << WGM11); 
	TCCR1B |=  (1 << WGM13) | (1 << WGM12);	
	
	
	// Prescale
	TCCR1B |= (1 << CS11);
	TCCR1B &= ~(1 << CS12) & ~(1 << CS10);	
	
	// Clear OC2A on compare match, set OC2A at BOTTOM			
	TCCR1A |= (1 << COM1A1);
	TCCR1A &= ~(1 << COM1A0);
	// TOP Value
	ICR1 = TOP_VALUE;
	
	// Compare register
	OCR1A = us_to_compare(900);
	
	// Enable output
	DDRB |= (1 << PB6);
	
}

int us_to_compare(float us)
{
	return ( (us / 20000.0 ) * TOP_VALUE );
}




void servo_write(float val)
{
	if(val > 950.0 && val < 2050.0)
	{
		OCR1A = us_to_compare(val);
	}
	
}




