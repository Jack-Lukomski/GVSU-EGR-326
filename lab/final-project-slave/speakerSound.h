/*
 * speakerSound.h
 *
 *  Created on: Dec 5, 2022
 *      Author: jtluk
 */

#ifndef SPEAKERSOUND_H_
#define SPEAKERSOUND_H_
#include "msp.h"

void vSpeakerSound_Initlize(void);
void vSpeakerSound_AdjustNoteVol(uint16_t period_note, uint16_t DC_volume);

#endif /* SPEAKERSOUND_H_ */
