/* 
 * File:   ECU_LED_MATRIX.c
 * Author: amr09
 *
 * Created on August 13, 2024, 9:50 PM
 */

#include "ECU_LED_MATRIX.h"

/**
 * 
 * @param led_matrix
 * @return 
 */
std_ReturnType LED_MATRIX_INIT(const led_matrix_t *led_matrix){
    std_ReturnType ret = E_OK;
    if(NULL == led_matrix){
        ret = E_NOT_OK;
    }else{
        for(uint8 i = 0; i < ECU_LED_MATRIX_ROWS; i++){
            ret = GPIO_PIN_INITIALIZE(&(led_matrix -> LED_MATRIX_ROW_PINS[i]));
        }
        for(uint8 j = 0; j < ECU_LED_MATRIX_COLUMNS; j++){
            ret = GPIO_PIN_INITIALIZE(&(led_matrix -> LED_MATRIX_COLUMN_PINS[j]));
        }
    }
    return ret;
}

/**
 * 
 * @param led_matrix
 * @param rows
 * @param columns
 * @return 
 */
std_ReturnType LED_MATRIX_SET_LED(const led_matrix_t *led_matrix, uint8 row, uint8 column){
    std_ReturnType ret = E_OK;
    if(NULL == led_matrix || row > ECU_LED_MATRIX_ROWS || column >  ECU_LED_MATRIX_COLUMNS){
        ret = E_NOT_OK;
    }else{
        row--;
        column--;
        
        // Reset all rows to HIGH (turn off all LEDs)
        for (uint8_t i = 0; i < ECU_LED_MATRIX_ROWS; i++) {
            ret &= GPIO_PIN_WRITE_LOGIC(&(led_matrix->LED_MATRIX_ROW_PINS[i]), GPIO_HIGH);
        }

        // Reset all columns to LOW (turn off all LEDs)
        for (uint8_t j = 0; j < ECU_LED_MATRIX_COLUMNS; j++) {
            ret &= GPIO_PIN_WRITE_LOGIC(&(led_matrix->LED_MATRIX_COLUMN_PINS[j]), GPIO_LOW);
        }

        ret &= GPIO_PIN_WRITE_LOGIC(&(led_matrix->LED_MATRIX_ROW_PINS[row]), GPIO_LOW);
        ret &= GPIO_PIN_WRITE_LOGIC(&(led_matrix->LED_MATRIX_COLUMN_PINS[column]), GPIO_HIGH);
    }
    return ret;
}

/**
 * 
 * @param led_matrix
 * @param columns
 * @return 
 */
std_ReturnType LED_MATRIX_SET_LEDS(const led_matrix_t *led_matrix, uint8 *columns){
    std_ReturnType ret = E_OK;
    uint8_t row = 0;
    uint8_t column = 0;
    if(NULL == led_matrix || columns == NULL){
        ret = E_NOT_OK;
    }else{
        for(uint8 i = 0; i < ECU_LED_MATRIX_ROWS; i++){
            column = columns[i];
            
            for (uint8_t m = 0; m < ECU_LED_MATRIX_COLUMNS; m++) {
                ret &= GPIO_PIN_WRITE_LOGIC(&(led_matrix->LED_MATRIX_COLUMN_PINS[m]), GPIO_LOW);
            }
            
            for (uint8_t m = 0; m < ECU_LED_MATRIX_ROWS; m++) {
                ret &= GPIO_PIN_WRITE_LOGIC(&(led_matrix->LED_MATRIX_ROW_PINS[m]), GPIO_HIGH);
            }
            
            ret &= GPIO_PIN_WRITE_LOGIC(&(led_matrix->LED_MATRIX_ROW_PINS[i]), GPIO_LOW);
            
            for (uint8_t m = 0; m < ECU_LED_MATRIX_COLUMNS; m++) {
                ret &= GPIO_PIN_WRITE_LOGIC(&(led_matrix->LED_MATRIX_COLUMN_PINS[m]), (column >> m) & 0x01 ? GPIO_HIGH : GPIO_LOW); // LED on
            }
            
           __delay_ms(1);
            ret &= GPIO_PIN_WRITE_LOGIC(&(led_matrix->LED_MATRIX_ROW_PINS[i]), GPIO_HIGH);
        }          

    }
    return ret;
}
