/*
 * BUZZER.h
 *
 *  Created on: Jul 27, 2024
 *      Author: Osama
 */

#ifndef BUZZER_BUZZER_H_
#define BUZZER_BUZZER_H_
#include"../utils/std_types.h"

#define BUZZER_PORT		PORTA_ID
#define BUZZER_PIN		PIN0

void Buzeer_init();
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* BUZZER_BUZZER_H_ */
