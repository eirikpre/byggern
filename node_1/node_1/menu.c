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
menu_t menu;



void menu_init(){
	
	menu_t sub3sub1 = {"Calibrate",0,NULL,NULL,{}};
	
	menu_t sub1 = {"Play game",0,NULL,NULL,{}};
	menu_t sub2 = {"Highscores",0,NULL,NULL,{}};
	menu_t sub3 = {"Settings",1,NULL,NULL, {&sub3sub1}	};
	menu_t sub4 = {"Debug",0,NULL ,NULL,{}};
	
	
	menu_t main_menu = {"Main Menu",4,NULL,NULL,{&sub1,&sub2,&sub3,&sub4}};
	sub1.parent =&main_menu;	
	sub2.parent =&main_menu;
	sub3.parent =&main_menu;
	sub3sub1.parent= &sub3;
	
	menu = main_menu;
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
	can_message_t message = {'j',8,"joystick"};
	//can_message_send(&message);
	
	while(1)
	{
		menu_handler(&curr_dir, &last_dir);
		
		/*        TESTING     */
		joystick = get_position();
		message.data[0] = joystick.x_pos;
		message.data[1] = joystick.y_pos;
		//can_message_send(&message);
		can_message_receive(&message, 8);
		can_print(&message);
		
		
		
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
