/************************
 * Pin Definitions File
 * Wil Neeley
 * May 22, 2025
 *
 * A collection of pin and port definitions for the Mega2560 PWM Fan Controller
 * board. This makes it easy to keep things consistent across all the various
 * examples and projects for programming the board.
 *
 * Function source code location:
 * C:\Users\[insert Windows user here]\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\cores\arduino
 *
 * Arduino Mega 2560 pin definitions location:
 * C:\Users\[insert Windows user here]\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\variants\mega
 */
 
#ifndef PIN_DEFS_H
#define PIN_DEFS_H

/*
 * Port Definitions
 */

// ENABLE port (read): Port J
#define port_EN_DIR		DDRJ
#define port_EN_OUT		PORTJ
#define port_EN_IN		PINJ

// SET port (read): Port A
#define port_SET_DIR	DDRA
#define port_SET_OUT	PORTA
#define port_SET_IN		PINA

// FAULT port (write): Port C
#define port_FLT_DIR	DDRC
#define port_FLT_OUT	PORTC
#define port_FLT_IN		PINC

// PWR port (write): Port D
#define port_PWR_DIR	DDRD
#define port_PWR_OUT	PORTD
#define port_PWR_IN		PIND

/*
 * Pin Definitions
 *
 * Defines which pins (in Arduino Mega2560 header nomenclature) signals are 
 * mapped to. Comments about the actual AVR chip's pin number are added as a 
 * comment at the end.
 */
 
// PWM pins
#define p_PWM0		  8		// AVR: pin 17 (PH5/OC4C). Runs on Timer 4. 
#define p_PWM1  	 46		// AVR: pin 38 (PL3/OC5A). Runs on Timer 5.
#define p_PWM2  	 45		// AVR: pin 39 (PL4/OC5B). Runs on Timer 5.
#define p_PWM3		 44		// AVR: pin 40 (PL5/OC5C). Runs on Timer 5.
#define p_PWM4		  6		// AVR: pin 15 (PH3/OC4A). Runs on Timer 4.
#define p_PWM5		  3		// AVR: pin  7 (PE5/OC3C). Runs on Timer 3.
#define p_PWM6		  2		// AVR: pin  6 (PE4/OC3B). Runs on Timer 3.
#define p_PWM7  	  5		// AVR: pin  5 (PE3/OC3A). Runs on Timer 3. 
#define p_PWMT		  7		// AVR: pin 16 (PH4/OC4B). Runs on Timer 4.

// Tachometer Pins
#define p_TACH0		 A8		// AVR: pin 89 (PK0/PCINT16).
#define p_TACH1		 A9		// AVR: pin 88 (PK1/PCINT17).
#define p_TACH2		A10		// AVR: pin 87 (PK2/PCINT18).
#define p_TACH3		A11		// AVR: pin 86 (PK3/PCINT19).
#define p_TACH4		A12		// AVR: pin 85 (PK4/PCINT20).
#define p_TACH5		A13		// AVR: pin 84 (PK5/PCINT21).
#define p_TACH6		A14		// AVR: pin 83 (PK6/PCINT22).
#define p_TACH7		A15		// AVR: pin 82 (PK7/PCINT23).
#define p_TACHT		 12		// AVR: pin 25 (PB6/PCINT6).

// Temperature Pins
#define p_TEMP0		 A0		// AVR: pin 97 (PF0/ADC0).
#define p_TEMP1		 A1		// AVR: pin 96 (PF1/ADC1).
#define p_TEMP2		 A2		// AVR: pin 95 (PF2/ADC2).
#define p_TEMP3		 A3		// AVR: pin 94 (PF3/ADC3).
#define p_TEMP4		 A4		// AVR: pin 93 (PF4/ADC4).
#define p_TEMP5		 A5		// AVR: pin 92 (PF5/ADC5).
#define p_TEMP6		 A6		// AVR: pin 91 (PF6/ADC6).
#define p_TEMP7		 A7		// AVR: pin 90 (PF7/ADC7).

// Select Pins
#define p_SEL0		 43		// AVR: pin 41 (PL6).
#define p_SEL1		 42		// AVR: pin 42 (PL7).
#define p_SEL2  	 41		// AVR: pin 51 (PG0).
#define p_SEL3  	 40		// AVR: pin 52 (PG1).
#define p_SEL4  	 39		// AVR: pin 70 (PG2).
#define p_SEL5		 48		// AVR: pin 36 (PL1).
#define p_SEL6		 47		// AVR: pin 37 (PL2).

// Non-Grouped Pins
#define p_LED		 13		// AVR: pin 26 (PB7/OC0A/OC1C).
#define p_BUZZ		 10		// AVR: pin 23 (PB4/OC2A). Runs on Timer 2.
#define p_5V_STAT	 11		// AVR: pin 24 (PB5). 
#define p_5V_EN		 53		// AVR: pin 19 (PB0).
#define p_TRIGGER	  4		// AVR: pin  1 (PG5).
//	#define p_SER_TX	  1		// AVR: pin  3 (PE1/TXD0).
//	#define p_SER_RX	  0		// AVR: pin  2 (PE0/RXD0).

// Spare Pins
//	#define p_SPARE_09	  9		// AVR: pin 18 (PH6/OC2B).
//	#define p_SPARE_16	 16		// AVR: pin 13 (PH1/TXD2).
//	#define p_SPARE_17	 17		// AVR: pin 12 (PH0/RXD2).
//	#define p_SPARE_49	 49		// AVR: pin 35 (PL0).


#endif // PIN_DEFS_H