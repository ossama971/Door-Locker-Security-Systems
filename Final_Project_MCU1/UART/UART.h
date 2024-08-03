/*
 * UART.h
 *
 *  Created on: Jul 27, 2024
 *      Author: Osama
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#include "../utils/std_types.h"

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
typedef uint8 UART_BitData;
typedef uint32 UART_BaudRate;
typedef enum{
	Disabled,EVEN = 2, ODD = 3
}UART_Parity;

typedef enum{
	oneBit,twoBits
}UART_StopBit;

typedef struct{
UART_BitData bit_data;
UART_Parity parity;
UART_StopBit stop_bit;
UART_BaudRate baudrate;
}UART_ConfigType;


void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #



#endif /* UART_UART_H_ */
