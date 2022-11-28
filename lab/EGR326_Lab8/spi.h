#include <msp.h>

#define SPIPORT P3
#define CLK BIT5
#define MOSI BIT6
#define SSPORT P5
#define SSPIN BIT2

int x;

#ifndef SPI_H_
#define SPI_H_

void spi_init(void);

void spi_write(uint8_t addy, uint8_t data);

#endif /* SPI_H_ */