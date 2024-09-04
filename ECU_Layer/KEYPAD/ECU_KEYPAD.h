/* 
 * File:   ECU_KEYPAD.h
 * Author: amr09
 *
 * Created on July 31, 2024, 2:19 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_keypad_cfg.h"

#define ECU_KEYPAD_ROWS      4
#define ECU_KEYPAD_COLUMNS   4

typedef struct{
    pin_config_t KEYPAD_ROW_PINS[ECU_KEYPAD_ROWS];
    pin_config_t KEYPAD_COLUMN_PINS[ECU_KEYPAD_COLUMNS];
}keypad_t;

std_ReturnType KEYPAD_INIT(const keypad_t *keypad);
std_ReturnType KEYPAD_GET_VALUE(const keypad_t *keypad, uint8 *value);

#endif	/* ECU_KEYPAD_H */

