### Project Overview  
This project implements AUTOSAR-compliant Port, DIO, GPT drivers, and a custom NVIC driver, adhering to AUTOSAR standard 4.0.3. These drivers provide essential functionality for configuring microcontroller port pins, managing digital input/output, handling timers, and controlling interrupts. A simple application demonstrates their usage, running on a lightweight operating system with tasks triggered at predefined intervals.

### Project Components
- **Port Driver (AUTOSAR 4.0.3)**: Configures and manages microcontroller port pins.
- **DIO Driver (AUTOSAR 4.0.3)**: Manages digital input/output to interface with external devices and sensors.
- **GPT Driver (AUTOSAR 4.0.3)**: Handles timers for time-based operations.
- **NVIC Driver (Irq.h, Irq.c)**:  
  - Custom driver for interrupt control, enabling/disabling specific IRQ numbers.  
  - Manages IRQ priority levels and handles ARM system/fault exceptions (enable/disable and priority settings).  
  - Note: This is not an AUTOSAR driver.
- **Simple Application**: Demonstrates time-based task activation using the provided drivers.
- **Lightweight OS**: Handles task scheduling and timing.

### Setup Instructions
1. **Hardware Requirements**: Ensure compatibility with your microcontroller platform.
2. **Software Setup**: Use Code Composer Studio (CCS) for development and debugging.
3. **Driver Configuration**: Adjust settings like pin mappings, timers, and IRQ numbers to suit your hardware.
4. **Build and Debug**: Compile and debug using CCS, then flash the microcontroller.
5. **Execution**: Test the application on your hardware platform to validate functionality.

### AUTOSAR Documentation  
For more information on AUTOSAR standard 4.0.3, refer to the official AUTOSAR documentation.

### Usage Breakdown  
- **Port Driver**: Configure pins for input/output or alternate functions.
- **DIO Driver**: Manage digital I/O to interact with external hardware.
- **GPT Driver**: Schedule tasks using precise timers.
- **NVIC Driver**:  
  - Control interrupts and set IRQ priorities.  
  - Manage ARM system/fault exceptions.
- **Application Logic**: Explore the provided application to integrate and expand the drivers based on your project needs.
- **OS Integration**: Utilize the lightweight OS for time-based task coordination.
