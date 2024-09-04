/* 
 * File:   ECU_RELAY.h
 * Author: amr09
 *
 * Created on July 21, 2024, 5:33 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

    #include "../../MCAL_Layer/GPIO/hal_gpio.h"
    #include "ecu_relay_cfg.h"

    
    #define RELAY_OFF  0
    #define RELAY_ON   1
    

    typedef struct{
        uint8 PORT      :4;
        uint8 PIN       :3;
        uint8 STAT      :1;
    }relay_t;

    std_ReturnType RELAY_INIT(const relay_t *relay);
    std_ReturnType RELAY_TURN_ON(const relay_t *relay);
    std_ReturnType RELAY_TURN_OFF(const relay_t *relay);

#endif	/* ECU_RELAY_H */

