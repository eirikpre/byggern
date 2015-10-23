#include "ADC.h"
#include <avr/io.h>

void init_ADC(){
	ADMUX  |= (1 <<REFS0);
	ADMUX &= 0xe0;
	ADCSRA |= (1 << ADEN);
	//ADCH //lese fra
	//ADCL //lese fra
}

char ADC_read2(){
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC) == (1 << ADSC)) {
		//Delay?
	}
	return ADCL;
}

