#include "can_control.h"
#include "spi_control.h"
#include "MCP2515.h"
#include <stdio.h>

void mcp2515_init(){
	char status;
	spi_init();
	can_reset();
	
	status = can_read_status();
	if ((status& MODE_MASK) != MODE_CONFIG)
	{
		printf("MCP2515 is not in config mode!\n");
	}
	
}
char can_read (char addr){
	char result;
	
	spi_select();
	
	spi_transmit(MCP_READ);
	spi_transmit(addr);
	result = spi_receive();
	
	spi_deselect();
	
	return result;
}

void can_write(char addr, char data)
{
	spi_select();
	
	spi_transmit(MCP_WRITE);
	spi_transmit(addr);
	spi_transmit(data);
	
	spi_deselect();
	
}

void can_request_to_send(int reg)
{
	spi_select();
	
	spi_transmit(reg);
	
	spi_deselect();
}

void can_bit_modify(char addr, char mask_byte, char data)
{
	spi_select();
	
	spi_transmit(MCP_BITMOD);
	spi_transmit(addr);
	spi_transmit(mask_byte);
	spi_transmit(data);
	
	spi_deselect();
}

void can_reset()
{
	spi_select();
	
	spi_transmit(MCP_RESET);
	
	spi_deselect();
}

char can_read_status()
{
	char output;
	spi_select();
	
	spi_transmit(MCP_CANSTAT);
	output = spi_receive();
	
	spi_deselect();
	return output;
}


