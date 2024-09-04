/* 
 * File:   ECU_LED_MATRIX.h
 * Author: amr09
 *
 * Created on August 13, 2024, 9:50 PM
 */

#ifndef ECU_LED_MATRIX_H
#define	ECU_LED_MATRIX_H

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_matrix_cfg.h"

#define ECU_LED_MATRIX_ROWS      8
#define ECU_LED_MATRIX_COLUMNS   8

typedef struct{
    pin_config_t LED_MATRIX_ROW_PINS[ECU_LED_MATRIX_ROWS];
    pin_config_t LED_MATRIX_COLUMN_PINS[ECU_LED_MATRIX_COLUMNS];
}led_matrix_t;

std_ReturnType LED_MATRIX_INIT(const led_matrix_t *led_matrix);
std_ReturnType LED_MATRIX_SET_LED(const led_matrix_t *led_matrix, uint8 row, uint8 column);
std_ReturnType LED_MATRIX_SET_LEDS(const led_matrix_t *led_matrix, uint8 *columns);

#endif	/* ECU_LED_MATRIX_H */

