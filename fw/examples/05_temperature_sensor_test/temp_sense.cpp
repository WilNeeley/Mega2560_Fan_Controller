/************************
 * Temperature Sensor Source File
 * Wil Neeley
 * May 29, 2025
 *
 * A collection of function implementations for initializing, reading, and processing
 * data on the temperature sensors' analog pins. 
 *
 * Function source code location:
 * C:\Users\[insert Windows user here]\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\cores\arduino
 */
 
 
// Includes
#include "pindefs.h"
#include "temp_sense.h"
 
 
// Pin Initialization Function
void init_temp_sense() {
	
	// Set up pins as inputs
	pinMode( p_TEMP0, INPUT );
	pinMode( p_TEMP1, INPUT );	// trying something out here
	pinMode( p_TEMP2, INPUT );
	pinMode( p_TEMP3, INPUT );
	pinMode( p_TEMP4, INPUT );
	pinMode( p_TEMP5, INPUT );
	pinMode( p_TEMP6, INPUT );
	pinMode( p_TEMP7, INPUT );
	
}


// Read a pin's analog value and give the raw counts. 
int16_t read_sensor_counts( uint8_t idx ) {
	
	// Perform the correct analog read based on the index given.
	switch( idx ) {
		// For indices 0 through 7, return the results of the correct AnalogRead.
		case 0:
			return (int16_t)analogRead( p_TEMP0 ); 
		case 1:
			return (int16_t)analogRead( p_TEMP1 ); 
		case 2:
			return (int16_t)analogRead( p_TEMP2 ); 
		case 3:
			return (int16_t)analogRead( p_TEMP3 ); 
		case 4:
			return (int16_t)analogRead( p_TEMP4 ); 
		case 5:
			return (int16_t)analogRead( p_TEMP5 ); 
		case 6:
			return (int16_t)analogRead( p_TEMP6 ); 
		case 7:
			return (int16_t)analogRead( p_TEMP7 ); 
		// For other indices, return a -1. 
		default:	
			return -1;
	}
	
	// Should never get here, but adding this to keep the compiler happy.
	return -1;
	
}


// Convert raw counts to a temperature in Celsius. Assumes a TMP36 sensor.
float counts_to_celsius_tmp36( int16_t counts ) {
	
	// Constant variables
	// AREF voltage; powered by 5V supply. Can tweak depending on your board's
	// actual value for more accuracy.
	const float v_aref = 5.06;
	// Max counts; fixed at 1024. 
	const float counts_max = 1024.0;
	// M and B values for a linear mapping of voltage to temperature (Y=MX+B).
	const float temp_m = 100.0;		// 10mV/degC -> 100 degC/V
	const float temp_b = -50.0;		// 750mV @ 25C -> 500mV @ 0C -> -50C @ 0V
	
	// Variable definitions
	float volts;
	float temp;
	
	// Catching edge cases: if counts = -1, return -99.
	if( counts == -1 ) {
		return -99.0;
	}
	
	// Calculations
	volts = (v_aref * counts)/counts_max;
	temp  = (temp_m * volts) + temp_b;
	
	return temp;
}