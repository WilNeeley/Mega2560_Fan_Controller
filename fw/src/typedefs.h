/************************
 * Type Definitions File
 * Wil Neeley
 * May 12, 2025
 *
 * A copy of some type definitions I created a while back. The non-union types
 * make it easy to ensure you're calling out the correct bit size for each
 * variable, while the union types make it easy to access sub-bytes or sub-bits
 * in a given variable. We'll see if they wind up getting used!
 */

#ifndef TYPE_DEFS_H
#define TYPE_DEFS_H

#if defined(__AVR__)
	#define LITTLE_ENDIAN
#endif

#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
/*
 * Number Type Definitions
 */    

// 8-bit integers
typedef unsigned char uint8_t;
typedef char int8_t;
typedef union {
    uint8_t full;
	int8_t  sign;
    struct {
		unsigned Bit0:1;
		unsigned Bit1:1;
		unsigned Bit2:1;
		unsigned Bit3:1;
		unsigned Bit4:1;
		unsigned Bit5:1;
		unsigned Bit6:1;
		unsigned Bit7:1;
    };
} Byte_t;   // useful for individual bit access

// 16-bit integers
typedef unsigned int uint16_t;
typedef int int16_t;
typedef union {
    uint16_t full;
	int16_t  sign;
    struct {
	#ifdef LITTLE_ENDIAN
        uint8_t LSB;
        uint8_t MSB;
	#else
		uint8_t MSB;
		uint8_t LSB;
	#endif
    };
} Word_t;   // useful for individual byte access
    
// 32-bit integers
typedef unsigned long uint32_t;
typedef long int32_t;
typedef union {
    uint32_t full;
	int32_t  sign;
    struct {
	#ifdef LITTLE_ENDIAN
        unsigned char LSB;
        unsigned char MSB;
        unsigned char USB;
        unsigned char XSB;
	#else
		unsigned char XSB;
		unsigned char USB;
		unsigned char MSB;
		unsigned char LSB;
	#endif
    };
} Long_t;   // useful for individual byte access


// 32-bit Float
typedef union {
	float full;
	uint32_t binary;
    struct {
	#ifdef LITTLE_ENDIAN
        unsigned char LSB;
        unsigned char MSB;
        unsigned char USB;
        unsigned char XSB;
	#else
		unsigned char XSB;
		unsigned char USB;
		unsigned char MSB;
		unsigned char LSB;
	#endif
    };	
} Float32_t;



#ifdef	__cplusplus
}
#endif

#endif // TYPE_DEFS_H 