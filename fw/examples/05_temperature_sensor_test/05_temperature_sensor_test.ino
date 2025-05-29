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
#include "temp_sense.h"


// Parameter Definitions
#define UART_BAUD_RATE    115200
#define NUM_SENSORS            8


// Variables
int16_t  counts[ NUM_SENSORS ];
float    temps[ NUM_SENSORS ];
unsigned char  i;


void setup() {
  // put your setup code here, to run once:

  // Temperature sensor initialization
  init_temp_sense();

  // Serial port initialization
  Serial.begin( UART_BAUD_RATE );

}


void loop() {
  // put your main code here, to run repeatedly:

  // Get raw count readings
  for( i = 0; i < NUM_SENSORS; i++ ) {
    counts[i] = read_sensor_counts( i );
  }

  // Convert counts to temperature readings
  for( i = 0; i < NUM_SENSORS; i++ ) {
    temps[i] = counts_to_celsius_tmp36( counts[i] );
  }

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
  Serial.println(F("# | Counts | Temp C"));
  Serial.println(F("----------------------"));

  // Print out the contents of each line
  for( i = 0; i < NUM_SENSORS; i++ ) {
    // Sensor number
    Serial.print( i );
    Serial.print(F(" | "));

    // Counts
    Serial.print( counts[i] );
    Serial.print(F("\t   | "));

    // Temperatures
    Serial.println( temps[i], 1 );
  }

}
