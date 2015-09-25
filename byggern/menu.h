#ifndef MENU_H_
#define MENU_H_


typedef struct menu_t
{
	char name[15];
	int number_children;
	void (*fnc_pointer)();
	struct menu_t* parent;
	struct menu_t* children[7];
	
		
}menu_t;





void menu_print(menu_t* object);
void menu_init();


#endif /* MENU_H_ */