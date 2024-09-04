/* 
 * File:   hal_gpio.h
 * Author: amr09
 *
 * Created on September 16, 2023, 5:36 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

    #include "pic18f4620.h"
    #include "../mcal_std_types.h"
    #include "../device_config.h"
    #include "hal_gpio_cfg.h"

    #define BIT_MASK (uint8)1

    #define PORT_PIN_MAX_NUM 8
    #define PORT_MAX_NUM 5

    #define HWREG8(_x) (*(volatile unsigned char *)(_x))

    #define SET_BIT(REG, BIT_POS)       (REG |= (BIT_MASK << BIT_POS))
    #define CLEAR_BIT(REG, BIT_POS)     (REG &= ~(BIT_MASK << BIT_POS))
    #define TOGGLE_BIT(REG, BIT_POS)    (REG ^= (BIT_MASK << BIT_POS))
    #define READ_BIT(REG, BIT_POS)      ((REG >> BIT_POS) & (BIT_MASK))


    typedef enum{
        GPIO_LOW = 0,
        GPIO_HIGH
    }logic_t;

    typedef enum{
        GPIO_DIRECTION_OUTPUT = 0,
        GPIO_DIRECTION_INPUT
    }direction_t;

    typedef enum{
        PIN0 = 0,
        PIN1,
        PIN2,
        PIN3,
        PIN4,
        PIN5,
        PIN6,
        PIN7
    }pin_index_t;
    
    typedef enum{
        PORTA_INDEX = 0,
        PORTB_INDEX,
        PORTC_INDEX,
        PORTD_INDEX,
        PORTE_INDEX
    }port_index_t;
    
    typedef struct{
        uint8 PORT              :3; /*@ref port_index_t*/
        uint8 PIN               :3; /*@ref pin_index_t*/
        uint8 DIRECTION         :1; /*@ref direction_t*/
        uint8 LOGIC             :1; /*@ref logic_t*/
    }pin_config_t;

    
    std_ReturnType GPIO_PIN_DIRECTION_INITIALIZE(const pin_config_t *pin_config);
    std_ReturnType GPIO_PIN_GIT_DIRECTION_INITIALIZE(const pin_config_t *pin_config, direction_t *direction_stat);
    std_ReturnType GPIO_PIN_WRITE_LOGIC(const pin_config_t *pin_config, logic_t logic);
    std_ReturnType GPIO_PIN_READ_LOGIC(const pin_config_t *pin_config, logic_t *logic);
    std_ReturnType GPIO_PIN_TOGGLE_LOGIC(const pin_config_t *pin_config);
    std_ReturnType GPIO_PIN_INITIALIZE(const pin_config_t *pin_config);
    
    std_ReturnType GPIO_PORT_DIRECTION_INITIALIZE(port_index_t port, uint8 direction_stat);
    std_ReturnType GPIO_PORT_GET_DIRECTION_INITIALIZE(port_index_t port, uint8 *direction_stat);
    std_ReturnType GPIO_PORT_WRITE_LOGIC(port_index_t port, uint8 logic);
    std_ReturnType GPIO_PORT_READ_LOGIC(port_index_t port, uint8 *logic);
    std_ReturnType GPIO_PORT_TOGGLE_LOGIC(port_index_t port);
    


#endif	/* HAL_GPIO_H */