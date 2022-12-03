/*
 * encoder.h
 *
 *  Created on: Nov 30, 2022
 *      Author: jtluk
 */

#ifndef ENCODER_H_
#define ENCODER_H_
#include "pinsInit4.h"
#include "readInputs.h"
#include "systick.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct encoder_t
{
    bool b_buttonStatus;
    uint8_t encoderVal;
}encoder_t;

/*
 * Have the pins in the following order in array...
 * 1. Encoder button
 * 2. Encoder direction 1
 * 3. Encoder direction 2
 */
void vEncoder_Init(port4GPIO_t * s_encoderPorts_ptr);
void vEncoder_GetEncoderData(encoder_t * s_userEncoder_ptr);

#endif /* ENCODER_H_ */
