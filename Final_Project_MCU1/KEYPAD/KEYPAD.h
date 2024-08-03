/*
 * KEYPAD.h
 *
 *  Created on: Jul 27, 2024
 *      Author: Osama
 */

#ifndef KEYPAD_KEYPAD_H_
#define KEYPAD_KEYPAD_H_


#include "../utils/std_types.h"

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID                PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID           PIN0

#define KEYPAD_COL_PORT_ID                PORTB_ID
#define KEYPAD_FIRST_COL_PIN_ID           PIN4

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void);


#endif /* KEYPAD_KEYPAD_H_ */
