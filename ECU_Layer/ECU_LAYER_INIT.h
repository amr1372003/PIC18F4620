/* 
 * File:   ECU_LAYER_INIT.h
 * Author: amr09
 *
 * Created on July 31, 2024, 3:05 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

#include "LED/ECU_LED.h"
#include "PUSH_BUTTON/ECU_BUTTON.h"
#include "RELAY/ECU_RELAY.h"
#include "DC_MOTOR/ECU_DC_MOTOR.h"
#include "7_segment/ECU_7_SEG.h"
#include "KEYPAD/ECU_KEYPAD.h"
#include "CHAR_LCD/ECU_CHAR_LCD.h"
#include "LED_MATRIX/ECU_LED_MATRIX.h"
#include "../MCAL_Layer/INTERUPT/MCAL_EXTERNAL_INTERRUPT.h"
#include "../MCAL_Layer/EEPROM/HAL_EEPROM.h"

void ECU_INIT();

#endif	/* ECU_LAYER_INIT_H */

