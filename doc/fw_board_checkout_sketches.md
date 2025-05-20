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

1. [`buzzer_and_led_test`](#buzzer-and-led-test): A very simple first sketch aimed at verifying you can install a program. Validates the following:
    * Microcontroller basic functionality (programming, timing, basic I/O)
    * Buzzer functionality
    * Arduino heartbeat LED (D31) functionality
2. LED Effects
    * Reading the following inputs:
        * FAN_EN (SW3)
        * FAN_SET (SW4)
        * TEST_SEL (SW5)
        * TRIGGER (will light up D31)
    * Driving the following outputs:
        * FAN_FAULT LEDs (binary XOR of EN and SET)
        * FAN_PWR relays (turn one on based on TEST_SEL)
3. Power Monitoring
    * 5V_STAT
    * 5V_EN
4. UART Loopback
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



### Buzzer and LED Test

Sketch Location: `fw/examples/buzzer_and_led_test`

When uploaded, this sketch causes the LED and buzzer to turn on for one second, turn off for one second, and to repeat that pattern endlessly. 

While not very complicated, it does make sure the microcontroller is functional, can be programmed, can toggle its I/O pins, and that the clock frequency is correct (i.e. not double or half speed). It also verifies the buzzer and the Arduino heartbeat LED (D31, tied to Arduino Pin 13) are functioning as expected.

If your buzzer's not buzzing or your LED's not blinking, but you were able to successfully program your microcontroller, try re-examining your solder joints on the following components. 
* Buzzer: BZ1, R17, and U4
* LED: D31, R21, and U4

<p align="right">(<a href="#readme-top">back to top</a>)</p>