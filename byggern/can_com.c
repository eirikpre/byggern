#include "can_com.h"

#include "MCP2515.h"

void can_init()
{
	
	mcp2515_init();
	
	mcp2515_bit_modify(MCP_RXF0SIDH, 0xff , 0x00);
	mcp2515_bit_modify(MCP_RXF0SIDL, 0xE0 , 0x00);
	
	
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

void can_message_receive(can_message_t* message)
{
	char i;
	
	// ID
	message->id = mcp2515_read(MCP_RXB0CTRL + 1);
	
	// Length
	message->length = mcp2515_read(MCP_RXB0CTRL + 5);
	
	// Data
	for(i=0;i<message->length;i++)
	{
		*((message->data)+i)  = mcp2515_read(MCP_RXB0CTRL + 6 + i );
	}
	
}