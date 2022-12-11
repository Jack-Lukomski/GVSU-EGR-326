/*
 * port3ReadInputs.h
 *
 *  Created on: Sep 7, 2022
 *      Author: jtluk
 */

#ifndef PORT3READINPUTS_H_
#define PORT3READINPUTS_H_
#define MIN_DEBOUNCE_VAL 0xe000
#define MAX_DEBOUNCE_VAL 0xf000
#include "port3PinsInit.h"
#include <stdbool.h>

bool xReadInputs_3ReadPin(port3GPIO_t e_userPin);
static bool xPrv_ReadInputs_3read(port3GPIO_t e_userPin);


#endif /* PORT3READINPUTS_H_ */
