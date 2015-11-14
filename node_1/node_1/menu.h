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


menu_t sub3sub1sub1 = {"Touch"};
menu_t sub3sub1sub2 = {"Joystick"};
menu_t sub3sub3sub1 = {"Easy"};
menu_t sub3sub3sub2 = {"Medium"};

menu_t sub3sub1 = {"Choose input",2,NULL,	{&sub3sub1sub1,&sub3sub1sub2}};
menu_t sub3sub2 = {"Reset Scores"};
menu_t sub3sub3 = {"Difficulty",2,NULL, {&sub3sub3sub1, &sub3sub3sub2}};

menu_t sub1 = {"Play game"};
menu_t sub2 = {"Highscores"};
menu_t sub3 = {"Settings",	3,	NULL,	{&sub3sub1, &sub3sub2,&sub3sub3}};
menu_t menu = {"Main Menu",	3,	NULL,	{&sub1,&sub2,&sub3}};


#endif /* MENU_H_ */