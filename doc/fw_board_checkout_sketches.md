<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a id="readme-top"></a>
<!--
*** Hey there, welcome to my README File. Here's a couple helpful resources for writing up files like this:
*** - VS Code is super hepful for previewing files like this (CTRL + Shift + V).
*** - Alternatively, Notepad++ has a few plugins (e.g. MarkdownViewer++) that can preview files. 
*** - GitHub documentation (good for the basics): https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax
*** - Best-README-Template (lets you do sophisticated things): https://github.com/othneildrew/Best-README-template/blob/main/README.md
-->

<!-- Logo and Title Section -->
<br />
<div align="center">
  <!-- <a><img src="./img/board_populated_circuitmaker_rendering.jpg" alt="Logo" width="400" height="500"></a> -->
  <h3 align="center"><strong>
    Mega2560 Fan Controller <br />    
    Board Checkout Sketches
  </strong></h3>
  
  <p align="center">
    Wil Neeley
    <br />
    2025-05-22
  </p>
</div>


## Overview

So, you've assembled your board, run through the [post-assembly inspection](./hw_post_assembly_inspection.md), [loaded the Arduino bootloader, and uploaded your first sketch](./fw_loading_arduino_bootloader.md). Before you upload the full board control sketch or start writing your own sketches, I recommend uploading and running through the following sketches to make sure everything on your board's fully functional. That way, if your board has a problem, it should be easy to identify and fix!

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## The Sketches

Here's a quick rundown of the sketches I recommend you upload, in the order I recommend you upload them. 

> NOTE: For most of these sketches to work correctly, your board will need 12V power (through J1), especially anything involving the fan headers. 

1. [`01_buzzer_and_led_test`](#sketch-01-buzzer-and-led-test): A very simple first sketch aimed at verifying you can install a program. Validates the following:
    * Microcontroller basic functionality (programming, timing, basic I/O)
    * Buzzer functionality
    * Arduino heartbeat LED (D31) functionality
2. [`02_switches_and_more_leds_test`](#sketch-02-switches-and-more-leds-test): Another fairly simple sketch, this time geared towards assessing multiple I/O pins at once. Validates the following:
    * Reading the following inputs:
        * FAN_EN (SW3)
        * FAN_SET (SW4)
        * TEST_SEL (SW5)
        * TRIGGER (will light up D31)
    * Driving the following outputs:
        * FAN_FAULT LEDs
        * FAN_PWR relays
3. [`03_power_monitor_test`](#sketch-03-power-monitor-test): A third simple sketch that reads the two power diagnostic pins (5V_STAT and 5V_EN) and lights up the FAULT LEDs to indicate which power source is being used. Validates the following signals:
    * 5V_STAT
    * 5V_EN
4. ['04_serial_port_test'](#sketch-04-serial-port-test):  UART Loopback
    * UART receive and transmit
5. Fan PWM and Tachometer Testing
    * Drive fans based on SEL
    * Read tachometer pulses
    * Include TEST signals
6. Temp Sensor Testing
    * Read analog temperature measurements
7. Unused I/O
    * Toggle unused pins
    * Extend UART loopback through extra com port


<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Sketch 01: Buzzer and LED Test

Sketch Location: `fw/examples/01_buzzer_and_led_test`

When uploaded, this sketch causes the LED and buzzer to turn on for one second, turn off for one second, and to repeat that pattern endlessly. 

While not very complicated, it does make sure the microcontroller is functional, can be programmed, can toggle its I/O pins, and that the clock frequency is correct (i.e. not double or half speed). It also verifies the buzzer and the Arduino heartbeat LED (D31, tied to Arduino Pin 13) are functioning as expected.

> NOTE: If the buzzer works and you're finding it annoying, a simple way to eliminate it is to comment out the line that reads `analogWrite(buzzerPin, 127);`. 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Sketch 02: Switches and More LEDs Test

Sketch location: `fw/examples/02_switches_and_more_leds_test`

When uploaded, this sketch will run through a small initialization routine to toggle all LEDs controlled by the microcontroller. After that's complete, it will perform three operations:

1. Read the input trigger signal (high or low) and light up D31 to match its state.
2. Read the Enable and Set (labeled "Override/Clear" on the board) switches, perform a [bitwise](https://en.wikipedia.org/wiki/Bitwise_operations_in_C) logical exclusive-OR ([XOR](https://en.wikipedia.org/wiki/XOR_gate)) operation on them, and display the result on the Fault LEDs. 
3. Read the inputs associated with the Selector switch (SW5) and power on the associated fan (and light up its LED). When the switch is in its home/neutral position, Fan 8 (J18) will be powered on.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


### Sketch 03: Power Monitor Test

Sketch location: `fw/examples/03_power_monitor_test`

When uploaded, this sketch will read the two diagnostic signals (5V_EN and 5V_STAT) coming from the power source selector (U2) and light up the FAULT LEDs with a pattern, depending on which power source is being used. 

| LEDs (1->8) | 5V_STAT | 5V_EN | Source |
| -- | -- | -- | -- |
| 00000001 | 0 | 0 | Power Jack (5V Regulator) |
| 10000010 | 1 | 0 | USB Power |
| 11000100 | 1 | 1 | AVR Power (Bootloader Header) |
| Anything Else | ? | ? | Error state (should't get here) |

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Sketch 04: Serial Port Test

Sketch location: `fw/examples/04_serial_port_test`

When uploaded, this sketch will activate the microcontroller's serial port (UART0) at a baud rate of 115200. If you open up a serial port terminal with the right COM port value and type in a character, the board will do two things:

1. Send the character back to your terminal so you can see it in real time
2. Write the binary value to the FAULT LEDs

While the FAULT LEDs have the least significant bit on the left, this is the opposite