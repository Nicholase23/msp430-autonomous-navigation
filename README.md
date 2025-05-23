# MSP430 Autonomous Navigation Project

This project implements an embedded system for autonomous navigation using the **MSP430FR2355** microcontroller. Designed as part of an academic assignment, it integrates multiple subsystems to enable a robot to follow lines, detect obstacles, and respond to environmental changes through programmed escape routines.

## Features

- **Line Following** using analog-to-digital conversion (ADC)
- **Obstacle Detection** and movement analysis
- **Escape Routines** for navigating around obstacles
- **Display Integration** for user feedback
- **Serial Communication** via eUSCI interface
- **Interrupt-driven Architecture** using timers and ports
- Modular codebase for clarity and maintainability

## Technologies

- **Platform**: TI MSP430FR2355
- **Language**: C
- **Tools**: Code Composer Studio (CCS), TI Driver Libraries
- **Architecture**: Real-time embedded design using timers, interrupts, and low-level I/O

## File Structure

- `adc_line.c` – Line detection using ADC  
- `Escape_Route.c`, `Check_Movement.c` – Movement logic and route planning  
- `IOT_Process.c` – Communication handling  
- `Create_Display.c` – Display output routines  
- `interrupts_timers.c`, `interrupt_ports.c` – Interrupt service routines  
- `clocks.c`, `init.c` – System initialization and clock setup  

## Getting Started

To build and run the project:

1. Open Code Composer Studio (CCS).
2. Import the project folder.
3. Connect the MSP430FR2355 development board.
4. Build and flash the firmware.

## License

This project was developed for educational purposes. Feel free to use and modify for non-commercial applications.
