/************************
 * Fan Control Class Source File
 * Wil Neeley
 * May 30, 2025
 *
 * A class designed to read the Enable and Override switches, turn on and off
 * the fans, and set their speeds. 
 */


/*** Includes ***/
#include "FanControl.h"
#include "pindefs.h"



/*** Constructor ***/

FanControl::FanControl() {
	
	// Variable definitions
	uint8_t i;
	
	/* Parameter Initialization */
	
	// switch_en = 0;	// covered by input initialization
	// switch_or = 0;	// covered by input initialization
	
	// Keep fans off for now
	fan_pwr			= 0x00;
	fan_fault		= 0x00;
	test_dc			= 0;
	test_count		= 0;
	for( i = 0; i < NUM_FANS; i++ ) {
		fan_dc[i]		= 0;
		fan_count[i]	= 0;
	}
	
}



/*** Private PWM Control Functions ***/

// Enables PWM for a given fan index.
void FanControl::enable_pwm( uint8_t idx ) {
	
	switch( idx ) {
		// Indices 0 through 7: enable the matching fan
		case 0:	// OC4C
			TCCR4A |= 0b00001000;	// 0b----10--
			break;
		case 1: // OC5A
			TCCR5A |= 0b10000000;	// 0b10------
			break;
		case 2:	// OC5B
			TCCR5A |= 0b00100000;	// 0b--10----
			break;
		case 3:	// OC5C
			TCCR5A |= 0b00001000;	// 0b----10--
			break;
		case 4:	// OC4A
			TCCR4A |= 0b10000000;	// 0b10------
			break;
		case 5:	// OC3C
			TCCR3A |= 0b00001000;	// 0b----10--
			break;
		case 6:	// OC3B
			TCCR3A |= 0b00100000;	// 0b--10----
			break;			
		case 7:	// OC3A
			TCCR3A |= 0b10000000;	// 0b10------
			break;
		// If given an erroneous index, do nothing.
		default:
			return;
	}
	
}


// Disables PWM for a given fan index
void FanControl::disable_pwm( uint8_t idx ) {
	
	switch( idx ) {
		// Indices 0 through 7: disable the matching fan
		case 0:	// OC4C
			TCCR4A &= 0b11110011;	// 0b----00--
			break;
		case 1: // OC5A
			TCCR5A &= 0b00111111;	// 0b00------
			break;
		case 2:	// OC5B
			TCCR5A &= 0b11001111;	// 0b--00----
			break;
		case 3:	// OC5C
			TCCR5A &= 0b11110011;	// 0b----00--
			break;
		case 4:	// OC4A
			TCCR4A &= 0b00111111;	// 0b00------
			break;
		case 5:	// OC3C
			TCCR3A &= 0b11110011;	// 0b----00--
			break;
		case 6:	// OC3B
			TCCR3A &= 0b11001111;	// 0b--00----
			break;			
		case 7:	// OC3A
			TCCR3A &= 0b00111111;	// 0b00------
			break;
		// If given an erroneous index, do nothing.
		default:
			return;
	}
	
}


// Enables PWM on Test fan header
void FanControl::enable_test_pwm() {
	// Test Pin = OC4B
	TCCR4A |= 0b00100000;
}


// Disables PWM on Test fan header
void FanControl::disable_test_pwm() {
	// Test Pin = OC4B
	TCCR4A &= 0b11001111;
}



