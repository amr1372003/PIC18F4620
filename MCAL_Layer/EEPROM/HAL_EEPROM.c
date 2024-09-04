/* 
 * File:   HAL_EEPROM.c
 * Author: amr09
 *
 * Created on August 22, 2024, 12:34 PM
 */

#include "HAL_EEPROM.h"

/**
 * 
 * @param add
 * @param data
 * @return 
 */
std_ReturnType DATA_EEPROM_WRITEBYTE(uint16 add, uint8 data){
    std_ReturnType ret = E_OK;
    uint8 global_inturrupt_stat = INTCONbits.GIE;
    EEADRH = (uint8)((add >> 8) & 0x03);
    EEADR = (uint8)((add) & 0xff);
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_LEVEL_DISABLE();
        GLOBAL_INTERRUPT_H_PRIORITY_DISABLE();
        GLOBAL_INTERRUPT_L_PRIORITY_DISABLE();
    #else
        GLOBAL_INTERRUPT_DISABLE();
    #endif
    EECON2 = 0X55;
    EECON2 = 0XAA;
    EECON1bits.WR = 1;
    while(EECON1bits.WR);//wait for the write to compleat
    EECON1bits.WREN = 0;
    INTCONbits.GIE = global_inturrupt_stat;
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_LEVEL_ENABLE();
        GLOBAL_INTERRUPT_H_PRIORITY_ENABLE();
        GLOBAL_INTERRUPT_L_PRIORITY_ENABLE();
    #endif
    return ret;
}

/**
 * 
 * @param add
 * @param data
 * @return 
 */
std_ReturnType DATA_EEPROM_READBYTE(uint16 add, uint8 *data){
    std_ReturnType ret = E_OK;
        if(NULL == data){
            ret = E_NOT_OK;
        }else{
            EEADRH = (uint8)((add >> 8) & 0x03);
            EEADR = (uint8)((add) & 0xff);
            EECON1bits.EEPGD = 0;
            EECON1bits.CFGS = 0;
            EECON1bits.RD = 1;
            NOP(); // for high frequances
            NOP(); // for high frequances
            *data = EEDATA;
        }
    return ret;
}