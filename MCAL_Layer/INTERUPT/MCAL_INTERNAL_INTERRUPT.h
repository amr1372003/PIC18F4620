/* 
 * File:   MCAL_INTERNAL_INTERRUPT.h
 * Author: amr09
 *
 * Created on August 14, 2024, 3:44 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

    #include "mcal_interrupt_cfg.h"

    #if ADC_INTERUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
        #define IN_ADC_INTERRUPT_ENABLE()                         (PIE1bits.ADIE = 1)
        #define IN_ADC_INTERRUPT_DISENABLE()                      (PIE1bits.ADIE = 0)
        #define IN_ADC_INTERRUPT_FLAG_CLEAR()                     (PIR1bits.ADIF = 0)

        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            #define IN_ADC_H_PRIORITY_INTERRUPT_ENABLE()          (IPR1bits.ADIP = 1)
            #define IN_ADC_L_PRIORITY_INTERRUPT_ENABLE()          (IPR1bits.ADIP = 0)
        #endif
    #endif


    #if TMR0_INTERUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
        #define IN_TMR0_INTERRUPT_ENABLE()                         (INTCONbits.TMR0IE = 1)
        #define IN_TMR0_INTERRUPT_DISENABLE()                      (INTCONbits.TMR0IE = 0)
        #define IN_TMR0_INTERRUPT_FLAG_CLEAR()                     (INTCONbits.T0IF = 0)

        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            #define IN_TMR0_H_PRIORITY_INTERRUPT_ENABLE()          (INTCON2bits.TMR0IP = 1)
            #define IN_TMR0_L_PRIORITY_INTERRUPT_ENABLE()          (INTCON2bits.TMR0IP = 0)
        #endif
    #endif

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

