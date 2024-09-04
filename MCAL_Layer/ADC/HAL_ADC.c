/* 
 * File:   HAL_ADC.c
 * Author: amr09
 *
 * Created on August 25, 2024, 1:10 PM
 */

#include "HAL_ADC.h"


#if ADC_INTERUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*ADC_INTERRUBT_HANDLER) (void) = NULL;
#endif
    
static inline std_ReturnType ADC_INPUT_CHANNEL_PORT_CFG(const adc_channel_select_t channel);

/**
 * 
 * @param adc
 * @return 
 */
std_ReturnType ADC_INIT(const adc_cfg_t *adc){
    std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }else{
        ADC_CONVERTER_DISABLE();
        ADCON2bits.ACQT = adc -> ACQUISITION_TIME;
        ADCON2bits.ADCS = adc -> CLOCK;
        ADCON0bits.CHS = adc -> CHANNAL;
        ADC_INPUT_CHANNEL_PORT_CFG(adc -> CHANNAL);
        
        #if ADC_INTERUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
            IN_ADC_INTERRUPT_ENABLE();
            IN_ADC_INTERRUPT_FLAG_CLEAR();
            #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PRIORITY_LEVEL_ENABLE();
                if(INTERRUPT_HIGH_PRIORITY == adc -> PRIORITY){
                    GLOBAL_INTERRUPT_H_PRIORITY_ENABLE();
                    IN_ADC_H_PRIORITY_INTERRUPT_ENABLE();
                }else if(INTERRUPT_LOW_PRIORITY == adc -> PRIORITY){
                    GLOBAL_INTERRUPT_L_PRIORITY_ENABLE();
                    IN_ADC_L_PRIORITY_INTERRUPT_ENABLE();
                }else{}
            #else
                GLOBAL_INTERRUPT_ENABLE();
                INTERRUPT_PERPHERAL_ENABLE();
            #endif
            ADC_INTERRUBT_HANDLER = adc -> ADC_INTERRUBT_HANDLER;
        #endif
        
        if(ADC_RESULT_RIGHT == adc -> RESULT_FORMAT){
            ADC_RIGHT_JUSTIFIED_RESULT_FORMAT();
        }else if(ADC_RESULT_LEFT == adc -> RESULT_FORMAT){
            ADC_LEFT_JUSTIFIED_RESULT_FORMAT();
        } else{
            ADC_RIGHT_JUSTIFIED_RESULT_FORMAT();
        }
        
        if(ADC_ENABLE_VOLTAGE_REFRANCE_ENABLE == adc -> VOLTAGE_REF){
            ADC_ENABLE_VOLTAGE_REFRANCE();
        }else if (ADC_ENABLE_VOLTAGE_REFRANCE_DISABLE == adc -> VOLTAGE_REF){
            ADC_DISABLE_VOLTAGE_REFRANCE();
        } else{
            ADC_DISABLE_VOLTAGE_REFRANCE();
        }
        
        ADC_CONVERTER_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param adc
 * @return 
 */
std_ReturnType ADC_DEINIT(const adc_cfg_t *adc){
    std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }else{
        ADC_CONVERTER_DISABLE();
        #if ADC_INTERUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
            IN_ADC_INTERRUPT_DISENABLE();
        #endif
    }
    return ret;
}

/**
 * 
 * @param adc
 * @param channel
 * @return 
 */
std_ReturnType ADC_SELECT_CHANNEL(const adc_cfg_t *adc, const adc_channel_select_t channel){
    std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }else{
        ADCON0bits.CHS = channel;
        ret = ADC_INPUT_CHANNEL_PORT_CFG(channel);
    }
    return ret;
}

/**
 * 
 * @param adc
 * @return 
 */
std_ReturnType ADC_START_CONVERSION(const adc_cfg_t *adc){
    std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }else{
        _ADC_START_CONVERSION();
    }
    return ret;
}

/**
 * 
 * @param adc
 * @param result
 * @return 
 */
