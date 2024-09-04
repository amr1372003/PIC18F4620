/* 
 * File:   mcal_std_types.h
 * Author: amr09
 *
 * Created on September 16, 2023, 5:52 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

    #include "std_libraries.h"
    #include "compiler.h"
    #include <string.h>

    
    typedef unsigned char uint8;
    typedef unsigned short uint16;
    typedef unsigned int uint32;
    typedef signed char sint8;
    typedef signed short sint16;
    typedef signed int sint32;
    
    typedef uint8 std_ReturnType;
    
    
    #define E_OK            0X01
    #define E_NOT_OK        0X00

    #define STD_HIGH        0X01
    #define STD_LOW         0X00

    #define STD_ON          0X01
    #define STD_OFF         0X00

    #define STD_ACTIVE      (std_ReturnType)0X01
    #define STD_IDE         (std_ReturnType)0X00

    

#endif	/* MCAL_STD_TYPES_H */

