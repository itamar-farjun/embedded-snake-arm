# MCB-STR9 Embedded Interactive LCD Game

This project is an embedded C application developed for the Keil MCB-STR9 evaluation board based on the ARM9 (STR91x) microcontroller architecture.

The system implements a real-time interactive LCD game utilizing multiple hardware peripherals including GPIO, ADC, and a 16x2 character LCD display.

## Features
- Real-time gameplay on a 16x2 LCD display
- Player-controlled movement using GPIO push buttons (UP/DOWN)
- Dynamic difficulty adjustment using ADC input (potentiometer)
- Score and life tracking system
- Visual feedback using onboard LEDs
- Game-over state with score display

## Hardware Platform
- Keil MCB-STR9 Evaluation Board (STR91x ARM9 microcontroller)
- 16x2 Character LCD
- GPIO push buttons
- ADC potentiometer input
- Onboard LEDs

## Technical Highlights
- Bare-metal embedded C programming
- Direct hardware register manipulation
- ADC sampling for analog input control
- GPIO-based input handling
- Real-time loop-based game logic

## What I Learned
- Low-level embedded system programming on ARM architecture
- Working with ADC, GPIO, and LCD peripherals
- Real-time system design constraints
- Debugging hardware-dependent C code
- Integrating multiple peripherals into a single embedded application
