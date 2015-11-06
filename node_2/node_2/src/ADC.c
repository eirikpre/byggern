#include "ADC.h"
#include <avr/io.h>
#include "can_com.h"


int recent_goal = 0;
int recent_goal_counter = 0;

can_message_t goal_msg = {'g',1,"aaaaaaaa"};

void init_ADC(){
	DDRF &= ~(1 << PF0);
	//ADMUX &= 0xe0;
	ADCSRA |= (1 << ADEN) | (1 << ADATE)  | (1 << ADSC) | (1 << ADPS2) |(1 << ADIE)| (1 << ADPS1) | (1 << ADPS0);
	//ADCH //lese fra
	//ADCL //lese fra
	ADMUX  |= (1 <<REFS0) | (1 <<ADLAR);
	
}

uint8_t ADC_read(){
	int mean = 0; int i = 0;
	int nsamples = 4;
	for (i = 0; i <nsamples; i++){
		mean = mean + ADCH;
	}
	mean = mean/nsamples;
	return mean;
}

void check_and_report_goal( void ){
	
	int threshold = 40;
	
	if (recent_goal == 0)
	{
		goal_msg.data[0] = ADC_read();
		
		if(goal_msg.data[0] < threshold){
			recent_goal = 1;
			can_message_send(&goal_msg);
			
			
		}

	}
	else // recent_goal == 1 
	{
		recent_goal_counter += 1;
		if (recent_goal_counter > 1000/40)
		{
			recent_goal_counter = 0;
			if (ADC_read() > threshold){
				recent_goal = 0;
			}
			
		}

	}
	
}