# IoT Web Server with LED Control

This project demonstrates the implementation of a simple IoT-based web server using an ESP8266 Wi-Fi module. The web server allows users to control an LED remotely through a web interface over the internet or locally within the network. 

## Project Objective
The main goal is to set up a web server on the ESP8266 module, allowing users to control the state of an LED (on/off) through a web interface from anywhere, either via the internet or locally.

## Key Features
- **Local and Remote Control:** The LED can be controlled both locally via the network and remotely through an internet connection.
- **Station Mode (STA):** The ESP8266 operates in Station mode and connects to an existing Wi-Fi access point, making it accessible via a web interface.
- Indirect Access via a Proxy Server
- **Adjustable ON/OFF Timing:** Users can set custom durations for turning the LED on and off through a web interface.
- Control household appliances using a relay module.
- Receive commands via Telegram for more advanced IoT control.

## Technologies Used
- **Hardware:** ESP8266 Wi-Fi Module, LED, Relay Module (optional)
- **Software:** Arduino IDE, HTML, and C++ for ESP8266 programming
- **Network Communication:** HTTP protocol for web-based control

This project is an excellent example of how to build a simple IoT-based web server using ESP8266 to control devices remotely, showcasing basic IoT concepts and web-based control interfaces.
