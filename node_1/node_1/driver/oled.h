#ifndef OLED_H_
#define OLED_H_

#define OLED_START_C ((volatile char*)0x1000)
#define OLED_START_D ((volatile char*)0x1200)

void oled_init();

void oled_print(char* input);				// Print a char array

void oled_goto(char page, char column );	// Set reference point where to start typing

void oled_clear_page(char page);			// Clear a line

void oled_clear_all();						// Clear the entire screen


#endif