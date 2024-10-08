/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: amr09
 *
 * Created on August 14, 2024, 7:36 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

#define INTERRUPT_FEATURE_ENABLE                     1
//#define INTERRUPT_PRIORITY_LEVELS_ENABLE             INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE       INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_ONCHANGE_FEATURE_ENABLE   INTERRUPT_FEATURE_ENABLE

#define ADC_INTERUPT_ENABLE                          INTERRUPT_FEATURE_ENABLE

#define TMR0_INTERUPT_ENABLE                         INTERRUPT_FEATURE_ENABLE

#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

