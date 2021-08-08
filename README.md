# Olm Rebreater

## About
Olm Rebreather is a Swiss Made diving rebreather

## Components
Main card: **Arduino Uno**
OLED display: **Adafruit SSD1306 1.3" 128x64**
Stepper Motor: **22BYJ-48**
Stepper motor driver: **Velleman VMA401**
Analog converter: **Adafruit ADS1115 16Bit I2C**

## Arduino special

### F() Macro
When an instruction like :
```cpp
Serial.print("Write something on  the Serial Monitor, by default stored in RAM");
```
is used, the string to be printed is normally saved in RAM. If your sketch prints a lot of stuff on the Serial Monitor, you can easily fill the RAM. If you have free FLASH memory space, you can easily indicate that the string must be saved in FLASH using the syntax:
```cpp
Serial.print(F("Write something on the Serial Monitor, that is stored in FLASH"));
```