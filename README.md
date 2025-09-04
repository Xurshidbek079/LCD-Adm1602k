# STM32F411 HD44780 LCD Driver

A bare-metal C driver for interfacing HD44780-compatible LCD displays with STM32F411 microcontrollers using 4-bit mode communication.

## Features

- **4-bit mode LCD interface** - Reduces GPIO pin usage
- **Hardware abstraction** - Clean separation between hardware and application layers
- **Modular design** - Well-organized code structure with separate modules
- **Bare-metal implementation** - No external libraries or HAL dependencies
- **SysTick-based timing** - Precise delay functions using system timer
- **Debug LED support** - Visual feedback for development and debugging

## Hardware Requirements

### Microcontroller
- STM32F411 series microcontroller
- External 25 MHz crystal oscillator (HSE)
- System configured to run at 50 MHz

### LCD Display
- HD44780-compatible 16x2 or 20x4 character LCD
- 5V or 3.3V compatible display

### Connections

| STM32F411 Pin | LCD Pin | Function |
|---------------|---------|----------|
| PA0           | RS      | Register Select |
| PA1           | R/W     | Read/Write |
| PA2           | E       | Enable |
| PB4           | DB4     | Data Bit 4 |
| PB5           | DB5     | Data Bit 5 |
| PB6           | DB6     | Data Bit 6 |
| PB7           | DB7     | Data Bit 7 |
| PC13          | -       | Debug LED (optional) |

### Power Connections
- LCD VDD → 5V or 3.3V
- LCD VSS → GND
- LCD V0 → Contrast adjustment (potentiometer between VDD and GND)

## File Structure

```
stm32f411-lcd-driver/
├── main.c              # Main application
├── system.c/.h         # System configuration and timing
├── lcd.c/.h            # LCD driver implementation
├── debug.c/.h          # Debug LED control
├── startup.c           # Vector table and startup code
├── stm32f411xx.h       # Device register definitions
├── Makefile            # Build configuration
├── datasheets/         # Hardware documentation
│   ├── STM32F411xx.pdf # STM32F411 Reference Manual
│   └── HD44780.pdf     # HD44780 LCD Controller Datasheet
└── README.md           # This file
```

## Project Configuration

### Clock Configuration
- **Source:** HSE (25 MHz external crystal)
- **System Clock:** 50 MHz (via PLL)
- **AHB Clock:** 50 MHz
- **APB1 Clock:** 25 MHz
- **APB2 Clock:** 50 MHz

### Memory Layout
Ensure your linker script (`stm32f411.ld`) matches your STM32F411 variant:
- **STM32F411CE:** 512KB Flash, 128KB RAM
- **STM32F411RE:** 512KB Flash, 128KB RAM

## Documentation

### LCD Module Datasheet
The repository includes the complete LCD module datasheet:

- **Datasheet-LCD-Adm1602k-Nsw-Fbs-3-3v.pdf** - ADM1602K 16x2 LCD module specification containing:
  - Pin configuration and electrical characteristics
  - HD44780 controller command set and timing requirements
  - 4-bit interface protocol implementation
  - Character set and display memory organization
  - Power supply specifications (3.3V operation)
  - Mechanical dimensions and mounting details
  - Initialization sequence and operational parameters

This datasheet is the primary reference for understanding the LCD module's hardware interface, timing requirements, and proper initialization procedures used in this driver implementation.

## Hardware Variants

This driver is designed for STM32F411 series. For other STM32 families:
- Update register definitions in `stm32f411xx.h`
- Adjust clock configuration in `system.c`
- Modify GPIO pin assignments if needed
