# Olm Rebreater

## About
Olm Rebreather is the new prototype of diving rebreather made by Swiss Diving Manufacturer

## Introduction
Electrical prototype of the oxygen delivery system in a diving rebreather.
The system consists of an oxygen sensor analysing the breathing air in real time and a variable flow valve adjusting the mixture.
An arduino handles the logic. LEDs and OLED screen provide feedback to the user.

## Components
| Component        | Brand / Model                |
| ---------------- | ---------------------------- |
| Main card        | Arduino Uno                  |
| Oxygen sensor    | To Be Determined             |
| Analog converter | Adafruit ADS1115 16Bit I2C   |
| Stepper motor    | 22BYJ-48                     |
| Stepper driver   | Velleman VMA401              |
| OLED display     | Adafruit SSD1306 1.3" 128x64 |
| LED              | Grove LED socket kit         |


## Oxygen Sensor calibration
Oxygen sensors are believed to be linear, and without offset, below a PPO2 of 1.5 Bar.
The calibration process is as simple as finding the multiplication factor of the voltage.
That calibration can be done at any FO2, however, the higher the FO2 the more acurate the voltage.

The calibration process assume a homogeneous gas mixture in the loop.
Therefore, it should not be done if the voltage of the cells is not stable.

Calibration:
1.  Oxygen percentage of the calibration gaz ("Pure" Oxygen):
    FO2_cal = 98%  
2.  Voltage measured from the sensor:
    V_cal = 48 mV
3.  Calibration factor:
    C = V_Cal / FO2_cal = 48 / 0.98 = 50 [bar / mV]

Reading of the actual PPO2 during a dive:
4.  Voltage measured during the dive:
    V_mes = 65 mV
5.  Partial pressure calculation:
    PPO2 = V_mes / C = 65 / 50 = 1.3 bar

An oxygen sensor produce a voltage of 30mV to 70mV at 1013mbar and 98% O2 

**TODO:** adjust the calibration to the atmospheric pressure  

To simulate and oxygen cell, a voltage source of 0 - 200mV can be used.
This can be done with a simple electrical divider.
Current on the potentiometer: 200mV / 10k?? = 20??A
Resistor for the bridge: 5V / 20??A = 250k??


## ADS1115
Assuming an oxygen sensor producing 70mV during calibration, and a linear phase up to 2Bar.
The maximum voltage delivered by the sensor would be 2*70 = 140mV.

The set gain of the ADS1115 can be adjusted to 16x for an input range of +/-0.256V.
Voltage range: +/-0.256V = 0.512V
The resolution of will then be: 0.512 / 2^16 = 0.000007812V = 7.8125??V






## Arduino special

### serial.begin()
`serial.begin()` set the pins 0 (<-RX) et 1 (->TX). If those pins needs to be used, don't declare `serial.begin()` in the `void setup()`


### F() Macro
When an instruction like :
```cpp
Serial.print("Write something on  the Serial Monitor, by default stored in RAM");
```
is used, the string to be printed is normally saved in RAM. If your sketch prints a lot of stuff on the Serial Monitor, you can easily fill the RAM. If you have free FLASH memory space, you can easily indicate that the string must be saved in FLASH using the syntax:
```cpp
Serial.print(F("Write something on the Serial Monitor, that is stored in FLASH"));
```