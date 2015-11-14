#include "joystick.h"
#include "driver/ADC.h"

char x_ref = 0;
char y_ref = 0;

void joy_init(){
	joy_calibrate();
}

joy_position_t joy_read(){
	joy_position_t position;
	position.x_pos = (ADC_read(1) - x_ref)*100/128;
	position.y_pos = (ADC_read(0) - y_ref)*100/128;
	return position;
}

direction joy_get_direction(){
	joy_position_t position = joy_read();
	
	if (position.x_pos > 70)		return RIGHT;
	else if (position.x_pos < -70)	return LEFT;
	else if (position.y_pos > 70)	return UP;
	else if (position.y_pos < -70)	return DOWN;
	else							return NEUTRAL;
}

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
}
