# Subway Station Simulator

A simulated subway line built with Arduino, developed and prototyped in Tinkercad. The simulation cycles through four stations, controlling a 7-segment display, a servo motor, status LEDs, and a buzzer to represent train arrivals and departures.

## Features
- Finite-state machine managing bidirectional progression across 4 stations plus a "traveling" state
- 7-segment display driven directly via individual segment pins (no external display library)
- Servo motor simulating door opening/closing at each station
- Status LEDs with a blinking sequence on arrival, plus a buzzer alert
- Debounced push-button input to start/stop the simulation reliably

## Hardware Requirements
- Arduino Uno (or compatible)
- Servo motor
- 7-segment display (common configuration, individually wired segments)
- 4 status LEDs (one per station)
- Buzzer
- Push button

## Simulation
Built and tested in Tinkercad: https://www.tinkercad.com/things/gmrp41MHZvm-subway-station-simulator?sharecode=LtbeJKsYYnLEuoehBVmfaW8iZVNGrBHo4cpELH547Yg

## Author
Nicolás Martinez Kioso
