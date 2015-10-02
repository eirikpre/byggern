#ifndef CAN_COM_H_
#define CAN_COM_H_

typedef struct  
{
	char id;
	char length;
	char data[8];
} can_message_t;



void can_message_send(can_message_t *message);

#endif /* CAN_COM_H_ */