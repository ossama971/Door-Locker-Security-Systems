/*
 * TIMER.c
 *
 *  Created on: Jul 27, 2024
 *      Author: Osama
 */

#include "TIMER.h"
#include "avr/io.h"
#include "avr/interrupt.h"

static volatile void(*callback_ptr)(void) = NULL;


ISR(TIMER1_OVF_vect)
{
	if(callback_ptr != NULL){
		(*callback_ptr)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(callback_ptr != NULL){
		(*callback_ptr)();
	}
}

void Timer1_init(const Timer1_ConfigType* config_ptr)
{
	TCNT1 = config_ptr->intial_value;
	TCCR1A = (1<<FOC1A);
	if(config_ptr->mode == normal)
	{
		TIMSK |= (1<<TOIE1); //enable interrupt for overflow/normal mode
		TCCR1B |= (config_ptr->prescaler<<CS10);
	}
	else{
		OCR1A = config_ptr->compare_value; // insert compare value
		TIMSK |= (1<<OCIE1A); //enable interrupt for compare A match
		TCCR1B = (1<<WGM12) | (config_ptr->prescaler<<CS10); // set prescaler and ctc mode
	}
}

void Timer1_deInit(void)
{
	//Clear Timer1 Registers.
	TCCR1A=0;	TCCR1B=0;	TCNT1=0;	OCR1A=0;	TIMSK=0;
}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	callback_ptr = a_ptr;
}
