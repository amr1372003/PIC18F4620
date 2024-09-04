/* 
 * File:   ECU_7_SEG.c
 * Author: amr09
 *
 * Created on July 25, 2024, 6:13 PM
 */

#include "ECU_7_SEG.h"


/**
 * 
 * @param seg
 * @return 
 */
std_ReturnType _7_SEG_INIT(const _7_seg_t *seg){
    std_ReturnType ret = E_OK;
    if(NULL == seg){
        ret = E_NOT_OK;
    }else{
        ret = GPIO_PIN_INITIALIZE(&(seg ->_7_SEG_PINS[0]));
        ret = GPIO_PIN_INITIALIZE(&(seg ->_7_SEG_PINS[1]));
        ret = GPIO_PIN_INITIALIZE(&(seg ->_7_SEG_PINS[2]));
        ret = GPIO_PIN_INITIALIZE(&(seg ->_7_SEG_PINS[3]));
    }
    return ret;
}

/**
 * 
 * @param seg
 * @param data
 * @return 
 */
std_ReturnType _7_SEG_WRITE(const _7_seg_t *seg, uint8 data){
    std_ReturnType ret = E_OK;
    if(NULL == seg || data > 9){
        ret = E_NOT_OK;
    }else{
        ret = GPIO_PIN_WRITE_LOGIC(&(seg ->_7_SEG_PINS[0]), (data & 0X01));
        ret = GPIO_PIN_WRITE_LOGIC(&(seg ->_7_SEG_PINS[1]), ((data >> 1) & 0X01));
        ret = GPIO_PIN_WRITE_LOGIC(&(seg ->_7_SEG_PINS[2]), ((data >> 2) & 0X01));
        ret = GPIO_PIN_WRITE_LOGIC(&(seg ->_7_SEG_PINS[3]), ((data >> 3) & 0X01));
    }
    return ret;
}

/**
 * 
 * @param asciiChar
 * @return 
 */
uint8 ASCII_TO_INTEGER(uint8 *asciiChar) {
    // Ensure the character is a digit
    if (*asciiChar >= '0' && *asciiChar <= '9') {
        return *asciiChar - '0';
    } else {
        // Return -1 if the character is not a digit
        return *asciiChar;
    }
}