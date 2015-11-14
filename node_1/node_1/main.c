#define F_CPU 4915200
#include <util/delay.h>
#include <avr/io.h>
#include "driver/USART_driver.h"
#include "driver/oled.h"
#include "menu.h"
#include "can_com.h"
#include "joystick.h"

int main(void)
{	
	// Activate external memory
	MCUCR |= (1 << SRE);
		
	// Initialize	
	USART_init(MYUBRR);
	joy_init();
	oled_init();
	can_init();
	menu_init();
	
	// Starts the FSM
	while(1)
	{
		menu_fsm();
		_delay_ms(20);
	}	
}
