/* 
 * File:   ECU_CHAR_LCD.c
 * Author: amr09
 *
 * Created on August 5, 2024, 2:03 PM
 */

#include "ECU_CHAR_LCD.h"

static std_ReturnType LCD_SEND_4BIT(const char_lcd_4bit_t *lcd, uint8 data);
static std_ReturnType LCD_4BIT_SEND_ENABLE_SEGNAL(const char_lcd_4bit_t *lcd);

static std_ReturnType LCD_SEND_8BIT(const char_lcd_8bit_t *lcd, uint8 data);
static std_ReturnType LCD_8BIT_SEND_ENABLE_SEGNAL(const char_lcd_8bit_t *lcd);

static std_ReturnType LCD_8BIT_SET_CURCOR(const char_lcd_8bit_t *lcd, uint8 row, uint8 column);
static std_ReturnType LCD_4BIT_SET_CURCOR(const char_lcd_4bit_t *lcd, uint8 row, uint8 column);

//<------------ 4BIT FUNCTIONS ------------>

/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_4BIT_INIT(const char_lcd_4bit_t *lcd){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = GPIO_PIN_INITIALIZE(&(lcd -> LCD_RS));
        ret = GPIO_PIN_INITIALIZE(&(lcd -> LCD_EN));
        for(uint8 i = 0; i < 4; i++){
            ret = GPIO_PIN_INITIALIZE(&(lcd -> LCD_DATA[i]));
        }
        __delay_ms(20);
        ret = LCD_4BIT_SEND_COMMAND(lcd, LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret = LCD_4BIT_SEND_COMMAND(lcd, LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        ret = LCD_4BIT_SEND_COMMAND(lcd, LCD_8BIT_MODE_2LINE);
        
        ret = LCD_4BIT_SEND_COMMAND(lcd, LCD_CLEAR);
        ret = LCD_4BIT_SEND_COMMAND(lcd, LCD_RETURN_HOME);
        ret = LCD_4BIT_SEND_COMMAND(lcd, LCD_ENTERY_MODE);
        ret = LCD_4BIT_SEND_COMMAND(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        ret = LCD_4BIT_SEND_COMMAND(lcd, LCD_4BIT_MODE_2LINE);
        ret = LCD_4BIT_SEND_COMMAND(lcd, LCD_DDRAM_START);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_4BIT_SEND_COMMAND(const char_lcd_4bit_t *lcd, uint8 command){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = GPIO_PIN_WRITE_LOGIC(&(lcd -> LCD_RS), GPIO_LOW);
        ret = LCD_SEND_4BIT(lcd, command >> 4);
        ret = LCD_4BIT_SEND_ENABLE_SEGNAL(lcd);
        ret = LCD_SEND_4BIT(lcd, command);
        ret = LCD_4BIT_SEND_ENABLE_SEGNAL(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd Pointer to the LCD configurations
 * @param data The data that we need to send to the LCD
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_4BIT_SEND_CHAR_DATA(const char_lcd_4bit_t *lcd, uint8 data){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = GPIO_PIN_WRITE_LOGIC(&(lcd -> LCD_RS), GPIO_HIGH);
        ret = LCD_SEND_4BIT(lcd, data >> 4);
        ret = LCD_4BIT_SEND_ENABLE_SEGNAL(lcd);
        ret = LCD_SEND_4BIT(lcd, data);
        ret = LCD_4BIT_SEND_ENABLE_SEGNAL(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_4BIT_SEND_CHAR_DATA_POS(const char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = LCD_4BIT_SET_CURCOR(lcd, row, column);
        ret = LCD_4BIT_SEND_CHAR_DATA(lcd, data);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_4BIT_SEND_STRING_DATA(const char_lcd_4bit_t *lcd, uint8 *str){
    std_ReturnType ret = E_OK;
    if(NULL == lcd || NULL == str){
        ret = E_NOT_OK;
    }else{
        while(*str){
            ret = LCD_4BIT_SEND_CHAR_DATA(lcd, *str++);
            ret &= ret;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_4BIT_SEND_STRING_DATA_POS(const char_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    std_ReturnType ret = E_OK;
    if(NULL == lcd || NULL == str){
        ret = E_NOT_OK;
    }else{
        ret = LCD_4BIT_SET_CURCOR(lcd, row, column);
        while(*str){
            ret = LCD_4BIT_SEND_CHAR_DATA(lcd, *str++);
            ret &= ret;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_4BIT_SEND_CUSTOM_CHAR(const char_lcd_4bit_t *lcd, uint8 row, uint8 column, 
                                         const uint8 *character, uint8 mem_pos){
    std_ReturnType ret = E_OK;
    if(NULL == lcd || NULL == character){
        ret = E_NOT_OK;
    }else{
        ret = LCD_4BIT_SEND_COMMAND(lcd, LCD_CGRAM_START + (mem_pos * 8));
        for(uint8 i = 0; i <= 7;i++){
            ret = LCD_4BIT_SEND_CHAR_DATA(lcd, character[i]);
        }
        ret = LCD_4BIT_SEND_CHAR_DATA_POS(lcd, row, column, mem_pos);
    }
    return ret;
}

//<------------ 8BIT FUNCTIONS ------------>

/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_8BIT_INIT(const char_lcd_8bit_t *lcd){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = GPIO_PIN_INITIALIZE(&(lcd -> LCD_RS));
        ret = GPIO_PIN_INITIALIZE(&(lcd -> LCD_EN));
        for(uint8 i = 0; i < 8; i++){
            ret = GPIO_PIN_INITIALIZE(&(lcd -> LCD_DATA[i]));
        }
        __delay_ms(20);
        ret = LCD_8BIT_SEND_COMMAND(lcd, LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret = LCD_8BIT_SEND_COMMAND(lcd, LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        ret = LCD_8BIT_SEND_COMMAND(lcd, LCD_8BIT_MODE_2LINE);
        
        ret = LCD_8BIT_SEND_COMMAND(lcd, LCD_CLEAR);
        ret = LCD_8BIT_SEND_COMMAND(lcd, LCD_RETURN_HOME);
        ret = LCD_8BIT_SEND_COMMAND(lcd, LCD_ENTERY_MODE);
        ret = LCD_8BIT_SEND_COMMAND(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        ret = LCD_8BIT_SEND_COMMAND(lcd, LCD_8BIT_MODE_2LINE);
        ret = LCD_8BIT_SEND_COMMAND(lcd, LCD_DDRAM_START);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_8BIT_SEND_COMMAND(const char_lcd_8bit_t *lcd, uint8 command){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = GPIO_PIN_WRITE_LOGIC(&(lcd -> LCD_RS), GPIO_LOW);
        ret = LCD_SEND_8BIT(lcd, command);
        ret = LCD_8BIT_SEND_ENABLE_SEGNAL(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_8BIT_SEND_CHAR_DATA(const char_lcd_8bit_t *lcd, uint8 data){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = GPIO_PIN_WRITE_LOGIC(&(lcd -> LCD_RS), GPIO_HIGH);
        ret = LCD_SEND_8BIT(lcd, data);
        ret = LCD_8BIT_SEND_ENABLE_SEGNAL(lcd);
        
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_8BIT_SEND_CHAR_DATA_POS(const char_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = LCD_8BIT_SET_CURCOR(lcd, row, column);
        ret = LCD_8BIT_SEND_CHAR_DATA(lcd, data);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_8BIT_SEND_STRING_DATA(const char_lcd_8bit_t *lcd, uint8 *str){
    std_ReturnType ret = E_OK;
    if(NULL == lcd || NULL == str){
        ret = E_NOT_OK;
    }else{
        while(*str){
            ret = LCD_8BIT_SEND_CHAR_DATA(lcd, *str++);
            ret &= ret;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_8BIT_SEND_STRING_DATA_POS(const char_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    std_ReturnType ret = E_OK;
    if(NULL == lcd || NULL == str){
        ret = E_NOT_OK;
    }else{
        ret = LCD_8BIT_SET_CURCOR(lcd, row, column);
        while(*str){
            ret = LCD_8BIT_SEND_CHAR_DATA(lcd, *str++);
            ret &= ret;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType LCD_8BIT_SEND_CUSTOM_CHAR(const char_lcd_8bit_t *lcd, uint8 row, uint8 column,
                                         const uint8 *character, uint8 mem_pos){
    std_ReturnType ret = E_OK;
    if(NULL == lcd || NULL == character){
        ret = E_NOT_OK;
    }else{
        ret = LCD_8BIT_SEND_COMMAND(lcd, LCD_CGRAM_START + (mem_pos * 8));
        for(uint8 i = 0; i <= 7;i++){
            ret = LCD_8BIT_SEND_CHAR_DATA(lcd, character[i]);
        }
        ret = LCD_8BIT_SEND_CHAR_DATA_POS(lcd, row, column, mem_pos);
        
    }
    return ret;
}

//<------------ CONVERT TO STRING FUNCTIONS ------------>

/**
 * 
 * @param value
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str){
    std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset((char *)str, '\0', 4);
        sprintf(str, "%i", value);
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str){
    std_ReturnType ret = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset(str, ' ', 5);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str){
    std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset((char *)str, '\0', 11);
        sprintf(str, "%i", value);
    }
    return ret;
}


//<------------ HELLPER FUNCTIONS ------------>

/**
 * 
 * @param lcd
 * @param data
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static std_ReturnType LCD_SEND_4BIT(const char_lcd_4bit_t *lcd, uint8 data){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        for(uint8 i = 0; i < 4; i++){
            ret = GPIO_PIN_WRITE_LOGIC(&(lcd -> LCD_DATA[i]), (data >> i) & (uint8)0x01);
            ret &= ret;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static std_ReturnType LCD_4BIT_SEND_ENABLE_SEGNAL(const char_lcd_4bit_t *lcd){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = GPIO_PIN_WRITE_LOGIC(&(lcd -> LCD_EN), GPIO_HIGH);
        __delay_us(5);
        ret = GPIO_PIN_WRITE_LOGIC(&(lcd -> LCD_EN), GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param _data_command
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static std_ReturnType LCD_SEND_8BIT(const char_lcd_8bit_t *lcd, uint8 data){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        for(uint8 i = 0; i < 8; i++){
            ret = GPIO_PIN_WRITE_LOGIC(&(lcd -> LCD_DATA[i]), (data >> i) & (uint8)0x01);
            ret &= ret;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static std_ReturnType LCD_8BIT_SEND_ENABLE_SEGNAL(const char_lcd_8bit_t *lcd){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = GPIO_PIN_WRITE_LOGIC(&(lcd -> LCD_EN), GPIO_HIGH);
        __delay_us(5);
        ret = GPIO_PIN_WRITE_LOGIC(&(lcd -> LCD_EN), GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param lcd Pointer to the LCD configuration parameters defined by the user
 * @param row Which row you need to print your character
 * @param coulmn Which column you need to print your character
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static std_ReturnType LCD_8BIT_SET_CURCOR(const char_lcd_8bit_t *lcd, uint8 row, uint8 column){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        column--;
        switch(row){
            case row1: ret = LCD_8BIT_SEND_COMMAND(lcd, (0x80 + column)); break;
            case row2: ret = LCD_8BIT_SEND_COMMAND(lcd, (0xC0 + column)); break;
            case row3: ret = LCD_8BIT_SEND_COMMAND(lcd, (0x94 + column)); break;
            case row4: ret = LCD_8BIT_SEND_COMMAND(lcd, (0xD4 + column)); break;
            default: ;
        }
    }
    return ret;
}

/**
 * 
 * @param lcd Pointer to the LCD configuration parameters defined by the user
 * @param row Which row you need to print your character
 * @param coulmn Which column you need to print your character
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static std_ReturnType LCD_4BIT_SET_CURCOR(const char_lcd_4bit_t *lcd, uint8 row, uint8 column){
    std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        column--;
        switch(row){
            case row1: ret = LCD_4BIT_SEND_COMMAND(lcd, (0x80 + column)); break;
            case row2: ret = LCD_4BIT_SEND_COMMAND(lcd, (0xC0 + column)); break;
            case row3: ret = LCD_4BIT_SEND_COMMAND(lcd, (0x94 + column)); break;
            case row4: ret = LCD_4BIT_SEND_COMMAND(lcd, (0xD4 + column)); break;
            default: ;
        }
    }
    return ret;
}
