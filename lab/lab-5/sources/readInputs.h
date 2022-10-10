/*
 * readInputs.h
 *
 *  Created on: Sep 2, 2022
 *      Author: jtluk
 */

#ifndef READINPUTS_H_
#define READINPUTS_H_

#define MIN_DEBOUNCE_VAL 0xe001
#define MAX_DEBOUNCE_VAL 0xf000
#include "pinsInint.h"
#include <stdbool.h>

bool xReadInputs_ReadPin(port2GPIO_t e_userPin);
bool xReadInputs_read(port2GPIO_t e_userPin);

#endif /* READINPUTS_H_ */
