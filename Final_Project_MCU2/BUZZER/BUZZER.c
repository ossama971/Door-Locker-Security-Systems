/*
 * BUZZER.c
 *
 *  Created on: Jul 27, 2024
 *      Author: Osama
 */


#include "BUZZER.h"
#include "../GPIO/GPIO.h"


void Buzzer_init()
{
	GPIO_setupPin(BUZZER_PORT, BUZZER_PIN,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN,LOGIC_LOW);

}
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN,LOGIC_HIGH);
}

void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN,LOGIC_LOW);
}
