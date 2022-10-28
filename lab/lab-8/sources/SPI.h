/*
 * SPI.h
 *
 *  Created on: Oct 27, 2022
 *      Author: jtluk
 */

#ifndef SPI_H_
#define SPI_H_
#include "msp.h"
#include "pinsInint.h"
#include "systick.h"
#include "Toggle.h"
#include <stdbool.h>

void vSPI_Initlize(void);
void vSPI_writeByte(uint8_t userAddress, uint8_t userData);

#endif /* SPI_H_ */
