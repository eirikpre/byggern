#define F_CPU 4915200
#include "menu.h"
#include "oled.h"
#include "joystick.h"
#include <stdio.h>
#include "spi_control.h"
#include "util/delay.h"
#include "MCP2515.h"
#include "can_com.h"

void update_next(direction dir);
void menu_fsm();
void menu_handler(direction* curr_dir, direction* last_dir);
void menu_print(menu_t* object);

menu_t* current;
int next;
menu_t sub3sub1 = {"Calibrate",0,NULL,NULL,{}};
menu_t sub1 = {"Play game",0,NULL,NULL,{}};
menu_t sub2 = {"Highscores",0,NULL,NULL,{}};
menu_t sub3 = {"Settings",1,NULL,NULL, {&sub3sub1}	};
menu_t sub4 = {"Debug",0,NULL ,NULL,{}};
menu_t menu = {"Main Menu",4,NULL,NULL,{&sub1,&sub2,&sub3,&sub4}};

void menu_init(){

	sub3sub1.parent= &sub3;
	sub1.parent = &menu;	
	sub2.parent = &menu;
	sub3.parent = &menu;
	
	
	
	current = &menu;
	next = 1;
	
	
	menu_print(current);
	menu_fsm();
	
}


void menu_fsm(){
	direction curr_dir;
	direction last_dir = NEUTRAL;
	joy_position_t joystick;
	
	// Testing
	can_message_t joystick_msg = {'j',1,"joystick"};
	
	while(1)
	{
		// Menu
		menu_handler(&curr_dir, &last_dir);
		
		//Joystick
		joystick_msg.data[0] = get_position().x_pos;
		can_message_send(&joystick_msg);
		
		// Handle potential goals
		if (can_get_message(&message) == 1)
		{
			can_handle_message(&message);
		}
		
		/*        TESTING     */

		//message.data[1] = joystick.y_pos;
		
		
		
		
	
		
		
		_delay_ms(10);
	}
}



void menu_handler(direction* curr_dir, direction* last_dir)
{
	
	*curr_dir = get_direction();
	if (*curr_dir != *last_dir)
	{
		switch (*curr_dir){
			case RIGHT:
			//if (current->children[next]->number_children == 0){
			//current->children[next]->fnc_pointer();
			//}
			
			if (next == 3)
			{
				current = current->children[next-1];
				next = 1;
				menu_print(current);
			}

			break;
			case LEFT:
			if (current->parent != NULL){
				current = current->parent;
				next = 1;
				menu_print(current);
			}
			break;
			case UP:
			
			update_next(*curr_dir);
			break;
			case DOWN:
			
			update_next(*curr_dir);
			break;
			default:
			break;
		}
	}
	*last_dir = *curr_dir;
}


void update_next(direction dir){
	if (dir == DOWN) {
		if (next+1 <= current->number_children){
			oled_goto(next,0);
			oled_print(" ");
			next++;
			oled_goto(next,0);
			oled_print("-");
		}
		
	}
	else{
		if (next > 1){
			oled_goto(next,0);
			oled_print(" ");
			next--;
			oled_goto(next,0);
			oled_print("-");
		}
	}
}

void menu_print(menu_t* object){
	oled_clear_all();
	oled_goto(0,0);
	oled_print(object->name);
	oled_goto(next,0);
	oled_print("-");
	
	int i;
	for (i=1;i<object->number_children+1;i++)
	{
		oled_goto(i,8);
		oled_print((object->children[i-1])->name);
	}
}
