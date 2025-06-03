/*
* Fan PWM Test
* Wil Neeley
* 2025-05-30
*
* For details on sketch functionality, please consult the "fw_board_checkout_sketches.md" Markdown file
* in the "doc" folder. For the best experience, you will want to view it through GitHub or using an IDE
* with Markdown viewing utility like Virtual Studio Code (CTRL + SHIFT + V).
*/

// Includes
#include "FanControl.h"
#include "pindefs.h"

// Fan Controller Class Object
FanControl fc;


// Variable Initializations
uint8_t i;
uint8_t sel;
uint8_t dc_vals[NUM_FANS] = { 0, 20, 35, 50, 62, 75, 88, 100 };



void setup() {
  // put your setup code here, to run once:

  // Initialize the "TEST SEL" rotary switch inputs
  pinMode( p_SEL0, INPUT );
  pinMode( p_SEL1, INPUT );
  pinMode( p_SEL2, INPUT );
  pinMode( p_SEL3, INPUT );
  pinMode( p_SEL4, INPUT );
  pinMode( p_SEL5, INPUT );
  pinMode( p_SEL6, INPUT );

  // Initialize the FAULT LED outputs
  port_FLT_DIR = 0xFF;
  port_FLT_OUT = 0x00;

  // Fan Controller Initialization
  fc.init();

}

void loop() {
  // put your main code here, to run repeatedly:

  // Have the fan controller read its switches
  fc.read_switches();

  // Read the TEST SEL switch's position
  sel = read_sel_switch_position();

  // Set PWM duty cycles to values set in "dc_vals"
  for( i =0; i < NUM_FANS; i++ ) {
    fc.set_duty_cycle(  i,  dc_vals[sel] );
    fc.set_test_duty_cycle( dc_vals[sel] );
  }

  // Update the fan outputs
  fc.update_outputs();

  // Update FAULT LEDs
  update_fault_leds();

}



// Returns the index of where the SEL switch is positioned (0 through 7). 
// Position "7" corresponds to the neutral position.
uint8_t read_sel_switch_position( ) {

  // Bit 0
  if( digitalRead( p_SEL0 ) ) { return 0; }
  // Bit 1
  if( digitalRead( p_SEL1 ) ) { return 1; }
  // Bit 2
  if( digitalRead( p_SEL2 ) ) { return 2; }
  // Bit 3
  if( digitalRead( p_SEL3 ) ) { return 3; }
  // Bit 4
  if( digitalRead( p_SEL4 ) ) { return 4; }
  // Bit 5
  if( digitalRead( p_SEL5 ) ) { return 5; }
  // Bit 6
  if( digitalRead( p_SEL6 ) ) { return 6; }
  // If none were set, switch is in the home position, so return 7
  return 7;

}



// Updates the output LEDS based on a given "sel" value
void update_fault_leds() {

  switch( sel ) {
    case 0:
      port_FLT_OUT = 0b00000001;
      break;
    case 1:
      port_FLT_OUT = 0b00000011;
      break;
    case 2:
      port_FLT_OUT = 0b00000111;
      break;
    case 3:
      port_FLT_OUT = 0b00001111;
      break;
    case 4:
      port_FLT_OUT = 0b00011111;
      break;
    case 5:
      port_FLT_OUT = 0b00111111;
      break;
    case 6:
      port_FLT_OUT = 0b01111111;
      break;
    case 7:
      port_FLT_OUT = 0b11111111;
      break;
    default:
      port_FLT_OUT = 0x00;
  }

}