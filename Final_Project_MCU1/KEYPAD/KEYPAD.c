#include "KEYPAD.h"
#include "../GPIO/GPIO.h"
#include <util/delay.h>

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
#elif (KEYPAD_NUM_COLS == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
#endif

#endif /* STANDARD_KEYPAD */

uint8 KEYPAD_getPressedKey(void)
{
    uint8 col, row;
    // Setup rows as inputs with pull-up resistors
    for (row = 0; row < KEYPAD_NUM_ROWS; row++)
    {
        GPIO_setupPin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, PIN_INPUT);
        GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, 1); // Enable internal pull-up resistor
    }
    // Setup columns as inputs with pull-up resistors
    for (col = 0; col < KEYPAD_NUM_COLS; col++)
    {
        GPIO_setupPin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col, PIN_INPUT);
        GPIO_writePin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col, 1); // Enable internal pull-up resistor
    }
    while (1)
    {
        for (row = 0; row < KEYPAD_NUM_ROWS; row++) /* loop for rows */
        {
            /* Set this row to output low */
            GPIO_setupPin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, PIN_OUTPUT);
            GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, 0);

            for (col = 0; col < KEYPAD_NUM_COLS; col++) /* loop for columns */
            {
                /* Check if the switch is pressed in this column */
                if (GPIO_readPin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col) == 0)
                {
                    /* Wait for debounce */
                    _delay_ms(5);

                    /* Check again if the button is still pressed */
                    if (GPIO_readPin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col) == 0)
                    {
                        while (GPIO_readPin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col) == 0);
                        /* Wait for the button to be released */
                        #if (KEYPAD_NUM_COLS == 3)
                            #ifdef STANDARD_KEYPAD
                                return ((row * KEYPAD_NUM_COLS) + col + 1);
                            #else
                                return KEYPAD_4x3_adjustKeyNumber((row * KEYPAD_NUM_COLS) + col + 1);
                            #endif
                        #elif (KEYPAD_NUM_COLS == 4)
                            #ifdef STANDARD_KEYPAD
                                return ((row * KEYPAD_NUM_COLS) + col + 1);
                            #else
                                return KEYPAD_4x4_adjustKeyNumber((row * KEYPAD_NUM_COLS) + col + 1);
                            #endif
                        #endif
                    }
                }
            }
            /* Set this row back to input */
            GPIO_setupPin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, PIN_INPUT);
            GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, 1); // Enable internal pull-up resistor
        }
    }
}



#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
		case 10: keypad_button = '*'; // ASCII Code of *
				 break;
		case 11: keypad_button = 0;
				 break;
		case 12: keypad_button = '#'; // ASCII Code of #
				 break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
}

#elif (KEYPAD_NUM_COLS == 4)

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
		case 1: keypad_button = 7;
				break;
		case 2: keypad_button = 8;
				break;
		case 3: keypad_button = 9;
				break;
		case 4: keypad_button = '%'; // ASCII Code of %
				break;
		case 5: keypad_button = 4;
				break;
		case 6: keypad_button = 5;
				break;
		case 7: keypad_button = 6;
				break;
		case 8: keypad_button = '*'; /* ASCII Code of '*' */
				break;
		case 9: keypad_button = 1;
				break;
		case 10: keypad_button = 2;
				break;
		case 11: keypad_button = 3;
				break;
		case 12: keypad_button = '-'; /* ASCII Code of '-' */
				break;
		case 13: keypad_button = 13;  /* ASCII of Enter */
				break;
		case 14: keypad_button = 0;
				break;
		case 15: keypad_button = '='; /* ASCII Code of '=' */
				break;
		case 16: keypad_button = '+'; /* ASCII Code of '+' */
				break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
}

#endif

#endif /* STANDARD_KEYPAD */
