/* 
 * File:   MCAL_EXTERNAL_INTERRUPT.c
 * Author: amr09
 *
 * Created on August 14, 2024, 3:42 PM
 */

#include "MCAL_EXTERNAL_INTERRUPT.h"

static void (*INT0_INTERRUBT_HANDLER) (void) = NULL;
static void (*INT1_INTERRUBT_HANDLER) (void) = NULL;
static void (*INT2_INTERRUBT_HANDLER) (void) = NULL;

static void (*RB4_INTERRUBT_HANDLER_HIGH) (void) = NULL;
static void (*RB4_INTERRUBT_HANDLER_LOW) (void) = NULL;
static void (*RB5_INTERRUBT_HANDLER_HIGH) (void) = NULL;
static void (*RB5_INTERRUBT_HANDLER_LOW) (void) = NULL;
static void (*RB6_INTERRUBT_HANDLER_HIGH) (void) = NULL;
static void (*RB6_INTERRUBT_HANDLER_LOW) (void) = NULL;
static void (*RB7_INTERRUBT_HANDLER_HIGH) (void) = NULL;
static void (*RB7_INTERRUBT_HANDLER_LOW) (void) = NULL;

static std_ReturnType INTERRUPT_INTx_ENABLE(const interrupt_INTx_t *interrubt_object);
static std_ReturnType INTERRUPT_INTx_DISABLE(const interrupt_INTx_t *interrubt_object);
static std_ReturnType INTERRUPT_INTx_PRIORITY_INIT(const interrupt_INTx_t *interrubt_object);
static std_ReturnType INTERRUPT_INTx_EDGE_INIT(const interrupt_INTx_t *interrubt_object);
static std_ReturnType INTERRUPT_INTx_PIN_INIT(const interrupt_INTx_t *interrubt_object);
static std_ReturnType INTERRUPT_INTx_CLEAR_FLAG(const interrupt_INTx_t *interrubt_object);

static std_ReturnType INT0_SET_INTERRUBT_HANDLER(void (*INTERRUBT_HANDLER) (void));
static std_ReturnType INT1_SET_INTERRUBT_HANDLER(void (*INTERRUBT_HANDLER) (void));
static std_ReturnType INT2_SET_INTERRUBT_HANDLER(void (*INTERRUBT_HANDLER) (void));
static std_ReturnType INTERRUPT_INTx_SET_INTERRUBT_HANDLER(const interrupt_INTx_t *interrubt_object);


static std_ReturnType INTERRUPT_RBx_ENABLE(const interrupt_RBx_t *interrubt_object);
static std_ReturnType INTERRUPT_RBx_DISABLE(const interrupt_RBx_t *interrubt_object);
static std_ReturnType INTERRUPT_RBx_PRIORITY_INIT(const interrupt_RBx_t *interrubt_object);
static std_ReturnType INTERRUPT_RBx_PIN_INIT(const interrupt_RBx_t *interrubt_object);


/**
 * 
 * @param interrubt_object
 * @return 
 */
std_ReturnType INTERRUPT_INTx_INIT(const interrupt_INTx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        ret &= INTERRUPT_INTx_DISABLE(interrubt_object);
        ret &= INTERRUPT_INTx_CLEAR_FLAG(interrubt_object);
        ret &= INTERRUPT_INTx_EDGE_INIT(interrubt_object);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            ret &= INTERRUPT_INTx_PRIORITY_INIT(interrubt_object);
        #endif
        ret &= INTERRUPT_INTx_PIN_INIT(interrubt_object);
        ret &= INTERRUPT_INTx_SET_INTERRUBT_HANDLER(interrubt_object);
        ret &= INTERRUPT_INTx_ENABLE(interrubt_object);
    }
    return ret;
}


void INT0_ISR(void){
    EXT_INT0_INTERRUPT_FLAG_CLEAR();
    if(INT0_INTERRUBT_HANDLER){
        INT0_INTERRUBT_HANDLER();
    }
}

void INT1_ISR(void){
    EXT_INT1_INTERRUPT_FLAG_CLEAR();
    if(INT1_INTERRUBT_HANDLER){
        INT1_INTERRUBT_HANDLER();
    }
}

void INT2_ISR(void){
    EXT_INT2_INTERRUPT_FLAG_CLEAR();
    if(INT2_INTERRUBT_HANDLER){
        INT2_INTERRUBT_HANDLER();
    }
}

/**
 * 
 * @param interrubt_object
 * @return 
 */
std_ReturnType INTERRUPT_INTx_DEINIT(const interrupt_INTx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        ret = INTERRUPT_INTx_DISABLE(interrubt_object);
    }
    return ret;
}

