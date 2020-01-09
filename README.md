# ESP32-WIRELESS-MIDI
A guide for utilization of ESP32 as a DIN-5 MIDI to wireless MIDI over bluetooth. ESP32 is a Low power device that can be powered from both 5V (Develpoment board) or 3.3V off the midi bus. The ESP reads the MIDI messages from serial/UART 2 and relays the messages over bleutooth MIDI. An optocoupler can be added but is not mandatory. The code is developed with Arduino IDE

UART 2
Rx: GPIO 16
Tx: GPIO 17


# Tools
Arduino IDE:  Compiler for the code

nRF Connect:  For connecting to unofficial bluetooth devices on IOS devices.

# Prerequisites:
https://github.com/espressif/arduino-esp32  - Arduino core for the ESP32
