/************************
 * Temperature Sensor Header File
 * Wil Neeley
 * May 29, 2025
 *
 * A collection of function definitions for initializing, reading, and processing
 * data on the temperature sensors' analog pins. 
 *
 * Function source code location:
 * C:\Users\[insert Windows user here]\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\cores\arduino
 *
 * Arduino Mega 2560 pin definitions location:
 * C:\Users\[insert Windows user here]\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\variants\mega
 */

#ifndef TEMP_SENSE_H
#define TEMP_SENSE_H

// Includes
#include <Arduino.h> 


// Pin Initialization Function
void init_temp_sense();

// Read a pin's analog value and give the raw counts.
int16_t read_sensor_counts( uint8_t idx );

// Convert raw counts to a temperature in Celsius. Assumes a TMP36 sensor.
float counts_to_celsius_tmp36( int16_t counts );


#endif // TEMP_SENSE_H 