#ifndef MENU_H_
#define MENU_H_


typedef struct menu_t
{
	char name[15];
	int number_children;
	struct menu_t* parent;
	struct menu_t* children[7];	
}menu_t;

void menu_init();
void menu_fsm(); //Chooses state based on menu object and joystick input

#endif /* MENU_H_ */