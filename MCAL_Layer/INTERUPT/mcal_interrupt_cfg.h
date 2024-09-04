/* 
 * File:   mcal_interrupt_cfg.h
 * Author: amr09
 *
 * Created on August 14, 2024, 3:45 PM
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H

    #include "pic18f4620.h"
    #include "../GPIO/hal_gpio.h"
    #include "../mcal_std_types.h"
    #include "mcal_interrupt_gen_cfg.h"

    #define INTERRUPT_ENABLE            1
    #define INTERRUPT_DISABLE           0
    #define INTERRUPT_OCCUR             1
    #define INTERRUPT_NOT_OCCUR         0
    #define INTERRUPT_PRIORITY_ENABLE   1
    #define INTERRUPT_PRIORITY_DISABLE  0


    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        #define INTERRUPT_PRIORITY_LEVEL_ENABLE()           (RCONbits.IPEN = 1)
        #define INTERRUPT_PRIORITY_LEVEL_DISABLE()          (RCONbits.IPEN = 0)

        #define GLOBAL_INTERRUPT_H_PRIORITY_ENABLE()        (INTCONbits.GIEH = 1)
        #define GLOBAL_INTERRUPT_H_PRIORITY_DISABLE()       (INTCONbits.GIEH = 0)

        #define GLOBAL_INTERRUPT_L_PRIORITY_ENABLE()        (INTCONbits.GIEL = 1)
        #define GLOBAL_INTERRUPT_L_PRIORITY_DISABLE()       (INTCONbits.GIEL = 0)
    #else
        #define GLOBAL_INTERRUPT_ENABLE()                   (INTCONbits.GIE = 1)
        #define GLOBAL_INTERRUPT_DISABLE()                  (INTCONbits.GIE = 0)

        #define INTERRUPT_PERPHERAL_ENABLE()                (INTCONbits.PEIE = 1)
        #define INTERRUPT_PERPHERAL_DISABLE()               (INTCONbits.PEIE = 0)
    #endif


    typedef enum{
        INTERRUPT_LOW_PRIORITY = 0,
        INTERRUPT_HIGH_PRIORITY,
    }interrubt_priority;

#endif	/* MCAL_INTERRUPT_CFG_H */