std_ReturnType ADC_GET_CONVERSION_RESULT(const adc_cfg_t *adc, uint16 *result){
    std_ReturnType ret = E_OK;
    if(NULL == adc || NULL == result){
        ret = E_NOT_OK;
    }else{
        if(ADC_RESULT_RIGHT == adc -> RESULT_FORMAT){
            *result = (uint16) (ADRESL + (ADRESH << 8));
        }else if(ADC_RESULT_LEFT == adc -> RESULT_FORMAT){
            *result = (uint16) ((ADRESL + (ADRESH << 8)) >> 6);
        } else{
            *result = (uint16) (ADRESL + (ADRESH << 8));
        }
    }
    return ret;
}

/**
 * 
 * @param adc
 * @param channel
 * @param result
 * @return 
 */
std_ReturnType ADC_GET_CONVERSION_BY_CHANNAL(const adc_cfg_t *adc, adc_channel_select_t channel){
    std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }else{
        ret = ADC_SELECT_CHANNEL(adc, channel);
        ret = ADC_START_CONVERSION(adc);
    }
    return ret;
}

/**
 * 
 * @param adc
 * @param channel
 * @param result
 * @return 
 */
std_ReturnType ADC_GET_CONVERSION_BY_CHANNAL_BLOKING(const adc_cfg_t *adc, adc_channel_select_t channel, uint16 *result){
    std_ReturnType ret = E_OK;
    if(NULL == adc || NULL == result){
        ret = E_NOT_OK;
    }else{
        ret = ADC_SELECT_CHANNEL(adc, channel);
        ret = ADC_START_CONVERSION(adc);
        while(ADC_CONVERSION_STAT());
        ret = ADC_GET_CONVERSION_RESULT(adc, result);
    }
    return ret;
}

/**
 * 
 * @param channel
 * @return 
 */
static inline std_ReturnType ADC_INPUT_CHANNEL_PORT_CFG(const adc_channel_select_t channel){
     std_ReturnType ret = E_OK;
    switch(channel){
        case ADC_AN0_ANALOG_ENABLE: 
            SET_BIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_AN1_ANALOG_ENABLE: 
            SET_BIT(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_AN2_ANALOG_ENABLE: 
            SET_BIT(TRISA, _TRISA_RA2_POSN);
            break;
        case ADC_AN3_ANALOG_ENABLE: 
            SET_BIT(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_AN4_ANALOG_ENABLE: 
            SET_BIT(TRISA, _TRISA_RA5_POSN);
            break;
        case ADC_AN5_ANALOG_ENABLE: 
            SET_BIT(TRISE, _TRISE_RE0_POSN);
            break;
        case ADC_AN6_ANALOG_ENABLE: 
            SET_BIT(TRISE, _TRISE_RE1_POSN);
            break;
        case ADC_AN7_ANALOG_ENABLE: 
            SET_BIT(TRISE, _TRISE_RE2_POSN);
            break;
        case ADC_AN8_ANALOG_ENABLE: 
            SET_BIT(TRISB, _TRISB_RB2_POSN);
            break;
        case ADC_AN9_ANALOG_ENABLE: 
            SET_BIT(TRISB, _TRISB_RB3_POSN);
            break;
        case ADC_AN10_ANALOG_ENABLE: 
            SET_BIT(TRISB, _TRISB_RB1_POSN);
            break;
        case ADC_AN11_ANALOG_ENABLE: 
            SET_BIT(TRISB, _TRISB_RB4_POSN);
            break;
        case ADC_ANx_ANALOG_ENABLE: 
            SET_BIT(TRISB, _TRISB_RB0_POSN);
            break;
        default: ret = E_NOT_OK;
    }
    return ret;
}

void ADC_ISR(void){
    IN_ADC_INTERRUPT_FLAG_CLEAR();
    if(ADC_INTERRUBT_HANDLER){
        ADC_INTERRUBT_HANDLER();
    }
}