/**
 * 
 * @param interrubt_object
 * @return 
 */
std_ReturnType INTERRUPT_RBx_INIT(const interrupt_RBx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        ret &= INTERRUPT_RBx_DISABLE(interrubt_object);
        EXT_RBx_INTERRUPT_FLAG_CLEAR();
        ret &= INTERRUPT_RBx_PRIORITY_INIT(interrubt_object);
        ret &= GPIO_PIN_DIRECTION_INITIALIZE(&(interrubt_object -> MCU_PIN));
        ret &= INTERRUPT_RBx_PIN_INIT(interrubt_object);
        ret &= INTERRUPT_RBx_ENABLE(interrubt_object);
    }
    return ret;
}

void RB4_ISR(uint8 rb4_source){
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if(1 == rb4_source){
        if(RB4_INTERRUBT_HANDLER_HIGH){
            RB4_INTERRUBT_HANDLER_HIGH();
        }
    }else if(0 == rb4_source){
        if(RB4_INTERRUBT_HANDLER_LOW){
            RB4_INTERRUBT_HANDLER_LOW();
        }
    }else{}
    
}

void RB5_ISR(uint8 rb5_source){
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if(1 == rb5_source){
        if(RB5_INTERRUBT_HANDLER_HIGH){
            RB5_INTERRUBT_HANDLER_HIGH();
        }
    }else if(0 == rb5_source){
        if(RB5_INTERRUBT_HANDLER_LOW){
            RB5_INTERRUBT_HANDLER_LOW();
        }
    }else{}
}

void RB6_ISR(uint8 rb6_source){
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if(1 == rb6_source){
        if(RB6_INTERRUBT_HANDLER_HIGH){
            RB6_INTERRUBT_HANDLER_HIGH();
        }
    }else if(0 == rb6_source){
        if(RB6_INTERRUBT_HANDLER_LOW){
            RB6_INTERRUBT_HANDLER_LOW();
        }
    }else{}
}

void RB7_ISR(uint8 rb7_source){
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if(1 == rb7_source){
        if(RB7_INTERRUBT_HANDLER_HIGH){
            RB7_INTERRUBT_HANDLER_HIGH();
        }
    }else if(0 == rb7_source){
        if(RB7_INTERRUBT_HANDLER_LOW){
            RB7_INTERRUBT_HANDLER_LOW();
        }
    }else{}
}

/**
 * 
 * @param interrubt_object
 * @return 
 */
std_ReturnType INTERRUPT_RBx_DEINIT(const interrupt_RBx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        ret = INTERRUPT_RBx_DISABLE(interrubt_object);
    }
    return ret;
}

//<---------------- HELPER FUNCTIONS ---------------->

/**
 * 
 * @param interrubt_object
 * @return 
 */
static std_ReturnType INTERRUPT_INTx_ENABLE(const interrupt_INTx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        switch(interrubt_object -> SOURCE){
            case EXT_INT0:
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PRIORITY_LEVEL_ENABLE();
                    GLOBAL_INTERRUPT_H_PRIORITY_ENABLE();
                #else
                    GLOBAL_INTERRUPT_ENABLE();
                    INTERRUPT_PERPHERAL_ENABLE();
                #endif
                EXT_INT0_INTERRUPT_ENABLE();
                break;
            case EXT_INT1: 
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PRIORITY_LEVEL_ENABLE();
                    if(interrubt_object -> PRIORITY == INTERRUPT_LOW_PRIORITY){
                        GLOBAL_INTERRUPT_L_PRIORITY_ENABLE();
                    }else if(interrubt_object -> PRIORITY == INTERRUPT_HIGH_PRIORITY){
                        GLOBAL_INTERRUPT_H_PRIORITY_ENABLE();
                    }else{}
                #else
                    GLOBAL_INTERRUPT_ENABLE();
                    INTERRUPT_PERPHERAL_ENABLE();
                #endif
                EXT_INT1_INTERRUPT_ENABLE(); 
                break;
            case EXT_INT2:
                
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PRIORITY_LEVEL_ENABLE();
                    if(interrubt_object -> PRIORITY == INTERRUPT_LOW_PRIORITY){
                        GLOBAL_INTERRUPT_L_PRIORITY_ENABLE();
                    }else if(interrubt_object -> PRIORITY == INTERRUPT_HIGH_PRIORITY){
                        GLOBAL_INTERRUPT_H_PRIORITY_ENABLE();
                    }else{}
                #else
                    GLOBAL_INTERRUPT_ENABLE();
                    INTERRUPT_PERPHERAL_ENABLE();
                #endif 
                EXT_INT2_INTERRUPT_ENABLE(); 
                break;
            default: ret = E_NOT_OK;
        };
    }
    return ret;
}

