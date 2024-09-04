/* 
 * File:   MCAL_INTERRUPT_MANAGER.h
 * Author: amr09
 *
 * Created on August 14, 2024, 3:40 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

#include "mcal_interrupt_cfg.h"


void TMR0_ISR(void);
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 rb4_source);
void RB5_ISR(uint8 rb5_source);
void RB6_ISR(uint8 rb6_source);
void RB7_ISR(uint8 rb7_source);
void ADC_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

