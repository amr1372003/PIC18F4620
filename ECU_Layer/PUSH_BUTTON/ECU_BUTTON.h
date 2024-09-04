/* 
 * File:   ECU_BUTTON.h
 * Author: amr09
 *
 * Created on July 16, 2024, 9:32 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"


typedef enum{
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED
}btn_stat_t;

typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}btn_active_t;

typedef struct{
    pin_config_t BUTTON_PIN;
    btn_stat_t BUTTON_STAT;
    btn_active_t BUTTON_CONECTION;
}btn_t;

std_ReturnType BTN_INIT(const btn_t *btn);
std_ReturnType BTN_READ(const btn_t *btn, btn_stat_t *btn_stat);

#endif	/* ECU_BUTTON_H */

