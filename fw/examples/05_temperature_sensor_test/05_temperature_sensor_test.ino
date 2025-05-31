/*
* Temperature Sensor Test
* Wil Neeley
* 2025-05-29
*
* For details on sketch functionality, please consult the "fw_board_checkout_sketches.md" Markdown file
* in the "doc" folder. For the best experience, you will want to view it through GitHub or using an IDE
* with Markdown viewing utility like Virtual Studio Code (CTRL + SHIFT + V).
*/


// Includes
#include "TempSense.h"


// Parameter Definitions
#define UART_BAUD_RATE    115200

// Temperature Sensor Type Definition
TempSense temps;


// Variables
uint8_t  i;


void setup() {
  // put your setup code here, to run once:

  // Temperature sensor class is initialized with its constructor, so we don't need anything here.
  temps.set_sensor_type( TMP36 );

  // Serial port initialization
  Serial.begin( UART_BAUD_RATE );

}


void loop() {
  // put your main code here, to run repeatedly:

  // Measure all sensors
  temps.read_all_sensors();

  // Display results on Serial Port
  display_results();

  delay( 2000 );
}


// Used for displaying results on the screen in a formatted manner. 
void display_results() {

  // NOTE: the F("string") functions force the text within to be saved to the MCU's program memory, which
  // saves space in the variable memory. 

  // Prints a blank line
  Serial.println(F(" "));

  // Print the header to a formatted table
  Serial.println(F("# | Counts | Volts | Temp C     | Temp F "));
  Serial.println(F("----------------------------------------"));

  // Print out the contents of each line
  for( i = 0; i < NUM_SENSORS; i++ ) {
    // Sensor number
    Serial.print( i );
    Serial.print(F(" | "));

    // Counts
    Serial.print( temps.get_counts( i ) );
    Serial.print(F("\t   | "));

    // Volts
    Serial.print( temps.get_volts( i ), 3 );
    Serial.print(F(" | "));

    // Temperature (C)
    Serial.print( temps.get_temp_c( i ), 1 );
    Serial.print(F("\t| "));

    // Temperature (C)
    Serial.println( temps.get_temp_f( i ), 1 );
  }

}