/**
 * 
 * @param interrubt_object
 * @return 
 */
static std_ReturnType INTERRUPT_INTx_DISABLE(const interrupt_INTx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        switch(interrubt_object -> SOURCE){
            case EXT_INT0: EXT_INT0_INTERRUPT_DISENABLE(); break;
            case EXT_INT1: EXT_INT1_INTERRUPT_DISENABLE(); break;
            case EXT_INT2: EXT_INT2_INTERRUPT_DISENABLE(); break;
            default: ret = E_NOT_OK;
        };
    }
    return ret;
}

/**
 * 
 * @param interrubt_object
 * @return 
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static std_ReturnType INTERRUPT_INTx_PRIORITY_INIT(const interrupt_INTx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        switch(interrubt_object -> SOURCE){
            case EXT_INT0:
                break;
            case EXT_INT1: 
                if(interrubt_object -> PRIORITY == INTERRUPT_LOW_PRIORITY){
                    EXT_INT1_L_PRIORITY_INTERRUPT_ENABLE();
                }else if(interrubt_object -> PRIORITY == INTERRUPT_HIGH_PRIORITY){
                    EXT_INT1_H_PRIORITY_INTERRUPT_ENABLE();
                }else{}
                break;
            case EXT_INT2: 
                if(interrubt_object -> PRIORITY == INTERRUPT_LOW_PRIORITY){
                    EXT_INT2_L_PRIORITY_INTERRUPT_ENABLE();
                }else if(interrubt_object -> PRIORITY == INTERRUPT_HIGH_PRIORITY){
                    EXT_INT2_H_PRIORITY_INTERRUPT_ENABLE();
                }else{}
                break;
            default: ret = E_NOT_OK;
        };
    }
    return ret;
}
#endif

/**
 * 
 * @param interrubt_object
 * @return 
 */
static std_ReturnType INTERRUPT_INTx_EDGE_INIT(const interrupt_INTx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        switch(interrubt_object -> SOURCE){
            case EXT_INT0:
                if(interrubt_object -> EDGE == RISING_EDGE){
                    EXT_INT0_INTERRUPT_RISING_EDGE_SET();
                }else if(interrubt_object -> EDGE == FALLING_EDGE){
                    EXT_INT0_INTERRUPT_FALLING_EDGE_SET();
                }else{}
                break;
            case EXT_INT1: 
                if(interrubt_object -> EDGE == RISING_EDGE){
                    EXT_INT1_INTERRUPT_RISING_EDGE_SET();
                }else if(interrubt_object -> EDGE == FALLING_EDGE){
                    EXT_INT1_INTERRUPT_FALLING_EDGE_SET();
                }else{}
                break;
            case EXT_INT2: 
                if(interrubt_object -> EDGE == RISING_EDGE){
                    EXT_INT2_INTERRUPT_RISING_EDGE_SET();
                }else if(interrubt_object -> EDGE == FALLING_EDGE){
                    EXT_INT2_INTERRUPT_FALLING_EDGE_SET();
                }else{}
                break;
            default: ret = E_NOT_OK;
        };
    }
    return ret;
}

/**
 * 
 * @param interrubt_object
 * @return 
 */
static std_ReturnType INTERRUPT_INTx_PIN_INIT(const interrupt_INTx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        ret = GPIO_PIN_DIRECTION_INITIALIZE(&(interrubt_object -> MCU_PIN));
    }
    return ret;
}

/**
 * 
 * @param interrubt_object
 * @return 
 */
static std_ReturnType INTERRUPT_INTx_CLEAR_FLAG(const interrupt_INTx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        switch(interrubt_object -> SOURCE){
            case EXT_INT0:
                EXT_INT0_INTERRUPT_FLAG_CLEAR();
                break;
            case EXT_INT1: 
                EXT_INT1_INTERRUPT_FLAG_CLEAR();
                break;
            case EXT_INT2: 
                EXT_INT2_INTERRUPT_FLAG_CLEAR();
                break;
            default: ret = E_NOT_OK;
        };
    }
    return ret;
}

