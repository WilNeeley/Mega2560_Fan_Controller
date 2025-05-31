/************************
 * Temperature Sensor Class Header File
 * Wil Neeley
 * May 30, 2025
 *
 * A class designed to read the analog inputs associated with the Mega2560 Fan
 * Controller board's temperature sensor pins and to convert said readings to 
 * their associated temperatures. 
 */


#ifndef TEMP_SENSE_CLASS_H
#define TEMP_SENSE_CLASS_H



/*** Includes ***/
#include <Arduino.h> 



/*** Definitions ***/

// Sensor Number Definition
#define NUM_SENSORS		8


// ADC Counts -> Voltage Conversion Parameters

// ADC Reference Voltage; measure on your own board with a multimeter and update accordingly.
#define V_AREF			5.06		// Represent it as a float so the math works correctly
// ADC Maximum Counts
#define CMAX			1024.0		// Keeping it a float helps it compile more efficiently


// Celsius to Fahrenheit Conversion Parameters
// Uses a Y = M*X + B format
#define M_C2F			(9.0/5.0)
#define B_C2F			32.0


// Temperature Sensor Slope (M) and Y-Intercept (B) Parameters
// For mapping voltage readings to temperatures

// TMP36 Parameters
// Source: https://www.analog.com/media/en/technical-documentation/data-sheets/tmp35_36_37.pdf
#define M_TMP36			100.0		// 10mV/degC -> 100 degC/V
#define B_TMP36			-50.0		// 750mV @ 25C -> 500mV @ 0C -> -50C @ 0V

// TMP37 parameters
// Source: https://www.analog.com/media/en/technical-documentation/data-sheets/tmp35_36_37.pdf
#define M_TMP37		 	50.0		// 20mV/degC -> 50 degC/V
#define B_TMP37		  	 0.0		// 500mV @ 25C -> 0V @ 0C



/*** Enumerations ***/

// Temperature Sensor Types (add your own here if you want)
typedef enum TempSensorType {
	TMP36		=	0,
	TMP37		=   1
} TempSensorType;




/*** Class Definition ***/
class TempSense {
	private:
		// Temperature Sensor Conversion Parameters
		float		sensor_m;
		float		sensor_b;
		
		// Parameter storage
		int16_t		raw[NUM_SENSORS];
		float   	volt[NUM_SENSORS];
		float		t_c[NUM_SENSORS];
		
	
	public:
		// Constructor
		TempSense( );
		
		// Configuration Functions
		bool 		set_sensor_type( TempSensorType t );
		
		// Sensor Reading Functions
		void 		read_sensor( uint8_t idx );
		void		read_sensor_mask( uint8_t mask );
		void 		read_all_sensors();
		
		// Measurement Reporting Functions
		uint16_t 	get_counts( uint8_t idx );
		float 		get_volts(  uint8_t idx );
		float 		get_temp_c( uint8_t idx );
		float		get_temp_f( uint8_t idx );
	
};

#endif // TEMP_SENSE_CLASS_H