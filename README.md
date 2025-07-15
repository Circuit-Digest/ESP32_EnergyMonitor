# DIY Real-Time Energy Monitoring Device using ESP32

A comprehensive power consumption monitoring system that measures voltage, current, instantaneous power, and energy consumption in real-time using ESP32 microcontroller and sensor modules.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Components Required](#components-required)
- [Hardware Setup](#hardware-setup)
- [Software Setup](#software-setup)
- [Circuit Diagram](#circuit-diagram)
- [Code Explanation](#code-explanation)
- [Assembly Instructions](#assembly-instructions)
- [Calibration Process](#calibration-process)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

## Overview

This project creates a smart power consumption monitoring device that can be inserted between any AC appliance and wall socket to measure real-time energy consumption. The device displays voltage, current, instantaneous power, and cumulative energy consumption on an OLED display, cycling through different screens automatically.

**Original Tutorial**: [DIY Real-Time Energy Monitoring Device using ESP32](https://circuitdigest.com/microcontroller-projects/diy-real-time-energy-monitoring-device-using-esp32)

## Features

- **Real-time monitoring** of voltage, current, and power consumption
- **Multi-screen display** showing different parameters
- **Energy consumption tracking** with units calculation
- **Automatic screen switching** every 5 seconds
- **Calibration support** for accurate readings
- **Compact design** with 3D printed enclosure
- **Safe isolation** up to 4000V with ZMPT101B sensor

## Components Required

| Component | Quantity | Description |
|-----------|----------|-------------|
| ESP32 WROOM 32D Module | 1 | Main microcontroller |
| HI LINK 5V 3W SMPS | 1 | Power supply module |
| 0.96" 128X64 I2C OLED Display | 1 | Display unit |
| ZMPT101B Voltage Sensor | 1 | AC voltage measurement |
| ACS712 20A Current Sensor | 1 | Current measurement |
| 220V AC 3 Pin Socket (Male) | 1 | Input connection |
| 220V AC 3 Pin Socket (Female) | 1 | Output connection |
| 3D Printed Casing | 1 | Protective enclosure |

## Hardware Setup

### Pin Connections

| ESP32 Pin | Component | Connection |
|-----------|-----------|------------|
| Pin 34 | ZMPT101B | Analog Output |
| Pin 36 (VP) | ACS712 | Analog Output |
| Pin 21 (SDA) | OLED Display | I2C Data |
| Pin 22 (SCL) | OLED Display | I2C Clock |
| 5V | All Components | Power Supply |
| GND | All Components | Ground |

### Power Supply Connections

- **HI-Link SMPS**: Connected in parallel with AC Live and Neutral
- **ZMPT101B**: Input terminals connected in parallel with AC supply
- **ACS712**: Connected in series with AC Live wire
- **All components**: Powered by 5V output from HI-Link module

## Software Setup

### Required Libraries

Install the following libraries through Arduino IDE Library Manager:

1. **Adafruit GFX Library**
2. **Adafruit SSD1306 Library**
3. **ZMPT101B Library** (Custom - download from GitHub)
4. **ACS712 Library** (Custom - download from GitHub)

### Library Installation Steps

1. Open Arduino IDE
2. Go to **Tools → Library Manager**
3. Search and install Adafruit libraries
4. For custom libraries:
   - Download ZIP files from GitHub repositories
   - Go to **Sketch → Include Library → Add .ZIP Library**
   - Select downloaded ZIP files

### Library Includes

```cpp
#include "ZMPT101B.h"
#include "ACS712.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
```

## Circuit Diagram

```
AC Live ──┬─── ZMPT101B Input ─── ESP32 Pin 34
          │
          └─── ACS712 Input ────── ACS712 Output ─── Load
          
AC Neutral ─── ZMPT101B Input ─── Load

HI-Link SMPS:
AC Live/Neutral ─── Input
5V/GND ─── ESP32 & Sensors Power

I2C OLED:
SDA ─── ESP32 Pin 21
SCL ─── ESP32 Pin 22
```

## Code Explanation

### Key Functions

- **`setup()`**: Initializes sensors, display, and calibration
- **`loop()`**: Main execution loop for data acquisition and display
- **`displayVoltCurrent()`**: Shows voltage and current readings
- **`displayInstPower()`**: Shows instantaneous power consumption
- **`displayEnergy()`**: Shows cumulative energy consumption
- **`displayUnits()`**: Shows energy units consumed
- **`CalibCurrent()`**: Calibrates current sensor zero point
- **`CalibVoltage()`**: Calibrates voltage sensor zero point

### Display Screens

The device cycles through 4 different screens:
1. **Voltage & Current** (V and A)
2. **Instantaneous Power** (W or kW)
3. **Energy Consumption** (Wh, kWh, etc.)
4. **Units Consumed** (Based on energy consumption)

## Assembly Instructions

1. **3D Print** the enclosure using provided STL files
2. **Solder** all connections according to the circuit diagram
3. **Test** the circuit on breadboard before final assembly
4. **Use heat shrink** and insulation tape for safety
5. **Fit components** into the 3D printed casing
6. **Secure** all connections and close the enclosure

## Calibration Process

### Initial Calibration Required

Before first use, calibrate both sensors:

1. **Uncomment calibration functions** in setup():
   ```cpp
   //CalibCurrent();
   //CalibVoltage();
   ```

2. **Upload code** with one calibration function active at a time

3. **Ensure no voltage/current** is present during calibration

4. **Note the zero point** values displayed

5. **Update zero points** in the code:
   ```cpp
   voltageSensor.setZeroPoint(2621);  // Update this value
   currentSensor.setZeroPoint(2943);  // Update this value
   ```

6. **Comment out** calibration functions and upload final code

## Usage

1. **Connect** the device between wall socket and appliance
2. **Power on** - the device will start automatically
3. **View readings** on the OLED display
4. **Screens change** automatically every 5 seconds
5. **Monitor** real-time energy consumption

### Reading Interpretation

- **Voltage**: AC voltage in Volts (V)
- **Current**: AC current in Amperes (A)  
- **Power**: Instantaneous power in Watts (W) or Kilowatts (kW)
- **Energy**: Cumulative energy in Wh, kWh, etc.
- **Units**: Energy consumption units for billing

## Troubleshooting

### Common Issues

1. **Display not working**: Check I2C connections and address (0x3C)
2. **Incorrect readings**: Perform sensor calibration
3. **No power**: Verify HI-Link SMPS connections
4. **Sensor noise**: Check grounding and shielding

### Threshold Values

The code includes threshold values to filter noise:
- **Voltage threshold**: 55V (below this, voltage = 0)
- **Current threshold**: 0.15A (below this, current = 0)

These can be adjusted based on your specific requirements.

## Safety Considerations

⚠️ **Warning**: This project involves mains AC voltage (220V). Take proper precautions:

- Use proper insulation and enclosure
- Test thoroughly before use
- Ensure proper grounding
- Use appropriate fuses and protection
- Follow local electrical codes

## Contributing

Feel free to contribute to this project by:
- Reporting bugs
- Suggesting improvements
- Adding new features
- Improving documentation

## License

This project is open-source and available under the MIT License.

---

**Project Source**: [CircuitDigest - DIY Real-Time Energy Monitoring Device](https://circuitdigest.com/microcontroller-projects/diy-real-time-energy-monitoring-device-using-esp32)

**Disclaimer**: This project is for educational purposes. Use at your own risk and ensure compliance with local electrical regulations.
