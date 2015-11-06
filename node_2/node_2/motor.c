#include <stdlib.h>
#include <avr/io.h>
#define F_OSC 16000000
#define F_CPU F_OSC
#include <util/delay.h>
#include "motor.h"


char motor_speed;

void motor_init(void)
{
	
	i2c_init();
	DDRF = 0xff;
	DDRK = 0x00;
	
	PORTF |= (1 << PF4); // Enable motor
	
	//Move to known reference point
	motor_drive(-50);
	_delay_ms(700);
	motor_drive(0);
	
	//Toggle reset encoder
	PORTF &= ~(1 << PF6);
	_delay_us(5);
	PORTF |= (1 << PF6);
	
	

}

uint16_t encoder_read( void )
{
	int output ;
	PORTF &= ~(1 << PF7); // !OE = 0
	PORTF &= ~(1 << PF5); // SET = 0 // For MSB
	_delay_us(20);
	output = PINK;
	output = (output << 8);
	PORTF |= (1 << PF5);	//SET = 1 // For LSB
	_delay_us(20); 
	output |= PINK;
	
	
	PORTF |= (1 << PF7); // !OE = 1
	
	return output;
}


void motor_drive( char joystick_x )
{
	
	
	
	// Set direction
	if(joystick_x < 0){
		PORTF &= ~(1 << PF3);
	}
	else{
		PORTF |= (1 << PF3);
	}
	
	// Set speed
	motor_speed = (char)((abs((float)joystick_x)*255)/100);
	i2c_transmit(0x50, &motor_speed,1);
}

