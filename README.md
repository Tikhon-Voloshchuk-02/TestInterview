# Embedded Systems – Technical Assignment

## Overview

This repository contains my solution for the technical assignment for the Working Student position at B. Braun Miethke.

The assignment involves an Android application communicating via Bluetooth Low Energy (BLE) with an nRF52840 main microcontroller, which communicates with a PIC16LF18346 secondary microcontroller connected to an RV-3028-C7 real-time clock (RTC).

## Repository Structure

- `firmware/secondary_mcu/` – C-like firmware pseudocode for the secondary microcontroller.
- `Solution_for_InterviewTest_Voloshchuk_Tikhon.pdf` – System architecture, diagrams and design documentation.

## Implemented Design

The proposed firmware logic covers:

- RTC initialization and time read/write operations.
- Communication between the main and secondary microcontrollers.
- Processing of time-related commands.
- Periodic RTC timer events and LED control.
- Separation of hardware access, communication and application logic.

## Implementation Status

The secondary MCU implementation is written as hardware-independent C-like pseudocode.

Hardware-specific drivers and actual communication interfaces are represented by abstractions and have not been implemented or tested on physical hardware.

The Android BLE application has not been implemented.

## Further Development

The next steps would be:

1. Implement and validate the hardware-specific firmware drivers.
2. Define and implement the BLE GATT service and characteristics.
3. Develop an Android application for sending commands and displaying RTC data.
