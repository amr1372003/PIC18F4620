/* 
 * File:   ECU_7_SEG.h
 * Author: amr09
 *
 * Created on July 25, 2024, 6:13 PM
 */

#ifndef ECU_7_SEG_H
#define	ECU_7_SEG_H

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_7_seg_cfg.h"

typedef enum{
    COM_CATHODE = 0,
    COM_ANODE
}_7_seg_type_t;

typedef struct{
    pin_config_t _7_SEG_PINS[4];
    _7_seg_type_t _7_SEG_TYPE;
}_7_seg_t;

std_ReturnType _7_SEG_INIT(const _7_seg_t *seg);
std_ReturnType _7_SEG_WRITE(const _7_seg_t *seg, uint8 data);
uint8 ASCII_TO_INTEGER(uint8 *asciiChar);

#endif	/* ECU_7_SEG_H */

