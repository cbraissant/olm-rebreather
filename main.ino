#include <Adafruit_ADS1X15.h>  // Analog to digital converter
#include <Adafruit_GFX.h>      // Graphics core library
#include <Adafruit_SSD1306.h>  // Monochrome OLED
#include <SPI.h>               // Serial Peripheral Interface communication
#include <Wire.h>              // Communication with I2C

#include "Led.h"          // Led outputs
#include "Motor.h"        // Vellemann motor
#include "Sensor.h"       // Oxygen sensor
#include "TimedAction.h"  // Trigger function on set interval

/************************************************
Adafruit SSD1306
1.3" 128x64 OLED Display
Communication: SPI(default) ou I2C
************************************************/
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13

#define TEXT_SIZE 0

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/************************************************
Vellemann VMA401 Driver
28BYJ-48 Stepper motor
Steps / revolution: 64
Step angle: 360 / 64 = 5.625ª
Frequency = 100Hz = 100pps
100pps * 60s = 6000ppm
6000 / 64 = 93.75 rpm 
************************************************/

//declare variables for the motor pins
#define MOTOR_PIN_1 7  // Blue          - 28BYJ48 pin 1
#define MOTOR_PIN_2 6  // Green / Pink  - 28BYJ48 pin 2
#define MOTOR_PIN_3 5  // Yellow        - 28BYJ48 pin 3
#define MOTOR_PIN_4 4  // Orange        - 28BYJ48 pin 4

#define STEPS_PER_REV 512
#define MOTOR_PPS 100

Motor motor1(MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4);

int counter = 0;

/************************************************
Adafruit ADS1115
16-Bit ADC - 4 Channel with Programmable Gain Amplifier
Communication: I2C
The gain of the ADC can only be adjusted for the card
and not for each channel
************************************************/
#define ADC_MULTIPLIER 16
#define ADC_RESOLUTION 0.0078125
#define CELL_1_CHANNEL 0
#define CELL_2_CHANNEL 1
#define CELL_3_CHANNEL 2
#define CELL_4_CHANNEL 3

Adafruit_ADS1115 ads1115;

Sensor sensor_a(ads1115, CELL_1_CHANNEL, ADC_RESOLUTION);
Sensor sensor_b(ads1115, CELL_2_CHANNEL, ADC_RESOLUTION);
Sensor sensor_c(ads1115, CELL_3_CHANNEL, ADC_RESOLUTION);
Sensor sensor_d(ads1115, CELL_4_CHANNEL, ADC_RESOLUTION);

/************************************************
LED modules
************************************************/
#define LED_0_PIN 0  // red
#define LED_1_PIN 1  // green
#define LED_2_PIN 2  // white

Led led_red(LED_0_PIN);
Led led_green(LED_1_PIN);
Led led_white(LED_2_PIN);

/************************************************
Timed Actions
************************************************/
void updateDisplay();
TimedAction TimedDisplay(1000, updateDisplay);

void updateSerial();
TimedAction TimedSerial(1000, updateSerial);

/************************************************
SETUP
************************************************/
void setup() {
    /*
     * initialise serial communication at 9600 bits per second
     * With serial port initialised, I/O "RX<-0" and "TX->1"
     * are reserved for serial communications
     */
    Serial.begin(9600);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;  // Don't proceed, loop forever
    }

    // set the basic text size and color for the OLED display
    display.setTextColor(WHITE, BLACK);

    // the library initialise the buffer of the screen with the adafruit logo
    // therefore a cleardisplay() is necessary
    display.clearDisplay();  // clear the screen
    display.display();       // update the screen

    // splah screen
    display.setCursor(36, 5);
    display.setTextSize(3);
    display.print(F("OLM"));
    display.setCursor(4, 35);
    display.setTextSize(2);
    display.print(F("REBREATHER"));
    display.setCursor(24, 55);
    display.setTextSize(1);
    display.print(F("- Swiss Made -"));
    display.display();
    delay(1000);
    display.clearDisplay();
    display.setTextSize(1);
    display.display();
    pinMode(0, OUTPUT);

    // initialize the ADS1115
    ads1115.begin();
    ads1115.setGain(GAIN_ONE);
    Serial.println(ads1115.getGain());
}

/************************************************
MAIN LOOP
************************************************/
void loop() {
    // if calibration need to been done
    //      blink leds
    //      alert message oled
    // else
    //      read setpoint
    //      read O2
    //      if O2 > setpoint        ⚠︎ hysteresis to avoid jerky movements
    //          close valve
    //      else
    //          open valve
    //      update led
    //      update OLED
    //
    motor1.clockwise();

    led_white.blink(1000);

    TimedSerial.check();
    TimedDisplay.check();
}

/************************************************
OLED HELPER FUNCTIONS
************************************************/
void clearLine(int line) {
    int startLine = line * 8;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            display.drawPixel(x, y, BLACK);
        }
    }
}

void updateSerial() {
    Serial.print("Sensor.cpp: ");
    Serial.print(sensor_a.read_value());
    Serial.println();
}

void updateDisplay() {
    display.setCursor(0, 0);
    display.print("Cell a: ");
    display.println(sensor_a.read_value());

    display.print("Cell b: ");
    display.println(sensor_b.read_value());

    display.print("Cell c: ");
    display.println(sensor_c.read_value());
    display.println(" ");

    display.print("Time: ");
    display.println(millis());
    display.display();
}