static std_ReturnType INT0_SET_INTERRUBT_HANDLER(void (*INTERRUBT_HANDLER) (void)){
    std_ReturnType ret = E_OK;
    if(NULL == INTERRUBT_HANDLER){
        ret = E_NOT_OK;
    }else{
       INT0_INTERRUBT_HANDLER = INTERRUBT_HANDLER;
    }
    return ret;
}
static std_ReturnType INT1_SET_INTERRUBT_HANDLER(void (*INTERRUBT_HANDLER) (void)){
    std_ReturnType ret = E_OK;
    if(NULL == INTERRUBT_HANDLER){
        ret = E_NOT_OK;
    }else{
       INT1_INTERRUBT_HANDLER = INTERRUBT_HANDLER;
    }
    return ret;
}
static std_ReturnType INT2_SET_INTERRUBT_HANDLER(void (*INTERRUBT_HANDLER) (void)){
    std_ReturnType ret = E_OK;
    if(NULL == INTERRUBT_HANDLER){
        ret = E_NOT_OK;
    }else{
       INT2_INTERRUBT_HANDLER = INTERRUBT_HANDLER;
    }
    return ret;
}

/**
 * 
 * @param interrubt_object
 * @return 
 */
static std_ReturnType INTERRUPT_INTx_SET_INTERRUBT_HANDLER(const interrupt_INTx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        switch(interrubt_object -> SOURCE){
            case EXT_INT0:
                ret = INT0_SET_INTERRUBT_HANDLER(interrubt_object -> EXTERNAL_INTERRUBT_HANDLER);
                break;
            case EXT_INT1: 
                ret = INT1_SET_INTERRUBT_HANDLER(interrubt_object -> EXTERNAL_INTERRUBT_HANDLER);
                break;
            case EXT_INT2: 
                ret = INT2_SET_INTERRUBT_HANDLER(interrubt_object -> EXTERNAL_INTERRUBT_HANDLER);
                break;
            default: ret = E_NOT_OK;
        };
    }
    return ret;
}

/**
 * 
 * @param interrubt_object
 * @return 
 */
static std_ReturnType INTERRUPT_RBx_ENABLE(const interrupt_RBx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        EXT_RBx_INTERRUPT_ENABLE();
    }
    return ret;
}

/**
 * 
 * @param interrubt_object
 * @return 
 */
static std_ReturnType INTERRUPT_RBx_DISABLE(const interrupt_RBx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        EXT_RBx_INTERRUPT_DISENABLE();
    }
    return ret;
}

/**
 * 
 * @param interrubt_object
 * @return 
 */
static std_ReturnType INTERRUPT_RBx_PRIORITY_INIT(const interrupt_RBx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_LEVEL_ENABLE();
            if(interrubt_object -> PRIORITY == INTERRUPT_LOW_PRIORITY){
                GLOBAL_INTERRUPT_L_PRIORITY_ENABLE();
                EXT_RBx_L_PRIORITY_INTERRUPT_ENABLE();
            }else if(interrubt_object -> PRIORITY == INTERRUPT_HIGH_PRIORITY){
                GLOBAL_INTERRUPT_H_PRIORITY_ENABLE();
                EXT_RBx_H_PRIORITY_INTERRUPT_ENABLE();
            }else{}
        #else
            GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_PERPHERAL_ENABLE();
        #endif
    }
    return ret;
}


static std_ReturnType INTERRUPT_RBx_PIN_INIT(const interrupt_RBx_t *interrubt_object){
    std_ReturnType ret = E_OK;
    if(NULL == interrubt_object){
        ret = E_NOT_OK;
    }else{
        switch(interrubt_object ->MCU_PIN.PIN){
            case PIN4 :
                RB4_INTERRUBT_HANDLER_HIGH = interrubt_object -> EXTERNAL_INTERRUBT_HANDLER_HIGH;
                RB4_INTERRUBT_HANDLER_LOW = interrubt_object -> EXTERNAL_INTERRUBT_HANDLER_LOW;
                break;
            case PIN5 : 
                RB5_INTERRUBT_HANDLER_HIGH = interrubt_object -> EXTERNAL_INTERRUBT_HANDLER_HIGH;
                RB5_INTERRUBT_HANDLER_LOW = interrubt_object -> EXTERNAL_INTERRUBT_HANDLER_LOW;
                break;
            case PIN6 : 
                RB6_INTERRUBT_HANDLER_HIGH = interrubt_object -> EXTERNAL_INTERRUBT_HANDLER_HIGH;
                RB6_INTERRUBT_HANDLER_LOW = interrubt_object -> EXTERNAL_INTERRUBT_HANDLER_LOW;
                break;
            case PIN7 : 
                RB7_INTERRUBT_HANDLER_HIGH = interrubt_object -> EXTERNAL_INTERRUBT_HANDLER_HIGH;
                RB7_INTERRUBT_HANDLER_LOW = interrubt_object -> EXTERNAL_INTERRUBT_HANDLER_LOW;
                break;
            default: 
                ret = E_NOT_OK;
        }  
    }
    return ret;
}

