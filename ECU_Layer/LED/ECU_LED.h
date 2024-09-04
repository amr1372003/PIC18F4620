/* 
 * File:   ECU_LED.h
 * Author: amr09
 *
 * Created on September 16, 2023, 5:59 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

    #include "../../MCAL_Layer/GPIO/hal_gpio.h"
    #include "ecu_led_cfg.h"

    typedef enum{
        LED_OFF,
        LED_ON
    }led_status;

    typedef struct{
        uint8 PORT          :3;
        uint8 PIN           :3;
        uint8 LED_STATUS    :1;
        uint8 RESIRVED      :1;
    }led_t;

    std_ReturnType LED_INIT(const led_t *led);
    std_ReturnType LED_TURN_ON(const led_t *led);
    std_ReturnType LED_TURN_OFF(const led_t *led);
    std_ReturnType LED_TOGGLE(const led_t *led);

#endif	/* ECU_LED_H */

