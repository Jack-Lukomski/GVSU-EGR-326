/*
 * stateMachene.h
 *
 *  Created on: Sep 5, 2022
 *      Author: jtluk
 */

#ifndef STATEMACHENE_H_
#define STATEMACHENE_H_

#include "pinsInint.h"

typedef enum stateOrder_t
{
    allOff,
    redOn,
    greenOn,
    blueOn,
}stateOrder_t;

typedef (*void)(stateMachieneFunction_ptr)(stateOrder_t);




#endif /* STATEMACHENE_H_ */