/*** GPIO Initializer ***/
void FanControl::init() {
	
	/* I/O Initializations */
	
	// Sets direction for input ports
	port_EN_DIR		= 0x00;
	port_SET_DIR	= 0x00;
	// Disable pull-up resistors
	port_EN_OUT		= 0x00;
	port_SET_OUT	= 0x00;
	// Perform an initial read and load results into their value registers
	switch_en		= port_EN_IN;
	switch_or		= port_SET_IN;
	
	// Sets direction for output ports
	port_PWR_DIR	= 0xFF;
	// Sets pin output value
	port_PWR_OUT	= fan_pwr;
	
	
	
	/* PWM Initializations */
	
	// PWM Pins
	pinMode( p_PWM0, OUTPUT );
	pinMode( p_PWM1, OUTPUT );
	pinMode( p_PWM2, OUTPUT );
	pinMode( p_PWM3, OUTPUT );
	pinMode( p_PWM4, OUTPUT );
	pinMode( p_PWM5, OUTPUT );
	pinMode( p_PWM6, OUTPUT );
	pinMode( p_PWM7, OUTPUT );
	pinMode( p_PWMT, OUTPUT ); // Test PWM
	
	// Default: set outputs to be low when PWM module not activated on pin. 
	// Only way to keep the pin low 100% is to deactivate PWM for said pin.
	digitalWrite( p_PWM0, LOW );
	digitalWrite( p_PWM1, LOW );
	digitalWrite( p_PWM2, LOW );
	digitalWrite( p_PWM3, LOW );
	digitalWrite( p_PWM4, LOW );
	digitalWrite( p_PWM5, LOW );
	digitalWrite( p_PWM6, LOW );
	digitalWrite( p_PWM7, LOW );
	digitalWrite( p_PWMT, LOW );
	
	// Configure Timers for Fast PWM, but leave the individual I/O pins undriven
	// by the PWM module for now. 
	TCCR3A 	= TCCR3A_VAL;
	TCCR4A 	= TCCR4A_VAL;
	TCCR5A 	= TCCR5A_VAL;
	
	TCCR3B 	= TCCR3B_VAL;
	TCCR4B 	= TCCR4B_VAL;
	TCCR5B 	= TCCR5B_VAL;
	
	// Sets the PWM frequency
	ICR3	= ICR3_VAL;
	ICR4	= ICR4_VAL;
	ICR5	= ICR5_VAL;
	
}


/*** Reading Switches and Configuring Outputs ***/

// Reads the ENABLE and OVERRIDE/CLEAR switch states.
void FanControl::read_switches() {
	
	// Simple port reads
	switch_en	= port_EN_IN;
	switch_or	= port_SET_IN;
	
}



// Updates PWM outputs for all fans; factors in Faults, Enables, and Overrides. 
void FanControl::update_outputs() {

	// Tracks the last value of "fan_pwr" when this function was called. If
	// there's a difference between the current value and the old value, I/Os
	// need to be either cleared or re-initialized. 
	static uint8_t last_fan_pwr = 0x00;
	
	
	// Variable Definitions
	uint8_t i    = 0;
	uint8_t diff = 0;
	uint8_t mask = 0;

	// First, clear any Faults if an Override bit is set. 
	fan_fault = fan_fault & ( ~switch_or );
	
	// Next, checks the Enable switches and Fault status to determine which fans
	// get powered on.
	fan_pwr = switch_en & ( ~fan_fault );
	
	
	// If there's a mismatch between "fan_pwr" and "last_fan_pwr", either a fan
	// needs to be powered down (remove signal -> cut power), or a fan needs to 
	// be powered up (apply power -> add signal). 
	diff = fan_pwr ^ last_fan_pwr;
	if( diff ) {
		
		// Iterate the mask up from least significant bit to most significant bit.
		for( i = 0; i < NUM_FANS; i++ ) {
			
			mask = 0x01 << i;
			
			// Check if the mask has aligned with where a difference has occurred.
			// If not, do nothing.
			if( diff & mask ) {
			
				// If now set in "fan_pwr", we need to turn on power to the fan first,
				// then enable the PWM signal. 
				if( fan_pwr & mask ) {
					
					port_PWR_OUT |= mask;
					this->enable_pwm( i );
					
				}
				// Otherwise, we need to disable the PWM first, then cut power to the fan.
				else {
					
					this->disable_pwm( i );
					port_PWR_OUT &= ~mask;
					
				}
				
			}	// if( diff & mask )
			
		} // mask for loop
		
	} // if( diff )
	
	
	// Always enable the Test PWM. Currently have no mechanism to disable it.
	this->enable_test_pwm();
	
	
	// Set PWM outputs to the count quantities corresponding to their duty cycles. 
	// Performing these writes won't do anything if the PWM's disabled.
	// NOTE: with a set duty cycle of 0, there will still be some runt pulses generated.
	// Still, this shouldn't be a problem for your fan controller.
	
	// Fan 0: OC4C
	OCR4C = fan_count[0];
	// Fan 1: OC5A
	OCR5A = fan_count[1];
	// Fan 2: OC5B
	OCR5B = fan_count[2];
	// Fan 3: OC5C
	OCR5C = fan_count[3];
	// Fan 4: OC4A
	OCR4A = fan_count[4];
	// Fan 5: OC3C
	OCR3C = fan_count[5];
	// Fan 6: OC3B
	OCR3B = fan_count[6];
	// Fan 7: OC3A
	OCR3A = fan_count[7];
	// Test Fan: OC4B
	OCR4B = test_count;
	
	
	// Lastly, updates the "last_fan_pwr" variable before exiting the loop.
	last_fan_pwr = fan_pwr;
	
}



