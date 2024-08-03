/*
 * DCMOTRO.c
 *
 *  Created on: Jul 5, 2024
 *      Author: Osama
 */
#include "DcMotor.h"
#include "../PWM/PWM.h"
#include "../GPIO/GPIO.h"

void DcMotor_Init(void){
	GPIO_setupPin(DcMotorPort,DcMotorPin1,PIN_OUTPUT);
	GPIO_setupPin(DcMotorPort,DcMotorPin2,PIN_OUTPUT);

	GPIO_writePin(DcMotorPort,DcMotorPin2,LOGIC_LOW);
	GPIO_writePin(DcMotorPort,DcMotorPin2,LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state)
{
	uint8 portvalue = GPIO_readPort(DcMotorPort);
	uint8 state_value = ((portvalue & 0xFC) | state);
	GPIO_writePort(DcMotorPort, state_value);
//	uint8 dutyCycle = (speed * 255) / 100;
	uint8 dutyCycle = 255; //Maximum speed always
	Timer0_PWM_Init(dutyCycle);
}
