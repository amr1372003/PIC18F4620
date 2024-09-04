/* 
 * File:   ECU_DC_MOTOR.h
 * Author: amr09
 *
 * Created on July 23, 2024, 1:20 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

    #include "../../MCAL_Layer/GPIO/hal_gpio.h"
    #include "ecu_dc_motor_cfg.h"

    #define DC_MOTOR_OFF  0
    #define DC_MOTOR_ON   1

    typedef struct{
        pin_config_t DC_MOTOR[2];
    }dc_motor_t;

    std_ReturnType DC_MOTOR_INIT(const dc_motor_t *dc_motor);
    std_ReturnType DC_MOTOR_MOVE_RIGHT(const dc_motor_t *dc_motor);
    std_ReturnType DC_MOTOR_MOVE_LEFT(const dc_motor_t *dc_motor);
    std_ReturnType DC_MOTOR_STOP(const dc_motor_t *dc_motor);

#endif	/* ECU_DC_MOTOR_H */

