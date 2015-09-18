#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "oled.h"
#include "oled_font.h"
void oled_print_char(char* input);
void oled_print_char(char* input){
	int i;
	for(i = 0; i<4 ;i++)
	{
		write_d(pgm_read_byte(&font[*input - ' '][i]));
	}
}

void oled_print(char* input){
	int i=0;
	
	while(input[i] != '\0'){
			oled_print_char(&input[i]);
			i++;
			
	}
}

void write_c(unsigned char out_data)
{
	*OLED_START_C = out_data;
}

void write_d(unsigned char out_data)
{
	*OLED_START_D = out_data;
}

void oled_init()
{
	write_c(0xae);    // display off
	write_c(0xa1);    //segment remap
	write_c(0xda);    //common pads hardware: alternative
	write_c(0x12);
	write_c(0xc8);    //common output scan direction:com63~com0
	write_c(0xa8);    //multiplex ration mode:63
	write_c(0x3f);
	write_c(0xd5);    //display divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81);    //contrast control
	write_c(0x50);
	write_c(0xd9);    //set pre-charge period
	write_c(0x21);
	write_c(0x20);    //Set Memory Addressing Mode
	write_c(0x00);
	write_c(0xdb);    //VCOM deselect level mode
	write_c(0x30);
	write_c(0xad);    //master configuration
	write_c(0x00);
	write_c(0xa4);    //out follows RAM content
	write_c(0xa6);    //set normal display
	write_c(0xaf);    // display on
}

void oled_goto(char page, char column ){
	write_c(0x21);
	write_c(column);
	write_c(0x7F);
	
	write_c(0x22);
	write_c(page);
	write_c(0x07);
}

void oled_clear_page(char page){

	oled_goto(page,0);
	
	for (int i = 0; i<128; i++){
		*OLED_START_D= 0x00;
	}
}

void oled_clear_all(){
	oled_goto(0,0);
	for (int i = 0; i<1024; i++){
		*OLED_START_D= 0x00;
	}
}
