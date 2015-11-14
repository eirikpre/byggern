#include "ADC.h"
#include <avr/io.h>

void init_ADC(){
	DDRF &= ~(1 << PF0);

	ADCSRA |= (1 << ADEN) | (1 << ADATE)  | (1 << ADSC) | (1 << ADPS2) |(1 << ADIE)| (1 << ADPS1) | (1 << ADPS0);
	ADMUX  |= (1 <<REFS0) | (1 <<ADLAR);
}

char ADC_read( void ){
	int mean = 0; int i = 0;
	int nsamples = 4;
	for (i = 0; i <nsamples; i++){
		mean = mean + ADCH;
	}
	mean = mean/nsamples;
	return mean;
}

