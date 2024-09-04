/* 
 * File:   application.c
 * Author: amr09
 *
 * Created on September 16, 2023, 5:25 PM
 */

#include "application.h"


uint8 heart[] = {0x18, 0x3c, 0x7e , 0xff, 0xff, 0xff, 0x66, 0x00};

led_t led1 = {.PORT = PORTC_INDEX, .PIN = PIN0, .LED_STATUS = GPIO_LOW};
led_t led2 = {.PORT = PORTC_INDEX, .PIN = PIN1, .LED_STATUS = GPIO_LOW};

volatile uint8 timer0_250ms_flag = 0;
volatile uint8 timer0_500ms_counter = 0;

volatile uint16 tmr0_flag = 0, val = 0;

void tmr0_handler(void) {
    tmr0_flag++;
    timer0_250ms_flag = 1;
    timer0_500ms_counter++;
}

tmr0_t timer0_timer_obj = {
    .TMR0_INTERRUBT_HANDLER = tmr0_handler,
    .MODE = TMR0_TIMER_MODE,
    .REGISTER_SIZE = TMR0_16BIT,
    .PRESCALER_ENABLE = TMR0_PRESCALER_ENABLE_CFG,
    .PRESCALER_VALUE = PRESCALER_4,
    .PRELOAD_VALUE = 3036,
    .PRIORITY = INTERRUPT_HIGH_PRIORITY,
    .COUNTER_EDGE = TMR0_RISING_EDGE_CFG
};

int main(){
    app_init();
    
    // Initialize Timer0
    ret = TMR0_INIT(&timer0_timer_obj);
    
    // Initialize LEDs
    ret = LED_INIT(&led1);
    
    ret = LED_INIT(&led2);
    
    while(1) {
        
        if (timer0_250ms_flag == 1) {
            timer0_250ms_flag = 0;
            LED_TOGGLE(&led1);
        }
        
        if (timer0_500ms_counter >= 2) {
            LED_TOGGLE(&led2);
            timer0_500ms_counter = 0;  // Reset the counter for the next 500ms interval
        }
    }
    
    return (EXIT_SUCCESS);
}
void app_init(){
    //ECU_INIT();
}

