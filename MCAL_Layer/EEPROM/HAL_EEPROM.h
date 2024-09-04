/* 
 * File:   HAL_EEPROM.h
 * Author: amr09
 *
 * Created on August 22, 2024, 12:34 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

#include "../../MCAL_Layer/mcal_std_types.h"
#include "../INTERUPT/MCAL_INTERNAL_INTERRUPT.h"
#include "pic18f4620.h"


std_ReturnType DATA_EEPROM_WRITEBYTE(uint16 add, uint8 data);
std_ReturnType DATA_EEPROM_READBYTE(uint16 add, uint8 *data);

#endif	/* HAL_EEPROM_H */

