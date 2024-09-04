/* 
 * File:   MCAL_EXTERNAL_INTERRUPT.h
 * Author: amr09
 *
 * Created on August 14, 2024, 3:42 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

    #include "mcal_interrupt_cfg.h"


    #if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        #define EXT_INT0_INTERRUPT_ENABLE()                         (INTCONbits.INT0IE = 1)
        #define EXT_INT0_INTERRUPT_DISENABLE()                      (INTCONbits.INT0IE = 0)
        #define EXT_INT0_INTERRUPT_FLAG_CLEAR()                     (INTCONbits.INT0IF = 0)
        #define EXT_INT0_INTERRUPT_RISING_EDGE_SET()                (INTCON2bits.INTEDG0 = 1)
        #define EXT_INT0_INTERRUPT_FALLING_EDGE_SET()               (INTCON2bits.INTEDG0 = 0)

        #define EXT_INT1_INTERRUPT_ENABLE()                         (INTCON3bits.INT1IE = 1)
        #define EXT_INT1_INTERRUPT_DISENABLE()                      (INTCON3bits.INT1IE = 0)
        #define EXT_INT1_INTERRUPT_FLAG_CLEAR()                     (INTCON3bits.INT1IF = 0)
        #define EXT_INT1_INTERRUPT_RISING_EDGE_SET()                (INTCON2bits.INTEDG1 = 1)
        #define EXT_INT1_INTERRUPT_FALLING_EDGE_SET()               (INTCON2bits.INTEDG1 = 0)

        #define EXT_INT2_INTERRUPT_ENABLE()                         (INTCON3bits.INT2IE = 1)
        #define EXT_INT2_INTERRUPT_DISENABLE()                      (INTCON3bits.INT2IE = 0)
        #define EXT_INT2_INTERRUPT_FLAG_CLEAR()                     (INTCON3bits.INT2IF = 0)
        #define EXT_INT2_INTERRUPT_RISING_EDGE_SET()                (INTCON2bits.INTEDG1 = 1)
        #define EXT_INT2_INTERRUPT_FALLING_EDGE_SET()               (INTCON2bits.INTEDG1 = 0)

        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            #define EXT_INT1_H_PRIORITY_INTERRUPT_ENABLE()          (INTCON3bits.INT1IP = 1)
            #define EXT_INT1_L_PRIORITY_INTERRUPT_ENABLE()       (INTCON3bits.INT1IP = 0)

            #define EXT_INT2_H_PRIORITY_INTERRUPT_ENABLE()          (INTCON3bits.INT2IP = 1)
            #define EXT_INT2_L_PRIORITY_INTERRUPT_ENABLE()       (INTCON3bits.INT2IP = 0)
        #endif
    #endif


    #if EXTERNAL_INTERRUPT_ONCHANGE_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        #define EXT_RBx_INTERRUPT_ENABLE()                      (INTCONbits.RBIE = 1)
        #define EXT_RBx_INTERRUPT_DISENABLE()                   (INTCONbits.RBIE = 0)
        #define EXT_RBx_INTERRUPT_FLAG_CLEAR()                  (INTCONbits.RBIF = 0)

        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            #define EXT_RBx_H_PRIORITY_INTERRUPT_ENABLE()       (INTCON2bits.RBIP = 1)
            #define EXT_RBx_L_PRIORITY_INTERRUPT_ENABLE()       (INTCON2bits.RBIP = 0)
        #endif
    #endif


    typedef enum{
        FALLING_EDGE = 0,
        RISING_EDGE
    }interrubt_INTx_edge;
    
    typedef enum{
        EXT_INT0 = 0,
        EXT_INT1,
        EXT_INT2
    }interrubt_INTx_src;
    

    typedef struct{
        pin_config_t MCU_PIN;
        interrubt_INTx_edge EDGE;
        interrubt_INTx_src SOURCE;
        interrubt_priority PRIORITY;
        void(* EXTERNAL_INTERRUBT_HANDLER)(void);
    }interrupt_INTx_t;

    
    typedef struct{
        pin_config_t MCU_PIN;
        interrubt_priority PRIORITY;
        void(* EXTERNAL_INTERRUBT_HANDLER_HIGH)(void);
        void(* EXTERNAL_INTERRUBT_HANDLER_LOW)(void);
    }interrupt_RBx_t;


    std_ReturnType INTERRUPT_INTx_INIT(const interrupt_INTx_t *interrubt_object);
    std_ReturnType INTERRUPT_INTx_DEINIT(const interrupt_INTx_t *interrubt_object);

    std_ReturnType INTERRUPT_RBx_INIT(const interrupt_RBx_t *interrubt_object);
    std_ReturnType INTERRUPT_RBx_DEINIT(const interrupt_RBx_t *interrubt_object);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

