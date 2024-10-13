
# Pollution Detection System

This Arduino-based project detects environmental pollution by measuring **CO2 levels** and **noise levels** using an **MQ135 gas sensor** and a sound sensor. The results are displayed on a **16x2 I2C LCD**, and alerts are triggered when pollution thresholds are exceeded.

## Features
- **CO2 Detection**: The MQ135 sensor detects air pollution in the form of CO2 levels.
- **Noise Detection**: An analog sound sensor measures noise pollution.
- **Real-time Display**: Data is shown on a 16x2 LiquidCrystal I2C display.
- **Alert System**: If CO2 levels exceed 1000 ppm or noise levels exceed 200 dB, the system flashes warning messages.

## Components
- **Arduino** (any compatible board)
- **MQ135 Gas Sensor**
- **Analog Sound Sensor**
- **16x2 LiquidCrystal I2C Display**
- **Jumper wires and Breadboard**

## Circuit Diagram
![Circuit Diagram](https://github.com/WhyRed-V/Air-Pollution-and-Sound-Detector/blob/main/arduinoDesg_page-0001.jpg)

### Connections:
1. **MQ135 Sensor**:
   - VCC → 5V
   - GND → GND
   - Analog output → A2

2. **Analog Sound Sensor**:
   - VCC → 5V
   - GND → GND
   - Analog output → A0

3. **LCD (I2C)**:
   - SDA → A4
   - SCL → A5
   - VCC → 5V
   - GND → GND

## Code Overview
### Libraries Used:
- `LiquidCrystal_I2C.h`: For controlling the I2C LCD.
- `MQ135.h`: For handling the MQ135 gas sensor.

### Main Functionality:
- **Sensor Calibration**: The MQ135 sensor is calibrated during setup with a warm-up time.
- **Data Averaging**: Multiple sensor readings are averaged to ensure more accurate measurements.
- **Pollution Alerts**: If CO2 or noise levels exceed the threshold, a warning message flashes on the LCD.

### Thresholds:
- CO2 Pollution: **1000 ppm**
- Noise Pollution: **200 dB**

## Setup Instructions
1. Connect all components as per the circuit diagram.
2. Upload the provided code to your Arduino board.
3. Open the serial monitor at 9600 baud rate to observe sensor calibration and live data.

## License
This project is licensed under the MIT License.
