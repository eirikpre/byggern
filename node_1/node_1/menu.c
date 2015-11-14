#include <stdlib.h>
#include "driver/oled.h"
#include "menu.h"
#include "joystick.h"
#include "game.h"

void update_next(direction dir); // Updates the pointer to a menu object.
void menu_print(menu_t* object); // Prints the menu on oled

menu_t* current;
int next;


void menu_init()
{
	// Setup the menu hierarchy
	sub3sub1sub1.parent = &sub3sub2;
	sub3sub1sub2.parent = &sub3sub2;
	sub3sub3sub1.parent = &sub3sub3;
	sub3sub3sub2.parent = &sub3sub3;
	sub3sub1.parent= &sub3;
	sub3sub2.parent= &sub3;
	sub3sub3.parent= &sub3;
	sub1.parent = &menu;	
	sub2.parent = &menu;
	sub3.parent = &menu;
	current = &menu;
	menu_print(current);
}

void menu_fsm()
{
	static direction curr_dir;
	static direction last_dir = NEUTRAL; 
	
	curr_dir = joy_get_direction();
	if (curr_dir != last_dir)
	{
		switch (curr_dir){
		case RIGHT:
			switch(current->children[next-1]->name[0])
			{
					
				case 'P':       // [P]lay Game
					current = current->children[next-1];
					game_play();
					current = current->parent;
					menu_print(current);
					break;
				case 'H':		// [H]ighscores
					current = current->children[next-1];
					game_print_highscore();
					break;
				default:	// [S]ettings & [C]hoose Input
					current = current->children[next-1];
					menu_print(current);
					break;
				case 'R' :		// [R]eset Scores
					game_reset_highscore();
					current = &menu;
					menu_print(current);
					break;	
				case 'T' :		// [T]ouch as input	
					game_change_mode( 1 );
					current = &menu;
					menu_print(current);
					break;	
				case 'J' :		// [J]oystick as input
					game_change_mode( 0 );
					current = &menu;
					menu_print(current);
					break;
				case 'M' :		// [M]edium as difficulty
					game_change_difficulty( 2 );
					current = &menu;
					menu_print(current);
					break;
				case 'E' :		// [E]asy as difficulty	
					game_change_difficulty( 1 );
					current = &menu;
					menu_print(current);
					break;
			}
			break;
				
		case LEFT:
			if (current->parent != NULL){
				current = current->parent;
				menu_print(current);
			}
			break;
		case UP:
			update_next(curr_dir);
			break;
		case DOWN:
			update_next(curr_dir);
			break;
			default:
			break;
		}
	}
	last_dir = curr_dir;
}


void update_next(direction dir){
	if (dir == DOWN)
	{
		if (next+1 <= current->number_children)
		{
			oled_goto(next,0);
			oled_print(" ");
			next++;
			oled_goto(next,0);
			oled_print("-");
		}
	}
	else
	{
		if (next > 1)
		{
			oled_goto(next,0);
			oled_print(" ");
			next--;
			oled_goto(next,0);
			oled_print("-");
		}
	}
}

void menu_print(menu_t* object){
	next = 1;
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
