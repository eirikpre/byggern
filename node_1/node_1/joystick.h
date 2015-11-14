
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

typedef enum{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL
} direction;

typedef struct{
	int x_pos;
	int y_pos;
}joy_position_t;



void joy_init();

joy_position_t get_position();
direction get_direction();
void joy_calibrate();

#endif