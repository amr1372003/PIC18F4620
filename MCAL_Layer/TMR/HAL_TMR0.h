/* 
 * File:   HAL_TMR0.h
 * Author: amr09
 *
 * Created on August 29, 2024, 12:26 PM
 */

#ifndef HAL_TMR0_H
#define	HAL_TMR0_H

    #include "../mcal_std_types.h"
    #include "../INTERUPT/MCAL_INTERNAL_INTERRUPT.h"
    #include "../GPIO/hal_gpio.h"
    #include "pic18f4620.h"


    #define TMR0_PRESCALER_ENABLE_CFG  1
    #define TMR0_PRESCALER_DISABLE_CFG 0

    #define TMR0_RISING_EDGE_CFG  1
    #define TMR0_FALLING_EDGE_CFG 0

    #define TMR0_COUNTER_MODE 0
    #define TMR0_TIMER_MODE 1

    #define TMR0_8BIT 1
    #define TMR0_16BIT 0


    #define TMR0_PRESCALER_ENABLE()  (T0CONbits.PSA == 0)
    #define TMR0_PRESCALER_DISABLE() (T0CONbits.PSA == 1)

    #define TMR0_RISING_EDGE()  (T0CONbits.T0SE == 0)
    #define TMR0_FALLING_EDGE() (T0CONbits.T0SE == 1)

    #define TMR0_MODE_COUNTER()  (T0CONbits.T0CS == 1)
    #define TMR0_MODE_TIMER() (T0CONbits.T0CS == 0)

    #define TMR0_REGISTER_8BIT()  (T0CONbits.T08BIT == 1)
    #define TMR0_REGISTER_16BIT() (T0CONbits.T08BIT == 0)

    #define TMR0_ENABLE()  (T0CONbits.TMR0ON == 1)
    #define TMR0_DISABLE() (T0CONbits.TMR0ON == 0)


    typedef enum{
        PRESCALER_2 = 0,
        PRESCALER_4,
        PRESCALER_8,
        PRESCALER_16,
        PRESCALER_32,
        PRESCALER_64,
        PRESCALER_128,
        PRESCALER_256
    }tmr0_prescaler_t;


    typedef struct{
        #if TMR0_INTERUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
            void(* TMR0_INTERRUBT_HANDLER)(void);
            interrubt_priority PRIORITY;
        #endif
        tmr0_prescaler_t PRESCALER_VALUE;
        uint16 PRELOAD_VALUE;
        uint8 PRESCALER_ENABLE : 1;
        uint8 COUNTER_EDGE : 1;
        uint8 MODE : 1;
        uint8 REGISTER_SIZE : 1;
        uint8 RESERVED : 4;
    }tmr0_t;


    std_ReturnType TMR0_INIT(const tmr0_t *tmr);
    std_ReturnType TMR0_DEINIT(const tmr0_t *tmr);
    std_ReturnType TMR0_WRITE(const tmr0_t *tmr, uint16 value);
    std_ReturnType TMR0_READ(const tmr0_t *tmr, uint16 *value);

#endif	/* HAL_TMR0_H */

