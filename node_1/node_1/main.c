#define F_CPU 4915200
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "USART_driver.h"
#include "ADC.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "spi_control.h"
#include "can_com.h"
#include "MCP2515.h"


int main(void)
{

	USART_init(MYUBRR);
	// Activate external memory
	MCUCR |= (1 << SRE);
		
	// Initialize	
	joy_init();
	oled_init();
	can_init();

	// Starts the FSM
	menu_init();
	
}
