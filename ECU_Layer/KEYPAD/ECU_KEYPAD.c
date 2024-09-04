/* 
 * File:   ECU_KEYPAD.c
 * Author: amr09
 *
 * Created on July 31, 2024, 2:19 PM
 */

#include "ECU_KEYPAD.h"


static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'#', '0', '=', '+'}
};

/**
 * 
 * @param keypad
 * @return 
 */
std_ReturnType KEYPAD_INIT(const keypad_t *keypad){
    std_ReturnType ret = E_OK;
    if(NULL == keypad){
        ret = E_NOT_OK;
    }else{
        for(uint8 i = 0; i < ECU_KEYPAD_ROWS; i++){
            ret = GPIO_PIN_INITIALIZE(&(keypad -> KEYPAD_ROW_PINS[i]));
        }
        for(uint8 j = 0; j < ECU_KEYPAD_COLUMNS; j++){
            ret = GPIO_PIN_INITIALIZE(&(keypad -> KEYPAD_COLUMN_PINS[j]));
        }
    }
    return ret;
}

/**
 * 
 * @param keypad
 * @param value
 * @return 
 */
std_ReturnType KEYPAD_GET_VALUE(const keypad_t *keypad, uint8 *value){
    std_ReturnType ret = E_OK;
    logic_t column_logic = 0;
    if(NULL == keypad || NULL == value){
        ret = E_NOT_OK;
    }else{
        for(uint8 i = 0; i < ECU_KEYPAD_ROWS;i++){
            for(uint8 j = 0; j < ECU_KEYPAD_ROWS; j++){
                ret = GPIO_PIN_WRITE_LOGIC(&(keypad -> KEYPAD_ROW_PINS[j]), GPIO_LOW);
            }
            
            ret = GPIO_PIN_WRITE_LOGIC(&(keypad -> KEYPAD_ROW_PINS[i]), GPIO_HIGH);
            
            for(uint8 k = 0; k < ECU_KEYPAD_COLUMNS; k++){
                ret = GPIO_PIN_READ_LOGIC(&(keypad -> KEYPAD_COLUMN_PINS[k]), &(column_logic));
                if(column_logic == GPIO_HIGH){
                    *value = btn_values[i][k];
                }
            }
            
        }
    }
    return ret;
}