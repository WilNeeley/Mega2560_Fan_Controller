/*
* Serial Port Test
* Wil Neeley
* 2025-05-24
*
* For details on sketch functionality, please consult the "fw_board_checkout_sketches.md" Markdown file
* in the "doc" folder. For the best experience, you will want to view it through GitHub or using an IDE
* with Markdown viewing utility like Virtual Studio Code (CTRL + SHIFT + V).
*/


// Includes
#include "pindefs.h"


// Parameter Definitions
#define UART_BAUD_RATE    115200      // Baud rate for the serial port


// LED Mirroring
// - Comment out the following definition to have the LED bits align with the numbering scheme
//   as written on the PCB (12345678).
// - Leave the following definition uncommented to have the LED bits align with what you'd expect
//   when reading a binary value (76543210).
#define MIRROR_LEDS


// Veriable Definitions
uint8_t val         = 0;          // Holds the value received by the serial port
uint8_t fault_leds  = 0;          // Holds the value being written to the Fault LEDs


void setup() {
  // put your setup code here, to run once:

  // Serial port initialization
  Serial.begin( UART_BAUD_RATE );


  // Output port initialization
  // Sets port directions
  port_FLT_DIR  = 0xFF;   // 0 in a given bit = output; 0xFF (in hexadecimal) represents that all bits are set to 1.
  // Sets port output values
  port_FLT_OUT  = 0x00;   // Output a low signal for starters
}



void loop() {
  // put your main code here, to run repeatedly:

  // Check if a valid byte has been received
  if( Serial.available() ) {

    // If so, read its contents into "val"
    val = Serial.read();

    // Transmit the received character back out
    Serial.write( val );

    // If LED mirroring is called for, perform the bit swapping here.
    #ifdef MIRROR_LEDS
      fault_leds = 0;
      for( int i = 0; i < 8; i++ ) {
        // Checks if a given bit is set in "val"; if so, sets the mirrored bit in "fault_leds"
        if( val & (0b00000001 << i) ) {
          fault_leds |= (0b10000000 >> i);
        }
      }
    // If LED mirroring isn't called for, simply copy over the value.
    #else
      fault_leds = val;
    #endif // MIRROR_LEDs

    // Output the value (mirrored or not) on the Fault LEDs
    port_FLT_OUT = fault_leds;

  }

}
