/* 
 * File:   HAL_TMR0.c
 * Author: amr09
 *
 * Created on August 29, 2024, 12:26 PM
 */

#include "HAL_TMR0.h"

#if TMR0_INTERUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*TMR0_INTERRUPT_HANDLER) (void) = NULL;
#endif

static uint16 tmr0_preload = 0;

/**
 * 
 * @param tmr
 * @return 
 */
std_ReturnType TMR0_INIT(const tmr0_t *tmr){
    std_ReturnType ret = E_OK;
    if(NULL == tmr){
        ret = E_NOT_OK;
    }else{
        TMR0_DISABLE();
        
        if(TMR0_PRESCALER_ENABLE_CFG == tmr -> PRESCALER_ENABLE){
            TMR0_PRESCALER_ENABLE();
            T0CONbits.T0PS = tmr -> PRESCALER_VALUE;
        }else if(TMR0_PRESCALER_DISABLE_CFG == tmr -> PRESCALER_ENABLE){
            TMR0_PRESCALER_DISABLE();
        }
        
        if(TMR0_TIMER_MODE == tmr -> MODE){
            TMR0_MODE_TIMER();
        }else if(TMR0_COUNTER_MODE == tmr -> MODE){
            TMR0_MODE_COUNTER();
            if(TMR0_RISING_EDGE_CFG == tmr -> COUNTER_EDGE){
                TMR0_RISING_EDGE();
            }else if(TMR0_FALLING_EDGE_CFG == tmr -> COUNTER_EDGE){
                TMR0_FALLING_EDGE();
            }
        }
        
        if(TMR0_8BIT == tmr -> REGISTER_SIZE){
            TMR0_REGISTER_8BIT();
        }else if(TMR0_16BIT == tmr -> REGISTER_SIZE){
            TMR0_REGISTER_16BIT();
        }
            
        TMR0H = (tmr -> PRELOAD_VALUE) >> 8;
        TMR0L = (uint8)(tmr -> PRELOAD_VALUE);
        
        tmr0_preload = tmr -> PRELOAD_VALUE;
        
        #if TMR0_INTERUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
            IN_TMR0_INTERRUPT_ENABLE();
            IN_TMR0_INTERRUPT_FLAG_CLEAR();
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PRIORITY_LEVEL_ENABLE();
                if(INTERRUPT_HIGH_PRIORITY == tmr -> PRIORITY){
                    GLOBAL_INTERRUPT_H_PRIORITY_ENABLE();
                    IN_TMR0_H_PRIORITY_INTERRUPT_ENABLE();
                }else if(INTERRUPT_LOW_PRIORITY == tmr -> PRIORITY){
                    GLOBAL_INTERRUPT_L_PRIORITY_ENABLE();
                    IN_TMR0_L_PRIORITY_INTERRUPT_ENABLE();
                }else{}
            #else
                GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERPHERAL_ENABLE();
            #endif
            TMR0_INTERRUPT_HANDLER = tmr -> TMR0_INTERRUBT_HANDLER;
        #endif
            
        TMR0_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param tmr
 * @return 
 */
std_ReturnType TMR0_DEINIT(const tmr0_t *tmr){
    std_ReturnType ret = E_OK;
    if(NULL == tmr){
        ret = E_NOT_OK;
    }else{
        TMR0_DISABLE();
        #if TMR0_INTERUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
            IN_TMR0_INTERRUPT_DISENABLE();
        #endif
    }
    return ret;
}

/**
 * 
 * @param tmr
 * @param value
 * @return 
 */
std_ReturnType TMR0_WRITE(const tmr0_t *tmr, uint16 value){
    std_ReturnType ret = E_OK;
    if(NULL == tmr){
        ret = E_NOT_OK;
    }else{
        TMR0H = (value) >> 8;
        TMR0L = (uint8)(value);
    }
    return ret;
}

/**
 * 
 * @param tmr
 * @param value
 * @return 
 */
std_ReturnType TMR0_READ(const tmr0_t *tmr, uint16 *value){
    std_ReturnType ret = E_OK;
    if(NULL == tmr || NULL == value){
        ret = E_NOT_OK;
    }else{
        uint8 tmr0l_l = TMR0L, tmr0h_l = TMR0H;
        *value = (uint16)((tmr0h_l << 8) + tmr0l_l);
    }
    return ret;
}


void TMR0_ISR(void){
    IN_TMR0_INTERRUPT_FLAG_CLEAR();
    TMR0H = ((tmr0_preload) >> 8);
    TMR0L = (uint8)(tmr0_preload);
    if(TMR0_INTERRUPT_HANDLER){
        TMR0_INTERRUPT_HANDLER();
    }
}