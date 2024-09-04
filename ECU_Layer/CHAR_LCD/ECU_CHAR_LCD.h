/* 
 * File:   ECU_CHAR_LCD.h
 * Author: amr09
 *
 * Created on August 5, 2024, 2:03 PM
 */

#ifndef ECU_CHAR_LCD_H
#define	ECU_CHAR_LCD_H

    #include "../../MCAL_Layer/GPIO/hal_gpio.h"
    #include "ecu_char_lcd_cfg.h"

    #define row1 1
    #define row2 2
    #define row3 3
    #define row4 4

    //<---------------- LCD COMMANDS ---------------->
    #define LCD_CLEAR                       0X01
    #define LCD_RETURN_HOME                 0X02
    #define LCD_ENTERY_MODE                 0X06
    #define LCD_CURSOR_OFF_DISPLAY_ON       0X0C
    #define LCD_CURSOR_OFF_DISPLAY_OFF      0X08
    #define LCD_CURSOR_ON_BLINK_ON          0X0F
    #define LCD_CURSOR_ON_BLINK_OFF         0X0E
    #define LCD_DISPLAY_SHIFT_RIGHT         0X1C
    #define LCD_DISPLAY_SHIFT_LEFT          0X18
    #define LCD_8BIT_MODE_2LINE             0X38
    #define LCD_4BIT_MODE_2LINE             0X28
    #define LCD_CGRAM_START                 0X40
    #define LCD_DDRAM_START                 0X80


    typedef struct{
        pin_config_t LCD_RS;
        pin_config_t LCD_EN;
        pin_config_t LCD_DATA[4];
    }char_lcd_4bit_t;

    typedef struct{
        pin_config_t LCD_RS;
        pin_config_t LCD_EN;
        pin_config_t LCD_DATA[8];
    }char_lcd_8bit_t;


    std_ReturnType LCD_4BIT_INIT(const char_lcd_4bit_t *lcd);
    std_ReturnType LCD_4BIT_SEND_COMMAND(const char_lcd_4bit_t *lcd, uint8 command);
    std_ReturnType LCD_4BIT_SEND_CHAR_DATA(const char_lcd_4bit_t *lcd, uint8 data);
    std_ReturnType LCD_4BIT_SEND_CHAR_DATA_POS(const char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data);
    std_ReturnType LCD_4BIT_SEND_STRING_DATA(const char_lcd_4bit_t *lcd, uint8 *str);
    std_ReturnType LCD_4BIT_SEND_STRING_DATA_POS(const char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str);
    std_ReturnType LCD_4BIT_SEND_CUSTOM_CHAR(const char_lcd_4bit_t *lcd, uint8 row, uint8 column,
                                             const uint8 *character, uint8 mem_pos);

    std_ReturnType LCD_8BIT_INIT(const char_lcd_8bit_t *lcd);
    std_ReturnType LCD_8BIT_SEND_COMMAND(const char_lcd_8bit_t *lcd, uint8 command);
    std_ReturnType LCD_8BIT_SEND_CHAR_DATA(const char_lcd_8bit_t *lcd, uint8 data);
    std_ReturnType LCD_8BIT_SEND_CHAR_DATA_POS(const char_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data);
    std_ReturnType LCD_8BIT_SEND_STRING_DATA(const char_lcd_8bit_t *lcd, uint8 *str);
    std_ReturnType LCD_8BIT_SEND_STRING_DATA_POS(const char_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str);
    std_ReturnType LCD_8BIT_SEND_CUSTOM_CHAR(const char_lcd_8bit_t *lcd, uint8 row, uint8 column,
                                             const uint8 *character, uint8 mem_pos);

    std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str);
    std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str);
    std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str);

#endif	/* ECU_CHAR_LCD_H */

