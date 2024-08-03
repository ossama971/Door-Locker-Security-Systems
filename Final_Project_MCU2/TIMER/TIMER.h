/*
 * TIMER.h
 *
 *  Created on: Jul 27, 2024
 *      Author: Osama
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_


#include "../utils/std_types.h"
#include "../utils/common_macros.h"


#define NULL ((void *)0)


typedef enum{
	cpu_clk=1,clk_8_prescaler,clk_64_prescaler,clk_256_prescaler,clk_1024_prescaler
}Timer1_Prescaler;

typedef enum{
	normal,compare
}Timer1_Mode;

typedef struct{
	uint16 intial_value;
	uint16 compare_value;
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
}Timer1_ConfigType;

void Timer1_init(const Timer1_ConfigType* config_ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER_TIMER_H_ */
