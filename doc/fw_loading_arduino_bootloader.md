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
    Loading the Arduino Bootloader
  </strong></h3>
  
  <p align="center">
    Wil Neeley
    <br />
    2025-05-20
  </p>
</div>


<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#overview">Overview</a>
      <ul>
        <li><a href="#required-equipment">Required Equipment</a></li>
      </ul>
    </li>
    <li><a href="#loading-the-bootloader">Loading the Bootloader</a></li>
    <li><a href="#verifying-the-bootloader">Verifying the Bootloader</a></li>
    <li><a href="#next-steps">Next Steps</a></li>
  </ol>
</details>



## Overview

So, you've assembled your board, run through the [post-assembly inspection](./hw_post_assembly_inspection.md), and you want to start programming with the Arduino environment. Well, before you can treat it like an Arduino Mega2560 board and start programming it over the USB port, you need to load the Arduino bootloader onto the microcontroller through the AVR header. For more information on what a bootloader is, check out [this article](https://docs.arduino.cc/retired/hacking/software/Bootloader/).

> NOTE: If you somehow managed to install a microcontroller pre-loaded with the Arduino Mega 2560 bootloader, you can skip these steps!

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Required Equipment

The specific parts can be tweaked, but there are some core essentials you'll need:

* An AVR In-circuit Serial Programmer (ISP); there's multiple options out there
    * What I use: Sparkfun [Pocket AVR Programmer](https://www.sparkfun.com/pocket-avr-programmer.html)
    * With some work, you can use an [Arduino Uno as an AVR ISP](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP/). Just note that you'll be tapping into the equivalent of the Arduino Mega2560 board's "ICSP" header. 
* Wires/jumpers to connect your AVR ISP to the Mega2560 Fan Controller board
    * I use SparkFun's [AVR Programming Cable](https://www.sparkfun.com/avr-programming-cable.html)
    * I also use Sparkfun's [ISP Pogo Adapter v2](https://www.sparkfun.com/sparkfun-isp-pogo-adapter-v2.html) so I don't have to install a connector in J5, which makes the board look a little cleaner.
* A computer with the following installed: 
    * [Ardunio IDE](https://www.arduino.cc/en/software/)
        * Can be Windows, Mac, or Linux
        * I recommend just installing the newest version (2.3.6 as of 2025-05-20)
        * v1.5.8 or newer "required" (I'm seeing a fix to the Mega2560's flash allocation in this version)
    * [FTDI Virtual COM Port (VCP) Drivers](https://ftdichip.com/drivers/vcp-drivers/)
        * The Arduino IDE sometimes installs these drivers for you. If not, you can either work with the Arduino IDE to get them installed, or you can go to FTDI directly (i.e. the link I provided).
    * AVR ISP Drivers
        * Sparkfun Pocket AVR Programmer: go through Adafruit for their [USBtinyISP drivers](https://github.com/adafruit/Adafruit_Windows_Drivers/releases/tag/2.5.0.0)
* USB cables to connect the following devices to your computer: 
    * AVR ISP
    * Mega2560 Fan Controller

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Loading the Bootloader

Use the following steps to install the bootloader. For more resources, you can consult the [Arduino as ISP article](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP/) or a number of other Arduino-related resources. There's a lot out there.

1. Connect your AVR ISP to your computer. If needed, install drivers.
2. Open the Arduino IDE. 
3. Under `Tools -> Board`, select `Arduino AVR Boards -> Arduino Mega or Mega 2560`.
4. Under `Tools -> Processor`, select `ATmega2560 (Mega 2560)`.
5. Under `Tools -> Programmer`, select your appropriate in-circuit programmer. 
    * Sparkfun Pocket AVR Programmer: `USBtinyISP`
    * Arduino Uno as ISP: `Arduino as ISP`
6. Connect your AVR ISP to the Mega2560 Fan Controller board at J5.
    * As far as pinouts are concerned, J5 is equivalent to the ICSP header found on the Arduino Uno or Arduino Mega 2560. 
7. Under `Tools`, select `Burn Bootloader`. Allow it to run until it's done. LED D31 should start blinking.
    * Using the Sparkfun Pocket AVR Programmer, I kept getting the following error. However, in practice, the bootloader appeared to be installed just fine.
    ```
    avrdude: verification error, first mismatch at byte 0x3e000
            0xff != 0x0d
    avrdude: verification error; content mismatch
    Failed to burn bootloader: uploading error: exit status 1
    ```
8. Disconnect the AVR ISP from both your computer and the Mega2560 Fan Controller board. 

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Verifying the Bootloader

With the bootloader installed, you should be able to program your Mega2560 Fan Controller board as though it was a standard Arduino Mega 2560 board. We'll verify your bootloader was installed correctly by loading a very simple sample program. 

1. In the Arduino IDE, open (`File -> Open...`) the `buzzer_and_led_test` sketch (`[repo root]\fw\examples\buzzzer_and_led_test\buzzer_and_led_test.ino`).
2. Verify the following settings are still set from the **Loading the Bootloader** section:
    * `Tools -> Board -> Arduino AVR Boards -> Arduino Mega or Mega 2560`
    * `Tools -> Processor -> ATmega2560 (Mega 2560)`.
3. Plug your Mega2560 Fan Controller board into your computer.
    * If you see any pop-ups related to installing drivers, LET THEM FINISH BEFORE YOU PROCEED. 
4. Under `Tools -> Port`, select the appropriate COM port number for your board (e.g. `COM4`)
    * If you don't have any boards with COM ports plugged in, there should only be one option.
    * IF you have multiple COM port options, you can use utilities like the Windows Device Manager to figure out which device each COM port number belongs to. 
    * If you aren't seeing any options, you may have to sort out your FTDI drivers. Still, I'd recommend unplugging and replugging your board first to see if that fixes it. 
5. Click the `Upload` button (the right arrow next to the checkmark) to compile and upload your program. If it's successful, you sould see text like the following: 
```
Sketch uses 1582 bytes (0%) of program storage space. Maximum is 253952 bytes.
Global variables use 9 bytes (0%) of dynamic memory, leaving 8183 bytes for local variables. Maximum is 8192 bytes.
```

Your board should now have the buzzer and LED D31 turning on for a second, then turning off for a second. If so, your bootloader's been verified, and you're ready to get to programming!

> NOTE: if that buzzing sound is getting annoying, insert two slashes (`//`) in front of Line 12 (`analogWrite(buzzerPin, 127);`) to comment out the line that creates the buzzing sound, and re-upload the program. LED D31 should still be blinking, but your board should be quiet.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Next Steps

Now that your bootloader's installed, you can program your board with whatever Arduino sketches you want! That said, here are a couple recommendations:
* Read through the [Board Checkout Sketches](./fw_board_checkout_sketches.md) document for additional sketches to make sure your board's fully functional. 
* Check out other example sketches in the `[repo root]/fw/examples` folder, and start playing with them to make the board do what you want.
* Upload my full fan controller program (name TBD) and just start using it!

<p align="right">(<a href="#readme-top">back to top</a>)</p>