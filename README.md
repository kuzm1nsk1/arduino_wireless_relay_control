# arduino_wireless_relay_control

This project uses nRF24L01 transceiver to establish wireless communication between 2 Arduino-based devices. One board acts as a transmitter (remote control), while the other functions as a receiver (relay module). Remote control can turn on or off 6 individual relays with the distance of roughly 70 meters. RGB LEDs on relay module indicate state of each relay, red meaning off and green meaning on.

## Features
- RF communication between the devices, up to 100 meters in ideal conditions
- switch loads up to 125VAC, 2A
- remote control with six pushbuttons
- visual indication of relay states with RGB LEDs
- transmitter and receiver can be powered with 7-24VDC

## Hardware requirements
### Transmitter
- Arduino-based board (Croduino Basic 2)
- nRF24L01 transceiver
- 6 pushbuttons
- 9V battery with a connector
- 10uF electrolytic capacitor
- toggle switch
- perfboard 7x9cm

### Receiver
- Arduino-based board (Croduino Basic 2)
- nRF24L01 transceiver
- 6 relays (OMRON G5V-2)
- 6 RGB CA LEDs
- 6 transistors (2N2222A)
- 6 diodes (1N4007)
- 6 resistors 4k7
- 12 resistors 220R
- 6 3pin screw terminals
- 2pin screw terminal
- perfboard 8x12cm

## Software Requirements
- Arduino IDE or Visual Studio Code

### Required libraries
- SPI communication: https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/SPI
- nRF24L01: https://github.com/nRF24/RF24 <br><br>

## Wiring and Schematics
**Transmitter schematic**
![transmitter](https://github.com/user-attachments/assets/c3b0d3cd-7b0f-424c-90ef-57980a7073b7)
<br><br><br>
**Receiver schematic**
![receiver](https://github.com/user-attachments/assets/2467aeb5-3e98-4239-8a94-25c952c33488)
<br><br><br>
## Troubleshooting  
**Transmitter and receiver boards**
![transmitter_receiver_board](https://github.com/user-attachments/assets/c3724b30-df50-441b-a285-bb14e072c283)
<br><br><br>
**Problem:** unreliable communication between the devices <br>
**Solution:** add 10uF capacitor near nRF24L01 power pins
<br><br><br>
## Usage
**Transmitter board**
![transmitter_board](https://github.com/user-attachments/assets/bcc2b8d3-5728-471a-9204-500ace57e75f)
<br><br><br>
**Receiver board**
![receiver_board](https://github.com/user-attachments/assets/45325f86-045c-4d97-be06-2272136d49f2)

- short press of a button turns on or off a specific relay
- long press of a button turns on a specific relay for 10 seconds
- holding the two buttons on the right turns on all relays
- holding the two buttons on the left turns off all relays
