// Includes
#include "pindefs.h"    // Covers pin and port definitions

// Variable Definitions
uint8_t sel = 0;

void setup() {
  // put your setup code here, to run once:

  // Input signal initialization
  pinMode( p_TRIGGER, INPUT );     // Trigger pin
  pinMode( p_SEL0,    INPUT );     // Select pins
  pinMode( p_SEL1,    INPUT );
  pinMode( p_SEL2,    INPUT );
  pinMode( p_SEL3,    INPUT );
  pinMode( p_SEL4,    INPUT );
  pinMode( p_SEL5,    INPUT );
  pinMode( p_SEL6,    INPUT );


  // Output signal initialization
  pinMode( p_LED,  OUTPUT );    // Heartbeat (D31) LED


  // Input port initialization
  // Sets port directions
  port_EN_DIR   = 0x00;   // 0 in a given bit = input; 0x00 (in hexadecimal) represents that all bits are set to 0.
  port_SET_DIR  = 0x00;
  // Disable pull-up resistors
  port_EN_OUT   = 0x00;   // 1 in a given bit could enable that pin's pull-up resistors if "PUD" in "MCUCR" is set. 
  port_SET_OUT  = 0x00;   // To be on the safe side, we're setting all values to 0.


  // Output port initialization
  // Sets port directions
  port_FLT_DIR  = 0xFF;   // 0 in a given bit = output; 0xFF (in hexadecimal) represents that all bits are set to 1.
  port_PWR_DIR  = 0xFF;   
  // Sets port output values
  //  port_FLT_OUT  = 0x00;   // Output a low signal for starters
  //  port_PWR_OUT  = 0x00;


  // LED Test Pattern
  // Step 1: All On
  port_FLT_OUT    = 0xFF;
  port_PWR_OUT    = 0xFF;
  digitalWrite( p_LED, HIGH );
  delay( 500 ); // wait half a second
  // Step 2: Half On
  port_FLT_OUT    = 0x55;
  port_PWR_OUT    = 0x55;
  digitalWrite( p_LED, LOW );
  delay( 500 ); // wait half a second
  // Step 3: Other Half On
  port_FLT_OUT    = 0xAA;
  port_PWR_OUT    = 0xAA;
  digitalWrite( p_LED, HIGH );
  delay( 500 ); // wait half a second
  // Step 4: All Off
  port_FLT_OUT    = 0x00;
  port_PWR_OUT    = 0x00;
  digitalWrite( p_LED, LOW );
  delay( 500 ); // wait half a second


}

void loop() {
  // put your main code here, to run repeatedly:

  // Part 1: read Trigger pin, set LED to the same value
  digitalWrite( p_LED, digitalRead( p_TRIGGER ) );



  // Part 2: read Enable and Set signals, perform a logical exclusive-OR on their results, and
  // display it on the Fault LED signals.
  port_FLT_OUT    = port_EN_IN ^ port_SET_IN;



  // Part 3: read the various SEL lines to find the switch position, and send power to the fan
  // that matches that bit (and light up its power LED).

  // Set SEL to 0 by default; will set bits to 1 if their pins read high.
  sel = 0;

  // Bit 0
  if( digitalRead( p_SEL0) == HIGH ) {    // The cleaner way to write this IF statement, for legibility
    sel = sel | 0b00000001;
  }
  // Bit 1
  if( digitalRead( p_SEL1 ) ) {           // Accomplishes the same result
    sel = sel | 0b00000010;
  }
  // Bit 2
  if( digitalRead( p_SEL2 ) ) {
    sel = sel | 0b00000100;
  }
  // Bit 3
  if( digitalRead( p_SEL3 ) ) {
    sel = sel | 0b00001000;
  }
  // Bit 4
  if( digitalRead( p_SEL4 ) ) {
    sel = sel | 0b00010000;
  }
  // Bit 5
  if( digitalRead( p_SEL5 ) ) {
    sel = sel | 0b00100000;
  }
  // Bit 6
  if( digitalRead( p_SEL6 ) ) {
    sel = sel | 0b01000000;
  }

  // If none were set, switch is in the home position, so set the most significant bit.
  if( sel == 0 ) {
    sel = 0b10000000;
  }

  // Set the power switches accordingly
  port_PWR_OUT = sel;

}
