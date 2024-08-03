/*
 * EEROM.h
 *
 *  Created on: Jul 27, 2024
 *      Author: Osama
 */

#ifndef EEROM_EEROM_H_
#define EEROM_EEROM_H_



#include "../utils/std_types.h"

#define ERROR 0
#define SUCCESS 1

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);


#endif /* EEROM_EEROM_H_ */
