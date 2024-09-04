/* 
 * File:   ECU_BUTTON.c
 * Author: amr09
 *
 * Created on July 16, 2024, 9:34 PM
 */

#include "ECU_BUTTON.h"


std_ReturnType BTN_INIT(const btn_t *btn){
    std_ReturnType ret = E_OK;
    if(NULL == btn){
        ret = E_NOT_OK;
    }else{
        ret = GPIO_PIN_DIRECTION_INITIALIZE(&(btn -> BUTTON_PIN));
    }
    return ret;
}
std_ReturnType BTN_READ(const btn_t *btn, btn_stat_t *btn_stat){
    std_ReturnType ret = E_OK;
    logic_t pin_logic_stat_temp = GPIO_LOW;
    if(NULL == btn || NULL == btn_stat){
        ret = E_NOT_OK;
    }else{
        GPIO_PIN_READ_LOGIC(&(btn -> BUTTON_PIN), &pin_logic_stat_temp);
        if(BUTTON_ACTIVE_HIGH == btn -> BUTTON_CONECTION){
            if(GPIO_HIGH == pin_logic_stat_temp){
                *btn_stat = BUTTON_PRESSED;
            }else{
                *btn_stat = BUTTON_RELEASED;
            }
        }else if(BUTTON_ACTIVE_LOW == btn -> BUTTON_CONECTION){
            if(GPIO_HIGH == pin_logic_stat_temp){
                *btn_stat = BUTTON_RELEASED;
            }else{
                *btn_stat = BUTTON_PRESSED;
            }
        }else{}
    }
    return ret;
}