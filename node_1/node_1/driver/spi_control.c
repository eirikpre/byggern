#include <avr/io.h>
#include "spi_control.h"
#include <stdio.h>

void spi_select()
{
	PORTB &= ~(1<<PB4);
}

void spi_deselect()
{
	PORTB |= (1<<PB4);
}

char spi_receive()
{
	spi_transmit(0);
	return SPDR;
}


void spi_transmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}


void spi_init(){
	/* Set MOSI,SCK and SS output, all others input */
	DDR_SPI |= (1<<DD_MOSI) | (1<<DD_SCK) | (1<<DD_SS);    
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}