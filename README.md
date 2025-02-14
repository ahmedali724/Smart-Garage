Here's the updated README file with sections for HAL and MCAL layers:

---

# Smart Garage System

## Overview

This project implements a smart garage system that automates the detection and management of cars inside a garage. The system features:

- Automatic car detection.
- A servo motor-controlled garage door.
- A smart lighting system based on values of LDR (Light Dependent Resistor).
- A password-protected entry system.
- An LCD to show the number of cars in the garage.

## Features

1. **Car Detection**: The system automatically detects cars entering or leaving the garage.
2. **Garage Door Control**: The garage door is controlled by a servo motor, which opens or closes the door based on the number of cars in the garage and a password entry.
3. **Smart Lighting**: The lighting system inside the garage is controlled by an LDR sensor, adjusting the lights based on ambient light conditions.
4. **LCD Display**: An LCD shows the current number of cars in the garage.
5. **Password Protection**: Entry to the garage is secured by a password system.

## Components

- **Servo Motor**: Controls the opening and closing of the garage door.
- **LDR Sensor**: Detects ambient light levels to control the lighting system.
- **LCD Display**: Shows the number of cars in the garage.
- **Microcontroller**: Manages all the sensors, controls the servo motor, and handles the password system.
- **Car Detection Sensor**: Detects the presence of cars entering or leaving the garage.

## Usage

1. **Start the System**: Power on the system.
2. **Enter Password**: Input the correct password to operate the garage door.
3. **Car Detection**: The system automatically detects cars entering or leaving the garage.
4. **Garage Door Operation**: The door will open if the password is correct and the garage is not full. It will remain closed if the garage is full.
5. **Lighting Control**: The lighting system will adjust based on the LDR sensor readings.
6. **Monitor LCD**: Check the number of cars displayed on the LCD.

## HAL (Hardware Abstraction Layer)

The HAL layer abstracts the hardware-specific details, making the application code more portable and easier to maintain. The following drivers are included in the HAL layer:

- **KEYPAD**: Manages the input from the keypad used for password entry.
- **LAMP**: Controls the lighting system inside the garage.
- **LCD**: Manages the display of information on the LCD.
- **LDR**: Reads the ambient light level to adjust the lighting system.
- **SERVO_MOTOR**: Controls the opening and closing of the garage door.

## MCAL (Microcontroller Abstraction Layer)

The MCAL layer provides an interface to the microcontroller's peripherals, allowing the HAL and application layers to interact with the hardware. The following drivers are included in the MCAL layer:

- **ADC**: Analog-to-Digital Converter driver used for reading the LDR sensor.
- **EXTERNAL_INTERRUPT**: Manages external interrupts for detecting cars.
- **GPIO**: General Purpose Input/Output driver for managing pins used by the keypad, LCD, servo motor, and other peripherals.
- **TIMER0**: Timer driver used for various timing operations within the system.

## Schematic

![image](https://github.com/ahmedali724/Smart-Garage/assets/111287464/470e8b4f-7343-4af4-be3e-f33d518e9896)
