#ifndef SPI_CONTROL_H_
#define SPI_CONTROL_H_


#define DDR_SPI DDRB
#define DD_SS	DDB4
#define DD_MOSI DDB5
#define DD_MISO DDB6
#define DD_SCK	DDB7




void spi_init();
void spi_transmit(char cData);
char spi_receive();
void spi_deselect();
void spi_select();

#endif /* SPI_CONTROL_H_ */