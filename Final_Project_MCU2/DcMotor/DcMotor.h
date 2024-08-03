/*
 * DCMOTRO.h
 *
 *  Created on: Jul 5, 2024
 *      Author: Osama
 */

#ifndef DCMOTOR_DCMOTOR_H_
#define DCMOTOR_DCMOTOR_H_

#include"../utils/std_types.h"


#define DcMotorPin1		PIN0
#define DcMotorPin2		PIN1
#define DcMotorPort		PORTB_ID
typedef enum{
	STOP, ACW , CW
}DcMotor_State;


void DcMotor_Init(void);

void DcMotor_Rotate(DcMotor_State state);


#endif /* DCMOTOR_DCMOTOR_H_ */
