#ifndef CAN_COM_H_
#define CAN_COM_H_

typedef struct  
{
	char id;
	char length;
	char data[8];
} can_message_t;


void can_init();
void can_message_send(can_message_t *message);
void can_message_receive(can_message_t* message, int buffer);
int can_get_message(can_message_t* message);
void can_print(can_message_t* msg);
void can_handle_message(can_message_t* message);




#endif /* CAN_COM_H_ */

