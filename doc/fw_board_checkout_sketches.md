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

Here's a quick rundown of the sketches I recommend you upload, in the order I recommend you upload them. All of them can be found in the `fw/examples` folder.

> [!IMPORTANT]
>
> For most of these sketches to work correctly, your board will need 12V power (through J1), especially for any sketches involving the fan headers. If you're only powering your board through the USB port, you may not get the results you expect.

1. [`01_buzzer_and_led_test`](#sketch-01-buzzer-and-led-test): A simple first sketch aimed at verifying you can install a program. Validates the following:
    * Microcontroller basic functionality (programming, timing, basic I/O)
    * Driving the following outputs:
        * Default Arduino LED (D31)
        * FLT_BUZZER
2. [`02_switches_and_more_leds_test`](#sketch-02-switches-and-more-leds-test): A sketch geared towards assessing multiple I/O pins at once. Validates the following:
    * Reading the following inputs:
        * FAN_EN (SW3)
        * FAN_SET (SW4)
        * TEST_SEL (SW5)
        * TRIGGER
    * Driving the following outputs:
        * FAN_FAULT LEDs
        * FAN_PWR relays
3. [`03_power_monitor_test`](#sketch-03-power-monitor-test): A third simple sketch that reads the two power diagnostic pins (5V_STAT and 5V_EN) and lights up the FAULT LEDs to indicate which power source is being used. Validates the following:
    * Reading the following inputs:
        * 5V_STAT
        * 5V_EN
4. [`04_serial_port_test`](#sketch-04-serial-port-test):  A serial port loopback sketch that shows each received byte on the Fault LEDs (either directly or mirrored to be human-readable). Validates the following:
    * UART receive and transmit
5. [`05_temperature_sensor_test`](#sketch-05-temperature-sensor-test): A sketch geared towards reading the analog signals coming from our external temperature sensors and mapping them to an actual temperature reading. Validates the following:
    * Analog input functionality
6. [`06_fan_pwm_test`](#sketch-06-fan-pwm-test): A sketch that gets to the heart of the board's core functionality: controlling fan speeds through PWM. Validates the following:
    * Driving the following outputs:
        * FAN_PWM (0 through 7 + TEST)
7. [07_fan_tachometer_test`](#sketch_07-fan-tachometer-test): A sketch that sets the fan speeds (either modulated or full speed), lets you select a fan through the TEST SEL rotary switch, and reports the tachometer statistics for the selected fan and the TEST fan over the serial port. Validates the following:
    * Reading the following inputs
        * FAN_TACH (0 through 7 + TEST)
8. Unused I/O
    * Toggle unused pins
    * Extend UART loopback through extra com port


<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Sketch 01: Buzzer and LED Test

When uploaded, this sketch causes the LED and buzzer to turn on for one second, turn off for one second, and to repeat that pattern endlessly. 

While not very complicated, it does make sure the microcontroller is functional, can be programmed, can toggle its I/O pins, and that the clock frequency is correct (i.e. not double or half speed). It also verifies the buzzer and the Arduino heartbeat LED (D31, tied to Arduino Pin 13) are functioning as expected.

> [!TIP]
>
> If the buzzer works and you're finding it annoying, a simple way to eliminate it is to comment out Line 17 (`analogWrite(buzzerPin, 127);`) with two slashes (`//`). 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Sketch 02: Switches and More LEDs Test

When uploaded, this sketch will run through a small initialization routine to toggle all LEDs controlled by the microcontroller. After that's complete, it will perform three operations:

1. Read the input trigger signal (high or low) and light up D31 to match its state.
2. Read the Enable and Set (labeled "Override/Clear" on the board) switches, perform a [bitwise](https://en.wikipedia.org/wiki/Bitwise_operations_in_C) logical exclusive-OR ([XOR](https://en.wikipedia.org/wiki/XOR_gate)) operation on them, and display the result on the Fault LEDs. 
3. Read the inputs associated with the Selector switch (SW5) and power on the associated fan (and light up its LED). When the switch is in its home/neutral position, Fan 8 (J18) will be powered on.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


### Sketch 03: Power Monitor Test

When uploaded, this sketch will read the two diagnostic signals (5V_EN and 5V_STAT) coming from the power source selector (U2) and light up the FAULT LEDs with a pattern, depending on which power source is being used. 

| LEDs (1->8) | 5V_STAT | 5V_EN | Source |
| -- | -- | -- | -- |
| 00000001 | 0 | 0 | Power Jack (5V Regulator) |
| 10000010 | 1 | 0 | USB Power |
| 11000100 | 1 | 1 | AVR Power (Bootloader Header) |
| Anything Else | ? | ? | Error state (should't get here) |

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Sketch 04: Serial Port Test

When uploaded, this sketch will activate the microcontroller's main serial port (UART0) at a baud rate of `115200`. If you connect to the board a serial port terminal (e.g. the Arduino IDE's [built-in Serial Monitor](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-serial-monitor/) or [PuTTY](https://www.putty.org/)) and send it an [ASCII](https://www.ascii-code.com/) character, the board will do two things:

1. Send the character back to your terminal so you can see it in real time
2. Write the binary value to the Fault LEDs output register

> [!IMPORTANT]
>
> The Fault LEDs were placed in ascending order from left to right (`12345678`) so they would match the switches used on the Enable and Override/Clear inputs. However, this direction is opposite of what you'd expect when reading a binary value (ascending order from right to left). By default, the binary value (e.g. `0b01100011` for a lower-case `c`) will appear backwards on the LEDs from what you'd expect (`11000110`). 
>
> I added in a `MIRROR_LEDS` definition that swaps the bit ordering to ascending order from right to left (`76543210`). This has the benefit of making the binary value appear how you expect on the LEDs, but the LED numbering will no longer match the order marked on the PCB (`12345678`). `MIRROR_LEDS` is enabled by default, but if the incongruity with the PCB's markings is bothering you, feel free to comment it out and disable the mirroring effect.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




### Sketch 05: Temperature Sensor Test

When uploaded, this sketch will initialize the temperature sensor lines as analog inputs, sample the voltages at their pins, calculate the corresponding temperatures (assuming you're using an [Analog Devices TMP36](https://www.analog.com/media/en/technical-documentation/data-sheets/tmp35_36_37.pdf) sensor), and output the results as a formatted table over the serial port (`115200` baud rate). 

> [!NOTE]
>
> On the V1 boards, there are no pull resistors on the analog signals coming from the temperature sensors, so the readings aren't biased to anything in particular when the sensor's unplugged. As a result, reading an unplugged sensor will yield fairly random results. For future revisions, I'll be adding some kind of pull resistor right at the signal's input to the board.
>
> I did look into enabling the ATmega2560's built-in pull-up resistors on the analog lines, but unfortunately they don't play nice with the 3k filter resistors, and the temperatures wind up being skewed high (by about 30 degrees C). 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Sketch 06: Fan PWM Test

When uploaded, this sketch does a couple things:
- The ENABLE switches choose which (non-Test) fans get powered on and have a PWM signal generated. 
- The TEST SEL rotary switch lets you pick the fan's PWM duty cycle from 0% (switch position 0) to 100% (home switch position, or spot "7").
- The FAULT LEDs let you know which TEST SEL switch position was selected, and gives you a general duty cycle indicator. 
- The OVERRIDE switches, when switched high, bypass the TEST SEL speed selection and send the selected fan to full speed.

| TEST SEL | LEDs | Duty Cycle | Note |
| -- | -- | -- | -- |
| 0 | 1 | 0% | Actually 0.156% |
| 1 | 2 | 20% | Minimum per [Intel spec](https://www.intel.com/content/dam/support/us/en/documents/intel-nuc/intel-4wire-pwm-fans-specs.pdf) |
| 2 | 3 | 35% | --- |
| 3 | 4 | 50% | --- |
| 4 | 5 | 62% | --- |
| 5 | 6 | 75% | --- |
| 6 | 7 | 88% | --- |
| 7 | 8 | 100% | Full Speed |



<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Sketch 07: Fan Tachometer Test

ASDF

<p align="right">(<a href="#readme-top">back to top</a>)</p>