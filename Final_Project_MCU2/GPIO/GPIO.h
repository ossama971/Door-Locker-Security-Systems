/*
 * GPIO.h
 *
 *  Created on: Jul 6, 2024
 *      Author: Osama
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_


#include "../utils/std_types.h"

/*Definitions*/
#define NUM_OF_PORTS 	4
#define NUM_OF_PINS		8

#define PORTA_ID		0
#define PORTB_ID		1
#define PORTC_ID		2
#define PORTD_ID		3

#define PIN0			0
#define PIN1			1
#define PIN2			2
#define PIN3			3
#define PIN4			4
#define PIN5			5
#define PIN6			6
#define PIN7			7


/*Type Declarations*/
typedef enum
{
	PIN_INPUT , PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT , PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/*Functions Prototypes*/
void GPIO_setupPin(uint8 port_num , uint8 pin_num, GPIO_PinDirectionType direction);

void GPIO_writePin(uint8 port_num , uint8 pin_num, uint8 value);

uint8 GPIO_readPin(uint8 port_num , uint8 pin_num);


void GPIO_setupPort(uint8 port_num , GPIO_PortDirectionType direction);

void GPIO_writePort(uint8 port_num ,  uint8 value);

uint8 GPIO_readPort(uint8 port_num);



#endif /* GPIO_GPIO_H_ */
