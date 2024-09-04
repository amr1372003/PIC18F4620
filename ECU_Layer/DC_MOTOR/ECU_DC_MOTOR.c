/* 
 * File:   ECU_DC_MOTOR.c
 * Author: amr09
 *
 * Created on July 23, 2024, 1:20 PM
 */

#include "ECU_DC_MOTOR.h"

/**
 * 
 * @param dc_motor
 * @return 
 */
std_ReturnType DC_MOTOR_INIT(const dc_motor_t *dc_motor){
    std_ReturnType ret = E_OK;
    if(NULL == dc_motor){
        ret = E_NOT_OK;
    }else{
        GPIO_PIN_INITIALIZE(&(dc_motor ->DC_MOTOR[0]));
        GPIO_PIN_INITIALIZE(&(dc_motor ->DC_MOTOR[1]));
    }
    return ret;
}

/**
 * 
 * @param dc_motor
 * @return 
 */
std_ReturnType DC_MOTOR_MOVE_RIGHT(const dc_motor_t *dc_motor){
    std_ReturnType ret = E_OK;
    if(NULL == dc_motor){
        ret = E_NOT_OK;
    }else{
        GPIO_PIN_WRITE_LOGIC(&(dc_motor ->DC_MOTOR[0]), GPIO_HIGH);
        GPIO_PIN_WRITE_LOGIC(&(dc_motor ->DC_MOTOR[1]), GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param dc_motor
 * @return 
 */
std_ReturnType DC_MOTOR_MOVE_LEFT(const dc_motor_t *dc_motor){
    std_ReturnType ret = E_OK;
    if(NULL == dc_motor){
        ret = E_NOT_OK;
    }else{
        GPIO_PIN_WRITE_LOGIC(&(dc_motor ->DC_MOTOR[1]), GPIO_HIGH);
        GPIO_PIN_WRITE_LOGIC(&(dc_motor ->DC_MOTOR[0]), GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param dc_motor
 * @return 
 */
std_ReturnType DC_MOTOR_STOP(const dc_motor_t *dc_motor){
    std_ReturnType ret = E_OK;
    if(NULL == dc_motor){
        ret = E_NOT_OK;
    }else{
        GPIO_PIN_WRITE_LOGIC(&(dc_motor ->DC_MOTOR[0]), GPIO_LOW);
        GPIO_PIN_WRITE_LOGIC(&(dc_motor ->DC_MOTOR[1]), GPIO_LOW);
    }
    return ret;
}