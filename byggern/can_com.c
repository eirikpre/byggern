#include "can_com.h"
#include "MCP2515.h"
#include "can_control.h"

void can_message_send(can_message_t *message){
	char i;
	
	// ID
	can_write(0x31,message->id);
	can_write(0x32,0x00);
	
	//Length
	can_write(0x35,message->length);
	
	//Data
	for (i = 0; i< message->length; i++){
		can_write(0x36+i, message->data[i] );
	}
	
	can_request_to_send(MCP_RTS_TX0);
}