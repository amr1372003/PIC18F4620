/* 
 * File:   hal_gpio.c
 * Author: amr09
 *
 * Created on September 16, 2023, 5:25 PM
 */
#include "hal_gpio.h"

/* Reference to the Data Direction Control Registers */
volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/* Reference to the Data Latch Register (Read and Write to Data Latch) */
volatile uint8 *lat_registers[]  = {&LATA, &LATB, &LATC, &LATD, &LATE};
/* Reference to the Port Status Register  */
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/**
 * @brief Initialize the direction of a specific pin @ref direction_t
 * @param pin_config pointer to the configurations @ref pin_config_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIG == CONFIG_ENABLE
    std_ReturnType GPIO_PIN_DIRECTION_INITIALIZE(const pin_config_t *pin_config){
        std_ReturnType ret = E_OK;
        if(NULL == pin_config || (PORT_PIN_MAX_NUM - 1) < pin_config -> PIN){
            ret = E_NOT_OK;
        }else{
            switch(pin_config -> DIRECTION){
                case GPIO_DIRECTION_OUTPUT:
                    CLEAR_BIT(*tris_registers[pin_config -> PORT], pin_config -> PIN);
                    break;
                case GPIO_DIRECTION_INPUT:
                    SET_BIT(*tris_registers[pin_config -> PORT], pin_config -> PIN);
                    break;
                default:
                    ret = E_NOT_OK;
            }
        }
        return ret;
    }
#endif

/**
 * 
 * @param pin_config pointer to the configurations @ref pin_config_t 
 * @param direction_status
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
#if GPIO_PORT_PIN_CONFIG == CONFIG_ENABLE
    std_ReturnType GPIO_PIN_GIT_DIRECTION_INITIALIZE(const pin_config_t *pin_config, direction_t *direction_stat){
        std_ReturnType ret = E_OK;
        if(NULL == pin_config || NULL == direction_stat || (PORT_PIN_MAX_NUM - 1) < pin_config -> PIN){
            ret = E_NOT_OK;
        }else{
            *direction_stat = READ_BIT(*tris_registers[pin_config -> PORT], pin_config -> PIN);
        }
        return ret;
    }
#endif

/**
 * 
 * @param pin_config_config PINTER TO THE CONFIGURATIONS @ref pin_config_t
 * @param logic
 * @return status of the function:
 *          (E_OK)      :FUN. SUCC.
 *          (E_NOT_OK)  :FUN. NOT SUCC.
 */
#if GPIO_PORT_PIN_CONFIG == CONFIG_ENABLE
    std_ReturnType GPIO_PIN_WRITE_LOGIC(const pin_config_t *pin_config, logic_t logic){
        std_ReturnType ret = E_OK;
        if(NULL == pin_config || (PORT_PIN_MAX_NUM - 1) < pin_config -> PIN){
            ret = E_NOT_OK;
        }else{
            switch(logic){
                case GPIO_LOW:
                    CLEAR_BIT(*lat_registers[pin_config -> PORT], pin_config -> PIN);
                    break;
                case GPIO_HIGH:
                    SET_BIT(*lat_registers[pin_config -> PORT], pin_config -> PIN);
                    break;
                default:
                    ret = E_NOT_OK;
            }
        }
        return ret;
    }
#endif

/**
 * 
 * @param pin_config_config PINTER TO THE CONFIGURATIONS @ref pin_config_t
 * @param logic
 * @return status of the function:
 *          (E_OK)      :FUN. SUCC.
 *          (E_NOT_OK)  :FUN. NOT SUCC.
 */
#if GPIO_PORT_PIN_CONFIG == CONFIG_ENABLE
    std_ReturnType GPIO_PIN_READ_LOGIC(const pin_config_t *pin_config, logic_t *logic){
        std_ReturnType ret = E_OK;
        if(NULL == pin_config || NULL == logic || (PORT_PIN_MAX_NUM - 1) < pin_config -> PIN){
            ret = E_NOT_OK;
        }else{
            *logic = READ_BIT(*port_registers[pin_config -> PORT], pin_config -> PIN);
        }
        return ret;
    }
#endif

/**
 * 
 * @param pin_config_config PINTER TO THE CONFIGURATIONS @ref pin_config_t
 * @return status of the function:
 *          (E_OK)      :FUN. SUCC.
 *          (E_NOT_OK)  :FUN. NOT SUCC.
 */
