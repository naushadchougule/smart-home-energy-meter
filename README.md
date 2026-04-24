# Smart Home Energy Meter using Arduino

## Overview
This project presents a basic energy monitoring system developed using Arduino. It measures the current drawn by a load and calculates the corresponding power consumption in real time. The calculated values are displayed on an LCD, allowing continuous observation of electrical usage.

The system is designed to demonstrate how electrical parameters can be measured and processed using embedded systems. It can also be extended to support IoT-based monitoring using modules like ESP8266.

## Components Used
- Arduino Uno
- ACS712 Current Sensor
- LCD Display (Keypad Shield)
- ESP8266 (optional)
- Breadboard and jumper wires

## Hardware Setup

Reference Setup:
![Hardware Setup](images/reference_hardware_setup.png)

Output Display:
![LCD Output](images/lcd_output.jpg)

## Working Principle
The ACS712 current sensor produces an analog output proportional to the current flowing through the load. This signal is read by the Arduino.

The microcontroller processes the signal to calculate current and power using:
P = V × I

The results are displayed continuously on the LCD.

## Features
- Real-time monitoring
- Simple and low-cost system
- Easy to implement
- Expandable for IoT

## Applications
- Home energy monitoring
- Educational projects
- Load analysis

## Limitations
- Accuracy depends on calibration
- Assumes constant voltage
- Does not measure voltage directly

## Author
Naushad
