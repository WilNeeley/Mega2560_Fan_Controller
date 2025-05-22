// Includes
#include "pindefs.h"    // Covers pin and port definitions

// Variable Definitions
uint8_t fault_leds = 0;

void setup() {
  // put your setup code here, to run once:

  // Input signal initialization
  pinMode( p_5V_STAT, INPUT );     // Source Selector STAT pin state
  pinMode( p_5V_EN,   INPUT );     // Source Selector EN pin state

  // Output port initialization
  // Sets port directions
  port_FLT_DIR  = 0xFF;   // 0 in a given bit = output; 0xFF (in hexadecimal) represents that all bits are set to 1.
  // Sets port output values
  //  port_FLT_OUT  = 0x00;   // Output a low signal for starters
}

void loop() {
  // put your main code here, to run repeatedly:

  // Initialize the output array to zero
  fault_leds = 0;

  // Read 5V_STAT and 5V_EN; set bits in Fault LEDs
  // Bit 0 (LED 1): 5V_STAT
  if( digitalRead( p_5V_STAT ) ) {
    fault_leds = fault_leds | 0b00000001;
  }
  // Bit 1 (LED 2): 5V_EN
  if( digitalRead( p_5V_EN ) ) {
    fault_leds = fault_leds | 0b00000010;
  }    

  // Depending on the current state of the pins (as saved in "fault_leds"),
  // set other LED bits to indicate what the power source is.
  // Bit 7 (LED 8): 5V Regulator (5V_EN = 0, 5V_STAT = 0)
  switch( fault_leds ) {
    // If 0, 5V_EN = 0 and 5V_STAT = 0, which happens when running on the 5V regulator.
    // Set Bit 7 (LED 8) for 5V Regulator.
    case 0:
      fault_leds |= 0b10000000; // same as "fault_leds = fault_leds | 0b10000000;"
      break;
    // If 1, 5V_EN = 0 and 5V_STAT = 1, which happens when running on USB power.
    // Set Bit 6 (LED 7) for USB power.
    case 1:
      fault_leds |= 0b01000000;
      break;
    // If 3, 5V_EN = 1 and 5V_STAT = 1, which happens when running on AVR power (bootloader header).
    // Set Bit 5 (LED 6) for AVR power.
    case 3:
      fault_leds |= 0b00100000;
      break;
    // Default: Should never happen, but set Bits 4 through 2 (LEDs 5 through 3). 
    default:
      fault_leds |= 0b00011100;

  }

  // Drive output LEDS appropriately
  port_FLT_OUT = fault_leds;

}