#if GPIO_PORT_PIN_CONFIG == CONFIG_ENABLE
    std_ReturnType GPIO_PIN_TOGGLE_LOGIC(const pin_config_t *pin_config){
        std_ReturnType ret = E_OK;
        if(NULL == pin_config || (PORT_PIN_MAX_NUM - 1) < pin_config -> PIN){
            ret = E_NOT_OK;
        }else{
            TOGGLE_BIT(*lat_registers[pin_config -> PORT], pin_config -> PIN);
        }
        return ret;
    }
#endif

/**
 * 
 * @param pin_config_config PINTER TO THE CONFIGURATIONS @ref pin_config_t
 * @return status of the function:
 *          (E_OK)      :FUN. SUCC.
 *          (E_NOT_OK)  :FUN. NOT SUCC.
 */    
#if GPIO_PORT_PIN_CONFIG == CONFIG_ENABLE
    std_ReturnType GPIO_PIN_INITIALIZE(const pin_config_t *pin_config){
        std_ReturnType ret = E_OK;
        if(NULL == pin_config || (PORT_PIN_MAX_NUM - 1) < pin_config -> PIN){
            ret = E_NOT_OK;
        }else{
            ret = GPIO_PIN_DIRECTION_INITIALIZE(pin_config);
            ret = GPIO_PIN_WRITE_LOGIC(pin_config, pin_config -> LOGIC);
        }
        return ret;
    }
#endif

/**
 * 
 * @param port
 * @param direction_stat
 * @return status of the function:
 *          (E_OK)      :FUN. SUCC.
 *          (E_NOT_OK)  :FUN. NOT SUCC. 
 */
#if GPIO_PORT_CONFIG == CONFIG_ENABLE
    std_ReturnType GPIO_PORT_DIRECTION_INITIALIZE(port_index_t port, uint8 direction_stat){
        std_ReturnType ret = E_OK;
        if(PORT_MAX_NUM - 1 < port){
            ret = E_NOT_OK;
        }else{
            *tris_registers[port] = direction_stat;
        }
        return ret;
    }
#endif

/**
 * 
 * @param port
 * @param direction_stat
 * @return status of the function:
 *          (E_OK)      :FUN. SUCC.
 *          (E_NOT_OK)  :FUN. NOT SUCC.
 */
#if GPIO_PORT_CONFIG == CONFIG_ENABLE
    std_ReturnType GPIO_PORT_GET_DIRECTION_INITIALIZE(port_index_t port, uint8 *direction_stat){
        std_ReturnType ret = E_OK;
        if(NULL == direction_stat || PORT_MAX_NUM - 1 < port){
            ret = E_NOT_OK;
        }else{
            *direction_stat = *tris_registers[port];
        }
        return ret;
    }
#endif

/**
 * 
 * @param port
 * @param logic
 * @return status of the function:
 *          (E_OK)      :FUN. SUCC.
 *          (E_NOT_OK)  :FUN. NOT SUCC.
 */
#if GPIO_PORT_CONFIG == CONFIG_ENABLE
    std_ReturnType GPIO_PORT_WRITE_LOGIC(port_index_t port, uint8 logic){
        std_ReturnType ret = E_OK;
        if(PORT_MAX_NUM - 1 < port){
            ret = E_NOT_OK;
        }else{
            *lat_registers[port] = logic;
        }
        return ret;
    }
#endif

/**
 * 
 * @param port
 * @param logic
 * @return status of the function:
 *          (E_OK)      :FUN. SUCC.
 *          (E_NOT_OK)  :FUN. NOT SUCC. 
 */
#if GPIO_PORT_CONFIG == CONFIG_ENABLE
    std_ReturnType GPIO_PORT_READ_LOGIC(port_index_t port, uint8 *logic){
        std_ReturnType ret = E_OK;
        if(NULL == logic || PORT_MAX_NUM - 1 < port){
            ret = E_NOT_OK;
        }else{
            *logic = *lat_registers[port];
        }
        return ret;
    }
#endif

/**
 * 
 * @param port
 * @return status of the function:
 *          (E_OK)      :FUN. SUCC.
 *          (E_NOT_OK)  :FUN. NOT SUCC.
 */
#if GPIO_PORT_CONFIG == CONFIG_ENABLE
    std_ReturnType GPIO_PORT_TOGGLE_LOGIC(port_index_t port){
        std_ReturnType ret = E_OK;
        if(PORT_MAX_NUM - 1 < port){
            ret = E_NOT_OK;
        }else{
            *lat_registers[port] ^= 0XFF;
        }
        return ret;
    }
#endif
