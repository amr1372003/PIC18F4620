/* 
 * File:   ECU_RELAY.c
 * Author: amr09
 *
 * Created on July 21, 2024, 5:33 PM
 */

#include "ECU_RELAY.h"

/**
 * 
 * @param relay
 * @return 
 */
std_ReturnType RELAY_INIT(const relay_t *relay){
    std_ReturnType ret = E_OK;
    if(NULL == relay){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_temp = {
            .PORT = relay->PORT, 
            .PIN = relay->PIN, 
            .LOGIC = relay->STAT, 
            .DIRECTION = GPIO_DIRECTION_OUTPUT
        };
        GPIO_PIN_INITIALIZE(&pin_temp);
    }
    return ret;
}

/**
 * 
 * @param relay
 * @return 
 */
std_ReturnType RELAY_TURN_ON(const relay_t *relay){
    std_ReturnType ret = E_OK;
    if(NULL == relay){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_temp = {
            .PORT = relay->PORT, 
            .PIN = relay->PIN, 
            .LOGIC = relay->STAT, 
            .DIRECTION = GPIO_DIRECTION_OUTPUT
        };
        ret = GPIO_PIN_WRITE_LOGIC(&pin_temp, GPIO_HIGH);
    }
    return ret;
}

/**
 * 
 * @param relay
 * @return 
 */
std_ReturnType RELAY_TURN_OFF(const relay_t *relay){
    std_ReturnType ret = E_OK;
    if(NULL == relay){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_temp = {
            .PORT = relay->PORT, 
            .PIN = relay->PIN, 
            .LOGIC = relay->STAT, 
            .DIRECTION = GPIO_DIRECTION_OUTPUT
        };
        ret = GPIO_PIN_WRITE_LOGIC(&pin_temp, GPIO_LOW);
    }
    return ret;
}