/*** Set Functions ***/

// Set the duty cycle [0 to 100] for a given fan index.
void FanControl::set_duty_cycle( uint8_t idx, uint8_t dc ) {
	
	// If the index parameter's out of bounds, exit without doing anything.
	if( idx >= NUM_FANS ) {
		return;
	}
	
	// If the duty cycle's greater than the maximum (100), knock it down to the
	// maximum. 
	if( dc > MAX_DUTY_CYCLE ) {
		dc = MAX_DUTY_CYCLE;
	}
	
	// Save the duty cycle value
	fan_dc[idx] = dc;
	
	// Calculate the corresponding fan counts
	fan_count[idx] = ( MAX_TIMER_COUNT * dc ) / MAX_DUTY_CYCLE;
	
}



// Set the duty cycle [0 to 100] for the test fan.
void FanControl::set_test_duty_cycle( uint8_t dc ) {
	
	// If the duty cycle's greater than the maximum (100), knock it down to the
	// maximum. 
	if( dc > MAX_DUTY_CYCLE ) {
		dc = MAX_DUTY_CYCLE;
	}
	
	// Save the duty cycle value
	test_dc = dc;
	
	// Calculate the corresponding fan counts
	test_count = ( MAX_TIMER_COUNT * dc ) / MAX_DUTY_CYCLE;
	
}



// Sets a fault for a given fan index. 
void FanControl::set_fault( uint8_t idx ) {
	
	// If the index parameter's out of bounds, exit without doing anything.
	if( idx >= NUM_FANS ) {
		return;
	}
	
	fan_fault |= ( 0x01 << idx );
	
}



// Sets faults according to a bitmask. 
void FanControl::set_fault_mask( uint8_t mask ) {
	
	fan_fault |= mask;
	
}



/*** Get Functions ***/

// Returns the most recent Eable switch reading results
uint8_t FanControl::get_enable_switches() {
	
	return switch_en;
	
}



// Return the most recent Override switch reading results
uint8_t FanControl::get_override_switches() {
	
	return switch_or;
	
}



// Return the current fan power status bitmask
uint8_t FanControl::get_power_status() {
	
	return fan_pwr;
	
}



// Returns true if a given fan is turned on.
bool FanControl::is_on( uint8_t idx ) {
	
	// If the index parameter's out of bounds, it's definitely not on
	if( idx >= NUM_FANS ) {
		return false;;
	}
	
	// If the associated bit's set, return a True. 
	if( fan_pwr & ( 0x01 << idx ) ) {
		return true;
	}
	
	// Otherwise, return false
	return false;
	
}



// Returns the current fan fault status bitmask
uint8_t FanControl::get_fault_status() {
	
	return fan_fault;
	
}



// Returns true if a given fan has a fault.
bool FanControl::has_fault( uint8_t idx ) {
	
	// If the index parameter's out of bounds, we'll consider that a fault of its own.
	if( idx >= NUM_FANS ) {
		return true;
	}
	
	// If the associated bit's set, return a True. 
	if( fan_fault & ( 0x01 << idx ) ) {
		return true;
	}
	
	// Otherwise, return false
	return false;
	
}



// Returns a given fan's set duty cycle
uint8_t FanControl::get_duty_cycle( uint8_t idx ) {
	
	// If the index parameter's out of bounds, return a crazy high value
	if( idx >= NUM_FANS ) {
		return 255;
	}
	
	return fan_dc[idx];
	
}



// Returns the test fan's set duty cycle
uint8_t FanControl::get_test_duty_cycle() {
	
	return test_dc;
	
}



// Returns a given fan's computed timer count (MEANT FOR DEBUG ONLY)
uint16_t FanControl::get_count( uint8_t idx ) {
	
	// If the index parameter's out of bounds, return a crazy high value
	if( idx >= NUM_FANS ) {
		return 32767;
	}	
	
	return fan_count[idx];
	
}



// Returns the test fan's computed timer count (MEANT FOR DEBUG ONLY)
uint16_t FanControl::get_test_count() {
	
	return test_count;
	
}