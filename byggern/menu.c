#define F_CPU 4915200
#include "menu.h"
#include "oled.h"
#include "joystick.h"
#include <stdio.h>
#include "spi_control.h"
#include "util/delay.h"
#include "can_control.h"
#include "MCP2515.h"


void update_next(direction dir);
void menu_fsm();
void menu_handler(direction* curr_dir, direction* last_dir);


menu_t* current;
int next;
menu_t menu;


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
	while(1){
		menu_handler(&curr_dir, &last_dir);
		
		
		can_reset(); //inti
		//can_bit_modify(MCP_CANCTRL,0x70,MODE_LOOPBACK);
		//can_write(0x0a,'A');
		_delay_ms(50);
		printf("%d\n",can_read(MCP_CANSTAT));
		
		
		
	}
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
				current = menu.children[next-1];
				
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