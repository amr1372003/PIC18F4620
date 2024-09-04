/* 
 * File:   application.h
 * Author: amr09
 *
 * Created on September 16, 2023, 6:31 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include "ECU_Layer/ECU_LAYER_INIT.h"
#include "MCAL_Layer/INTERUPT/MCAL_EXTERNAL_INTERRUPT.h"
#include "MCAL_Layer/ADC/HAL_ADC.h"
#include "MCAL_Layer/TMR/HAL_TMR0.h"

extern led_matrix_t led_matrix1;
extern std_ReturnType ret;

extern _7_seg_t seg1;
extern pin_config_t seg1_enable;
extern pin_config_t seg2_enable;
extern keypad_t key1;

extern char_lcd_4bit_t lcd1;
extern char_lcd_8bit_t lcd2;

void app_init();

#endif	/* APPLICATION_H */

