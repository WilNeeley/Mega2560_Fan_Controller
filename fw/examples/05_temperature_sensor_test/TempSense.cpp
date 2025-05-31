/************************
 * Temperature Sensor Class Source File
 * Wil Neeley
 * May 30, 2025
 *
 * A class designed to read the analog inputs associated with the Mega2560 Fan
 * Controller board's temperature sensor pins and to convert said readings to 
 * their associated temperatures. 
 */


 
/*** Includes ***/
#include "TempSense.h"
#include "pindefs.h"



/*** Constructor ***/

TempSense::TempSense( ) {
	
	// Variable Definitions
	uint8_t i;
	
	// Give the temperature sensor conversion parameters a default value
	sensor_m = 1.0;
	sensor_b = 0.0;
	
	// Initialize the readings with nonsensical default values
	for( i = 0; i < NUM_SENSORS; i++ ) {
		raw[i]  = 42069;
		volt[i] = -1.0;
		t_c[i]  = -99.0;
	}
	
	// Initialize the I/O
	pinMode( p_TEMP0, INPUT );
	pinMode( p_TEMP1, INPUT );
	pinMode( p_TEMP2, INPUT );
	pinMode( p_TEMP3, INPUT );
	pinMode( p_TEMP4, INPUT );
	pinMode( p_TEMP5, INPUT );
	pinMode( p_TEMP6, INPUT );
	pinMode( p_TEMP7, INPUT );
	
}



/*** Configuration Functions ***/

bool TempSense::set_sensor_type( TempSensorType t ) {
	
	// Set up the Temperature Sensor Conversion Parameters
	switch( t ) {
		// TMP36
		case TMP36:
			sensor_m = M_TMP36;
			sensor_b = B_TMP36;
			return true;
		// TMP37
		case TMP37:
			sensor_m = M_TMP37;
			sensor_b = M_TMP37;
			return true;
		// Add other sensors here as desired
		
		// Default
		default:
			sensor_m = 1.0;
			sensor_b = 0.0;
			return false;
	}	
	
}



/*** Sensor Reading Functions ***/

// Read One Sensor
void TempSense::read_sensor( uint8_t idx ) {
	
	// Catch unacceptable index parameters here; it's unsigned, so don't have to
	// worry about negative edge cases.
	if( idx >= NUM_SENSORS ) {
		return;
	}
	
	// Perform the correct analog read based on the index given.
	switch( idx ) {
		case 0:
			raw[idx] = analogRead( p_TEMP0 );	break;
		case 1:
			raw[idx] = analogRead( p_TEMP1 );	break;
		case 2:
			raw[idx] = analogRead( p_TEMP2 );	break;
		case 3:
			raw[idx] = analogRead( p_TEMP3 );	break; 
		case 4:
			raw[idx] = analogRead( p_TEMP4 );	break;
		case 5:
			raw[idx] = analogRead( p_TEMP5 );	break;
		case 6:
			raw[idx] = analogRead( p_TEMP6 );	break;
		case 7:
			raw[idx] = analogRead( p_TEMP7 );	break;
		// should never get here
		default:	
			break;
	}
	
	// Convert raw counts to a voltage value
	volt[idx] = (V_AREF/CMAX) * (float)raw[idx];
	
	// Convert voltage to degrees Celsius
	t_c[idx]  = (sensor_m * volt[idx]) + sensor_b;
	
}


// Read sensors based on a given bitmask
void TempSense::read_sensor_mask( uint8_t mask ) {
	
	// Variable definition
	uint8_t i;
	
	// Iteration Loop
	for( i = 0; i < NUM_SENSORS; i++ ) {
	
		// If the matching bit's set in the mask, read its sensor.
		if( mask & ( 0x01 << i ) ) {
			this->read_sensor( i );
		}
	
	}
	
}


// Read all sensors
void TempSense::read_all_sensors() {
	
	// Variable definition
	uint8_t i;
	
	// Iteration loop
	for( i = 0; i < NUM_SENSORS; i++ ) {
		this->read_sensor( i );
	}
	
}



/*** Measurement Reporting Functions ***/

// Report Raw ADC Counts

uint16_t TempSense::get_counts( uint8_t idx ) {
	
	// Catch unacceptable index parameters here; it's unsigned, so don't have to
	// worry about negative edge cases.
	if( idx >= NUM_SENSORS ) {
		return 42069;		// unrealistically high for the ADC
	}
	
	// Otherwise, return the raw counts
	return raw[idx];
	
}


// Report Voltage Reading

float TempSense::get_volts( uint8_t idx ) {
	
	// Catch unacceptable index parameters here; it's unsigned, so don't have to
	// worry about negative edge cases.
	if( idx >= NUM_SENSORS ) {
		return -1.0;		// ADC can't go negative, so it's an unrealistic value
	}
	
	// Otherwise, return the raw counts
	return volt[idx];
	
}


// Report Temperature in Celsius

float TempSense::get_temp_c( uint8_t idx ) {
	
	// Catch unacceptable index parameters here; it's unsigned, so don't have to
	// worry about negative edge cases.
	if( idx >= NUM_SENSORS ) {
		return -99.0;		// Unrealistically cold for the temperature sensor
	}
	
	// Otherwise, return the raw counts
	return t_c[idx];
	
}


// Report Temperature in Fahrenheit

float TempSense::get_temp_f( uint8_t idx ) {
	
	// Call the Celsius version, and convert its result to Fahrenheit. Don't have
	// to worry about index bounding, as the Celsius function covers that.
	return ( M_C2F * this->get_temp_c(idx) ) + B_C2F;
	
}