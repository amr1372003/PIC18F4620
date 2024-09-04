/* 
 * File:   HAL_ADC.h
 * Author: amr09
 *
 * Created on August 25, 2024, 1:10 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

    #include "pic18f4620.h"
    #include "../INTERUPT/MCAL_INTERNAL_INTERRUPT.h"
    #include "../mcal_std_types.h"
    #include "../GPIO/hal_gpio.h"
    #include "hal_adc_cfg.h"


    #define ADC_RESULT_RIGHT                   0X01
    #define ADC_RESULT_LEFT                    0X00
    #define ADC_ENABLE_VOLTAGE_REFRANCE_ENABLE 0X01
    #define ADC_ENABLE_VOLTAGE_REFRANCE_DISABLE 0X00

    #define ADC_CONVERSION_STAT()              (ADCON0bits.GO_nDONE)
    #define _ADC_START_CONVERSION()             (ADCON0bits.GODONE = 1)
    
    #define ADC_CONVERTER_ENABLE()             (ADCON0bits.ADON = 1)
    #define ADC_CONVERTER_DISABLE()            (ADCON0bits.ADON = 0)

    /* voltage reference is VREF- AND VREF+ on bin AN2, AN3*/
    #define ADC_ENABLE_VOLTAGE_REFRANCE()      do{\
                                                ADCON1bits.VCFG0 = 1;\
                                                ADCON1bits.VCFG1 = 1;\
                                                }while(0);
                                                
    /* voltage reference is VDD AND VSS  5 volt */
    #define ADC_DISABLE_VOLTAGE_REFRANCE()     do{\
                                                ADCON1bits.VCFG0 = 0;\
                                                ADCON1bits.VCFG1 = 0;\
                                                }while(0);


    /* note that by enabling an analog bit each analog bin before it will be enabled ex(AN4 will enable AN0, AN1, AN2, AN3, AN4) */
    #define ADC_AN0_ANALOG_ENABLE               0X0E
    #define ADC_AN1_ANALOG_ENABLE               0X0D
    #define ADC_AN2_ANALOG_ENABLE               0X0C
    #define ADC_AN3_ANALOG_ENABLE               0X0B
    #define ADC_AN4_ANALOG_ENABLE               0X0A
    #define ADC_AN5_ANALOG_ENABLE               0X09
    #define ADC_AN6_ANALOG_ENABLE               0X08
    #define ADC_AN7_ANALOG_ENABLE               0X07
    #define ADC_AN8_ANALOG_ENABLE               0X06
    #define ADC_AN9_ANALOG_ENABLE               0X05
    #define ADC_AN10_ANALOG_ENABLE              0X04
    #define ADC_AN11_ANALOG_ENABLE              0X03
    /* to enable all bins from bin AN12 TO AN0 */
    #define ADC_ANx_ANALOG_ENABLE               0X00
    /* to disable all bins from bin AN12 TO AN0 */
    #define ADC_ANx_ANALOG_DISABLLE             0X0F

    #define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG)     (ADCON1bits.PCFG = _CONFIG)

    #define ADC_RIGHT_JUSTIFIED_RESULT_FORMAT()         (ADCON2bits.ADFM = 1) //recomende 
    #define ADC_LEFT_JUSTIFIED_RESULT_FORMAT()          (ADCON2bits.ADFM = 0)


    typedef enum{
        ADC_0TAD = 0,
        ADC_2TAD,
        ADC_4TAD,
        ADC_6TAD,
        ADC_8TAD,
        ADC_12TAD,
        ADC_16TAD,
        ADC_20TAD,
    }adc_acquisition_time_t;

    typedef enum{
        ADC_FOSC_2 = 0,
        ADC_FOSC_8,
        ADC_FOSC_32,
        ADC_FRC,
        ADC_FOSC_4,
        ADC_FOSC_16,
        ADC_FOSC_64,
    }adc_conversion_clock_t;

    typedef enum{
        CHANNEL_AN0 = 0,
        CHANNEL_AN1,
        CHANNEL_AN2,
        CHANNEL_AN3,
        CHANNEL_AN4,
        CHANNEL_AN5,
        CHANNEL_AN6,
        CHANNEL_AN7,
        CHANNEL_AN8,
        CHANNEL_AN9,
        CHANNEL_AN10,
        CHANNEL_AN11,
        CHANNEL_AN12,
    }adc_channel_select_t;

    typedef struct{
        #if ADC_INTERUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
            void(* ADC_INTERRUBT_HANDLER)(void);
            interrubt_priority PRIORITY;
        #endif
        adc_channel_select_t CHANNAL;
        adc_conversion_clock_t CLOCK;
        adc_acquisition_time_t ACQUISITION_TIME;
        uint8 VOLTAGE_REF      :1;
        uint8 RESULT_FORMAT    :1;
        uint8 RESERVED_BITS    :6;
    }adc_cfg_t;


    std_ReturnType ADC_INIT(const adc_cfg_t *adc);
    std_ReturnType ADC_DEINIT(const adc_cfg_t *adc);
    std_ReturnType ADC_SELECT_CHANNEL(const adc_cfg_t *adc, adc_channel_select_t channel);
    std_ReturnType ADC_START_CONVERSION(const adc_cfg_t *adc);
    std_ReturnType ADC_GET_CONVERSION_RESULT(const adc_cfg_t *adc, uint16 *result);
    std_ReturnType ADC_GET_CONVERSION_BY_CHANNAL_BLOKING(const adc_cfg_t *adc, adc_channel_select_t channel, uint16 *result);
    std_ReturnType ADC_GET_CONVERSION_BY_CHANNAL(const adc_cfg_t *adc, adc_channel_select_t channel);

#endif	/* HAL_ADC_H */

