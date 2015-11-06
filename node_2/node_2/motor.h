#include <avr/io.h>
#include <stdio.h>
#include "i2c.h"


void motor_drive( char joystick_x );
void motor_init ( void );
uint16_t encoder_read( void );
