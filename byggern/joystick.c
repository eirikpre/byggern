#define F_CPU 4915200
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC.h"
#include "USART_driver.h"
#include "joystick.h"


char x_ref = 0;
char y_ref = 0;



void joy_calibrate(){
	int sum_x=0;
	int sum_y=0;
	int i;
	for(i=0;i<10;i++){
		sum_x += ADC_read(1);
		sum_y += ADC_read(0);
	}
	x_ref = sum_x/10;
	y_ref = sum_y/10;
	
	
	printf("Calibration finished with values:\nX:%d    Y:%d\n",x_ref,y_ref);
}

void joy_init(){
	joy_calibrate();
	
}

joy_position_t get_position(){
	joy_position_t position;
	position.x_pos = (ADC_read(1) - x_ref)*100/128;
	position.y_pos = (ADC_read(0) - y_ref)*100/128;
	return position;
}


direction get_direction(){
	
	joy_position_t position = get_position();
	
	if (position.x_pos > 70)
		{

			return RIGHT;
		}
	else if (position.x_pos < -70)
		{

			return LEFT;
		}
	else if (position.y_pos > 70)
		{

			return UP;
		}
	else if (position.y_pos < -70)
		{

			return DOWN;
		}
	else
		{

			return NEUTRAL;
		}
	
}
