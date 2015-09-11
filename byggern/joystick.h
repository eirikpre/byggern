
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

typedef enum{
	LEFT = 0,
	RIGTH = 1,
	UP = 2,
	DOWN = 3,
	NEUTRAL = 4
} Direction;

typedef struct{
	int x_pos;
	int y_pos;
}joy_position_t;


void joy_init();

joy_position_t get_position();

void get_direction();


#endif