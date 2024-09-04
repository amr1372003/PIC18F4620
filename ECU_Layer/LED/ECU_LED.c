/* 
 * File:   ECU_LED.c
 * Author: amr09
 *
 * Created on September 16, 2023, 5:59 PM
 */

#include"ECU_LED.h"


/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the led OFF or ON.
 * @param led : pointer to the led module configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
std_ReturnType LED_INIT(const led_t *led){
    std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_temp = {
            .PORT = led->PORT, 
            .PIN = led->PIN, 
            .LOGIC = led->LED_STATUS, 
            .DIRECTION = GPIO_DIRECTION_OUTPUT
        };
        GPIO_PIN_INITIALIZE(&pin_temp);
    }
    return ret;
}

/**
 * @brief Turn the led on
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
std_ReturnType LED_TURN_ON(const led_t *led){
    std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_temp = {
            .PORT = led->PORT, 
            .PIN = led->PIN, 
            .LOGIC = led->LED_STATUS, 
            .DIRECTION = GPIO_DIRECTION_OUTPUT
        };
        GPIO_PIN_WRITE_LOGIC(&pin_temp, GPIO_HIGH);
    }
    return ret;
}

/**
 * @brief Turn the led off
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
std_ReturnType LED_TURN_OFF(const led_t *led){
    std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_temp = {
            .PORT = led->PORT, 
            .PIN = led->PIN, 
            .LOGIC = led->LED_STATUS, 
            .DIRECTION = GPIO_DIRECTION_OUTPUT
        };
        GPIO_PIN_WRITE_LOGIC(&pin_temp, GPIO_LOW);
    }
    return ret;
}

/**
 * @brief Toggle the led
 * @param led : pointer to the led module configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
std_ReturnType LED_TOGGLE(const led_t *led){
    std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_temp = {
            .PORT = led->PORT, 
            .PIN = led->PIN, 
            .LOGIC = led->LED_STATUS, 
            .DIRECTION = GPIO_DIRECTION_OUTPUT
        };
        GPIO_PIN_TOGGLE_LOGIC(&pin_temp);
    }
    return ret;
}