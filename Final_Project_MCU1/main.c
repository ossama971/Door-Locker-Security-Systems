/*
 * main.c
 *
 *  Created on: Jul 23, 2024
 *      Author: Osama
 */
#include <stdio.h>
#include <string.h>
#include "LCD/LCD.h"
#include "KEYPAD/KEYPAD.h"
#include "UART/UART.h"
#include "util/delay.h"
#include"avr/io.h"
#include "TIMER/TIMER.h"


volatile uint8 ticks = 0;
volatile uint8 stay = 1 ;

volatile uint8 errorCounter = 0;
volatile uint8 correctPassword[5];

void counter(void)
{
	ticks++;
	if(ticks==15) /*15sec*/
	{
		LCD_clearScreen();
		LCD_displayString("Door is Unlocked");
	}
	else if(ticks == 18) /*3 sec after the first 15*/
	{
		LCD_clearScreen();
		LCD_displayString("Door is locking");
	}
	else if (ticks == 33)/*15 secs past the first 18*/
	{
		Timer1_deInit();
		ticks=0;
		LCD_clearScreen();
		LCD_displayString("Door is locked");
		stay = 0;
	}
}


void startTimer()
{

	Timer1_setCallBack(counter);
	Timer1_ConfigType *Timer_Config;
	Timer_Config ->mode = compare;
	Timer_Config ->compare_value = 31250;
	Timer_Config ->intial_value = 0;
	Timer_Config ->prescaler = clk_256_prescaler;
	Timer1_init(Timer_Config);

}

/*Landing Page Functions */
void getPassword(uint8*password,uint8 startColumn)
{
	int counter = 0;
	uint8 key;
	while(counter<5)
	{
		key = KEYPAD_getPressedKey();
		LCD_moveCursor(1,counter + startColumn);
		LCD_displayCharacter('*');
		password[counter] = key;
		counter ++;
	}
}

void sendPassword(uint8 *password)
{
	for(int i = 0;i<5;i++)
	{
		UART_sendByte(password[i]);
		_delay_ms(50);
	}
}
void getEnter()
{
	uint8 key;
	while(key != '=')
		key =  KEYPAD_getPressedKey();
}

uint8 matchPassword(uint8 *password)
{
	LCD_clearScreen();
	LCD_displayString("plz enter pass:");
	getPassword(password, 0 );
	getEnter();
	sendPassword(password);
	uint8 recievedACK = UART_recieveByte();
	//	LCD_displayCharacter(recievedACK);
	if(recievedACK == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


void landingScreen(uint8*password_1, uint8*password_2)
{
	LCD_clearScreen();
	LCD_displayString("plz enter pass:");
	getPassword(password_1, 0 );
	getEnter();
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("plz re-enter the");
	LCD_moveCursor(1,0);
	LCD_displayString("same pass:");
	getPassword(password_2, 10 );
	getEnter();
}


void rotateMotor()
{
	LCD_clearScreen();
	LCD_displayString("Door is");
	LCD_moveCursor(1,0);
	LCD_displayString("Unlocking");
	startTimer();
	while(stay);
}

void errorHandler()
{
	uint8 ack;
	uint8 password[5];
	while(errorCounter<=3)
	{
		ack =  matchPassword(password);
		if(ack == 1 )
		{
			errorCounter=0;
			return;
		}
		else
		{
			errorCounter++;
		}

	}
	if(errorCounter > 3 )
	{
		/*Activate buzzer*/
		sendPassword(correctPassword);
		errorCounter = 0;
		LCD_clearScreen();
		LCD_displayString("ERROR");
		_delay_ms(60000); /*Stop the system for one minute*/
		LCD_clearScreen();
		mainOptions();
	}
}

void mainOptions()
{
	uint8 ack;
	uint8 key;
	uint8 password[5];
	LCD_displayString("+ : Open Door");
	LCD_moveCursor(1,0);
	LCD_displayString("- : Change Pass");
	key = KEYPAD_getPressedKey();

	if(key == '+')
	{
		/*Open Door*/
		UART_sendByte('+');
		ack = matchPassword(password);
		if(ack == 1)
		{
			/*Rotate the motor*/
			rotateMotor();
			LCD_clearScreen();
			mainOptions();

		}
		else
		{
			/*Error*/
			errorHandler();
			UART_sendByte('+');
			sendPassword(correctPassword);
			rotateMotor();
			LCD_clearScreen();
			mainOptions();
		}

	}
	else
	{
		uint8 password_1[5];
		uint8 password_2[5];
		UART_sendByte(key);
		ack = matchPassword(password);
		if(ack == 1)
		{
			passwordCreation(password_1, password_2);
		}
		else
		{
			/*Error*/
			errorHandler();
			UART_sendByte('-');
			sendPassword(correctPassword);
			passwordCreation(password_1, password_2);
		}
	}

}

void passwordCreation(uint8* password_1, uint8* password_2)
{
	uint8 recievedACK = 1;
	landingScreen(password_1,password_2);
	LCD_clearScreen();

	sendPassword(password_1);
	sendPassword(password_2);

	recievedACK = UART_recieveByte();
	if(recievedACK == 1)
	{
		for(int i=0 ;i<5;i++)
		{
			correctPassword[i] = password_1[i];
		}

		mainOptions();
	}
	else
	{
		passwordCreation(password_1,password_2);
	}
}


int main()
{
	SREG  |= (1<<7);              // Enable global interrupts in MC.
	LCD_init();
	uint8  password_1[5];
	uint8  password_2[5];


	UART_ConfigType * UART_Config;
	UART_Config ->bit_data = 8; /* Use 8-Bits Data*/
	UART_Config ->parity = EVEN; /*Even Parity*/
	UART_Config ->stop_bit = oneBit; /*1-Stop Bit*/
	UART_Config ->baudrate = 9600;
	UART_init(UART_Config);


	while(1){
		passwordCreation(password_1,password_2);
		//		UART_sendByte(KEYPAD_getPressedKey());

	}
}
