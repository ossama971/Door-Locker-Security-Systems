/*
 * main.c
 *
 *  Created on: Jul 23, 2024
 *      Author: Osama
 */

#include"UART/UART.h"
#include "util/delay.h"
#include "TWI/TWI.h"
#include "EEROM/EEROM.h"
#include "DcMotor/DcMotor.h"
#include"TIMER/TIMER.h"
#include "BUZZER/BUZZER.h"
volatile uint8 errorcounter = 0;
#define EEROM_START_ADDRESS  0x311

volatile uint8 ticks = 0;
void counter(void){
	ticks++;
	if(ticks==15) /*15sec*/
	{
		DcMotor_Rotate(STOP);
	}
	else if(ticks == 18) /*3 sec after the first 15*/
	{
		DcMotor_Rotate(CW);
	}
	else if (ticks == 33)/*15 secs past the first 18*/
	{
		Timer1_deInit();
		DcMotor_Rotate(STOP);
		ticks=0;

		//
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

void recievePassword(uint8 *password)
{
	uint8 key;
	for(int i=0 ;i<5;i++)
	{
		key = UART_recieveByte();
		password[i] = key;
	}
}

uint8 checkSavedPassword(uint8 *passwordCheck)
{
	uint16 address = EEROM_START_ADDRESS;
	uint8 match = 1;
	uint8 savedPassword[5];
	for(int i = 0; i < 5; i++)
	{
		EEPROM_readByte(address, &savedPassword[i]);
		_delay_ms(10);
		address++;
	}
	for(int i=0 ;i<5;i++)
	{
		if(passwordCheck[i] != savedPassword[i])
		{
			match = 0;
			break;
		}
	}

	return match;
}

void errorHandler()
{
	uint8 match = 0;
	uint8 passwordCheck[5];
	while(!match){
		errorcounter++;
		recievePassword(passwordCheck);
		match = checkSavedPassword(passwordCheck);
		UART_sendByte(match);
		_delay_ms(50);
	}
	if(errorcounter>=2)
	{
		errorcounter = 0;
		Buzzer_on();
		_delay_ms(60000);
		Buzzer_off();
	}
	recieveCommand();
}
void recieveCommand()
{
	uint8 passwordCheck[5];
	uint8 match;
	uint8 key = 0;
	key = UART_recieveByte();
	recievePassword(passwordCheck);
	match = checkSavedPassword(passwordCheck);
	if(key == 11 ) /*+ open the door*/
			{
		if(match)
		{
			UART_sendByte(match);
			_delay_ms(50);
			DcMotor_Rotate(ACW);
			startTimer();
			recieveCommand();
		}
		else
		{
			/*Error*/
			UART_sendByte(match);
			_delay_ms(50);
			errorHandler();

		}
			}
	else /*- change password*/
	{
		if(match)
		{
			UART_sendByte(match);
			_delay_ms(50);
			uint8 password_1[5];
			uint8 password_2[5];
			passwordCreation(password_1, password_2);

		}
		else
		{
			UART_sendByte(match);
			_delay_ms(50);
			errorHandler();
		}
	}
}

void passwordCreation(uint8 *password_1, uint8 *password_2)
{
	uint16 address = EEROM_START_ADDRESS;
	uint8 match = 1;

	recievePassword(password_1);
	recievePassword(password_2);

	for(int i=0 ;i<5;i++)
	{
		if(password_1[i] != password_2[i])
		{
			match = 0;
			break;
		}
	}
	if(match)
	{
		UART_sendByte(match);
		_delay_ms(50);
		for(int i = 0; i < 5; i++)
		{
			EEPROM_writeByte(address, password_1[i]);
			_delay_ms(10);
			address++;
		}
		recieveCommand();


	}
	else
	{
		UART_sendByte(match);
		_delay_ms(50);
	}

}


int main()
{
	uint8  password_1[5] ;
	uint8  password_2[5] ;

	TWI_ConfigType *TWI_Config;
	TWI_Config ->address = 0x0a;
	TWI_Config ->bit_rate = 0x02;
	TWI_init(TWI_Config);

	UART_ConfigType * UART_Config;
	UART_Config ->bit_data = 8; /* Use 8-Bits Data*/
	UART_Config ->stop_bit = oneBit; /*1-Stop Bit*/
	UART_Config ->parity = EVEN; /*Even Parity*/
	UART_Config ->baudrate = 9600;
	UART_init(UART_Config);

	Buzzer_init();
	DcMotor_Init();

	while(1)
	{
		passwordCreation(password_1, password_2);
		//		recieveCommand();
	}
}
