#ifndef SPI_CONTROL_H_
#define SPI_CONTROL_H_


#define DDR_SPI DDRB
#define DD_SS	DDB0
#define DD_MOSI DDB2
#define DD_MISO DDB3
#define DD_SCK	DDB1


void spi_init(void);
void spi_transmit(char cData);
char spi_receive(void);
void spi_deselect(void);
void spi_select(void);

#endif /* SPI_CONTROL_H_ */