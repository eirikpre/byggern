#define F_CPU 4915200
#include <avr/io.h>
#include "USART_driver.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "can_com.h"


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
	}	
}
