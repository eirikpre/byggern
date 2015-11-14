#include "can_com.h"
#include <stdio.h>
#include "MCP2515.h"

void can_init()
{
	
	mcp2515_init();
	
	mcp2515_bit_modify(MCP_RXF0SIDH, 0xff , 0x00);
	mcp2515_bit_modify(MCP_RXF0SIDL, 0xE0 , 0x00);
	mcp2515_bit_modify(MCP_CANCTRL, 0xE0 , MODE_NORMAL);
	
}


void can_message_send(can_message_t *message)
{
	char i;
	
	// ID
	mcp2515_write(MCP_TXB0CTRL + 1,message->id);
	mcp2515_write(0x32,0x00);
	
	//Length
	mcp2515_write(MCP_TXB0CTRL + 5,message->length);
	
	// Data
	for (i = 0; i< message->length; i++){
		mcp2515_write(MCP_TXB0CTRL + 6 + i, *((message->data)+i) );
	}
	mcp2515_request_to_send(MCP_RTS_TX0);
}

void can_message_receive(can_message_t* message, int buffer)
{
	char i;
	
	// ID
	message->id = mcp2515_read(MCP_RXB0CTRL+buffer + 1);
	
	// Length
	message->length = mcp2515_read(MCP_RXB0CTRL+buffer + 5);
	
	// Data
	for(i=0;i<message->length;i++)
	{
		*((message->data)+i)  = mcp2515_read(MCP_RXB0CTRL+buffer + 6 + i );
	}
}

int can_get_message(can_message_t* message)
{
	
	if ((mcp2515_read(MCP_CANINTF) & 0x01) == 0x01)
	{
		can_message_receive(message,0);
		mcp2515_bit_modify(MCP_CANINTF,0x01,0x00);
		return 1;
	}
	else
	{
		return 0;
	}
	
}

void can_handle_message(can_message_t* message)
{
	switch (message->id)
	{
		case 'p' :				
			can_print(message);
			break;	
		case 'j' : 
			can_print(message);
			break;
		default:
			can_print(message);	
			break;
	}
}


void can_print(can_message_t* msg)
{
	printf("ID: %c ,Length: %d, ",msg->id,msg->length);
	int i ;
	for (i = 0; i < msg->length ; i++) 
	{
		printf("%c", msg->data[i]);
	}
	printf("\n");
}
