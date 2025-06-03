/************************
 * Fan Control Class Header File
 * Wil Neeley
 * May 30, 2025
 *
 * A class designed to read the Enable and Override switches, turn on and off
 * the fans, and set their speeds. 
 *
 * Gets into some pretty low-level direct register writes to set up and control
 * the output PWM modules. The AVR-specific register definitions for Arduino can
 * be found here (adjust the [USER] parameter for your particular installation):
 * C:\Users\[USER]\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\cores\arduino
 */


#ifndef FAN_CONTROL_CLASS_H
#define FAN_CONTROL_CLASS_H



/*** Includes ***/
#include <Arduino.h>



/*** Definitions ***/

// Fan Number Definition
#define NUM_FANS	8		// Doesn't count the test fan, which is treated separately.

// Max Timer Count
// Assuming clock is truly 16MHz, we're targeting 25kHz; 16MHz/25kHz = 640; subtract 1 for starting at 0.
#define MAX_TIMER_COUNT		639

// Max Duty Cycle
// User-facing functions can specify a PWM duty cycle between 0 and this value. 
// Setting it at 100 makes the parameter passed in equivalent to a percentage.
#define MAX_DUTY_CYCLE		100


/*** Register Value Definitions ***/
// There's enough here; I'll include a separate section. 

// TCCRnA: Timer/Counter N, Control Register A
// Settings dependent on Compare Output Mode; in this case, going with Fast PWM
// 0b10------ : Clear output A on compare match, set at Bottom (non-inverting mode)
// 0b--10---- : Clear output B on compare match, set at Bottom (non-inverting mode)
// 0b----10-- : Clear output C on compare match, set at Bottom (non-inverting mode)
// 0b000000-- : Turn off all three PWMs; the default load state.
// 0b------10 : WGMn1:0; want "10" as part of Fast PWM
#define TCCR3A_VAL 	0b00000010
#define TCCR4A_VAL	0b00000010
#define TCCR5A_VAL	0b00000010

// TCCRnB: Timer/Counter N Control Register B
// 0b0------- : Input Capture Pin noise filter; 0 leaves it deactivated
// 0b-0------ : Input Capture Edge Select; we don't care here, so leave at 0
// 0b--0----- : Reserved; leave 0
// 0b---11--- : WGMn3:2; we want "11" as part of Fast PWM
// 0b-----001 : Clock Select; 001 = I/O clock with no divider
#define TCCR3B_VAL	0x19
#define TCCR4B_VAL	0x19
#define TCCR5B_VAL	0x19

// TCCRnC: Timer/Counter N Control Register C
// Only matters when WGMn3:0 is a non-PWM mode, which isn't applicable here

// TCNTn: Timer/Counter N
// Don't need to do anything here, so leave it be

// ICRn: sets the frequency
// Assuming clock truly is 16MHz, we're targeting 25kHz; 16MHz/25kHz = 640; subtract 1
#define ICR3_VAL	MAX_TIMER_COUNT
#define ICR4_VAL	MAX_TIMER_COUNT
#define ICR5_VAL	MAX_TIMER_COUNT



/*** Class Definition ***/

class FanControl {
	private:
		// Enable and Override Switch state variables
		uint8_t  switch_en;	// ENABLE switches (SW3)
		uint8_t  switch_or;	// OVERRIDE/CLEAR switches (SW4)
		
		// Fan state variables
		uint8_t  fan_pwr; 				// Fan power status bitfield (1 = on, 0 = off)
		uint8_t  fan_fault;				// Tracks fan faults; set externally, cleared internally (OVERRIDE/CLEAR switches).
		uint8_t  fan_dc[NUM_FANS];		// Commanded duty cycle for a given fan	
		uint8_t  test_dc;
		uint16_t fan_count[NUM_FANS];	// Count compare value loaded into the timer
		uint16_t test_count;
		
		// Internal fan enable/disable functions. Not intended to be externally accessed.
		void enable_pwm( uint8_t idx );
		void disable_pwm( uint8_t idx );
		void enable_test_pwm( );
		void disable_test_pwm( );
	
	public:
		// Constructor
		FanControl();
		
		// I/O Initializer
		void init();
		
		// Switch reads
		void read_switches();
		
		// Update Outputs
		void update_outputs();
		
		// Set Functions
		void    set_duty_cycle( uint8_t idx, uint8_t dc );
		void    set_test_duty_cycle( uint8_t dc );
		void    set_fault( uint8_t idx );
		void    set_fault_mask( uint8_t mask );		
		
		// Get Functions
		uint8_t get_enable_switches();
		uint8_t get_override_switches();
		uint8_t get_power_status();	
		bool    is_on( uint8_t idx );
		uint8_t get_fault_status();
		bool    has_fault( uint8_t idx );
		uint8_t get_duty_cycle( uint8_t idx );
		uint8_t get_test_duty_cycle( );
		uint16_t get_count( uint8_t idx );	// MEANT FOR DEBUG ONLY
		uint16_t get_test_count();			// MEANT FOR DEBUG ONLY		
		
};



#endif // FAN_CONTROL_CLASS_H