# Lab 7

## Overview

This project uses the Arduino Uno's onboard ADC to measure DC voltage
and display it on a 16×2 I2C LCD. Two probe wires connect to A0 and GND.
The Serial Monitor is not used.

## Components

- Arduino Uno
- 16×2 LCD with I2C interface
- Three equal-value resistors
- Breadboard and jumper wires
- USB cable

## Wiring

| Component | Arduino Connection |
|---|---|
| Positive probe | A0 |
| Negative probe | GND |
| LCD VCC | 5V |
| LCD GND | GND |
| LCD SDA | A4 |
| LCD SCL | A5 |

The LCD address is `0x27`. The Arduino is powered through USB.

### Case 1

Connect two equal resistors in series:

`GND → R1 → A0 measurement node → R2 → 5V`

### Case 2

Connect three equal resistors in series:

`GND → R1 → A0 measurement node → R2 → R3 → 5V`

The blue wire connects to A0. In both cases, A0 measures the voltage
across R1 relative to GND.

## Arduino Code

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int voltageV = A0;

void setup() {
  pinMode(voltageV, INPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int VoltageMsmt = analogRead(voltageV);
  float Vcalc = (5.0 / 1023) * VoltageMsmt;

  lcd.setCursor(0, 0);
  lcd.print("BATT ");
  lcd.print(Vcalc);
  lcd.print(" V");

  delay(500);
}
```

## How It Works

The Arduino Uno has a 10-bit analog-to-digital converter (ADC).
The `analogRead()` function converts the input voltage into a number
from 0 to 1023.

Assuming a 5.0 V reference, the voltage is calculated as:

`Voltage = ADC reading × 5.0 / 1023`

The LCD displays the voltage with two decimal places and updates
approximately every 500 ms.

## Communication Protocol

The Arduino communicates with the LCD using I2C:

- SDA carries data.
- SCL provides the clock signal.

I2C reduces wiring by requiring only two signal wires, plus power
and ground.

The `Wire` library provides I2C communication, while
`LiquidCrystal_I2C` controls the LCD.


## Test Results

With a 5 V supply and equal resistors:

| Test | Expected Voltage Across R1 | LCD Reading |
|---|---:|---:|
| Case 1: two resistors | 5 / 2 = 2.50 V | 2.50 V |
| Case 2: three resistors | 5 / 3 ≈ 1.67 V | 1.67 V |

The displayed readings match the expected values at the displayed
precision.

## Setup and Operation

1. Build the circuit according to the wiring instructions.
2. Install the `LiquidCrystal_I2C` library in the Arduino IDE.
   The `Wire` library is included with Arduino Uno support.
3. Connect the Arduino to the computer using USB.
4. Select the Arduino Uno and the correct port.
5. Upload the sketch.
6. Read the voltage on the LCD.
7. Disconnect power before changing the resistor configuration.
