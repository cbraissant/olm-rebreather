#include <Adafruit_ADS1X15.h>  // Analog to digital converter
#include <Adafruit_GFX.h>      // Graphics core library
#include <Adafruit_SSD1306.h>  // Monochrome OLED
#include <SPI.h>               // Serial Peripheral Interface communication
#include <Wire.h>              // Communication with I2C

#include "Led.h"     // Led outputs
#include "Motor.h"   // Vellemann motor
#include "Sensor.h"  // Oxygen sensor

/**************************************************************************
Adafruit SSD1306
1.3" 128x64 OLED Display
Communication: SPI(default) ou I2C
**************************************************************************/
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

/**************************************************************************
Vellemann VMA401 Driver
28BYJ-48 Stepper motor
Steps / revolution: 64
Step angle: 360 / 64 = 5.625ª
Frequency = 100Hz = 100pps
100pps * 60s = 6000ppm
6000 / 64 = 93.75 rpm 
**************************************************************************/

//declare variables for the motor pins
#define MOTOR_PIN_1 7  // Blue   - 28BYJ48 pin 1
#define MOTOR_PIN_2 6  // Pink   - 28BYJ48 pin 2
#define MOTOR_PIN_3 5  // Yellow - 28BYJ48 pin 3
#define MOTOR_PIN_4 4  // Orange - 28BYJ48 pin 4 \
                       // Red    - 28BYJ48 pin 5 (VCC)
#define STEPS_PER_REV 512
#define MOTOR_PPS 100

Motor motor1(MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4);

int counter = 0;

/**************************************************************************
Adafruit ADS1115
16-Bit ADC - 4 Channel with Programmable Gain Amplifier
Communication: I2C
**************************************************************************/
#define SENSOR_1_ADC_CHANEL 0
#define SENSOR_1_ADC_CHANEL 1
#define SENSOR_1_ADC_CHANEL 2
#define ADC_MULTIPLIER 16

Sensor sensor1(SENSOR_1_ADC_CHANEL, ADC_MULTIPLIER);
Sensor sensor2(SENSOR_1_ADC_CHANEL, ADC_MULTIPLIER);
Sensor sensor3(SENSOR_1_ADC_CHANEL, ADC_MULTIPLIER);

/**************************************************************************
LED modules
**************************************************************************/
#define LED_1_PIN 0
#define LED_2_PIN 1
#define LED_3_PIN 2

Led led1(LED_1_PIN);
Led led2(LED_2_PIN);
Led led3(LED_3_PIN);

/**************************************************************************
miscellaneous
**************************************************************************/

/**************************************************************************
SETUP
**************************************************************************/
void setup() {
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
    // delay(2000);
    display.clearDisplay();
    display.setTextSize(1);
    display.display();
}

/**************************************************************************
MAIN LOOP
**************************************************************************/
void loop() {
    if (counter == 0) {
        for (int i = 0; i < 512; i++) {
            motor1.clockwise();
        }
    }
    counter = 1;
    delay(1000);

    led1.shift();
    delay(200);
    led2.shift();
    delay(200);
    led3.shift();
    delay(200);

    int16_t adc0, adc1, adc2, adc3;

    adc0 = sensor1.get_mV();
    adc1 = sensor2.get_mV();
    adc2 = sensor3.get_mV();
    display.setCursor(0, 0);
    display.print("Cell     0: ");
    display.print(adc0);
    display.println(" ");
    display.print("Cell 1: ");
    display.println(adc1);
    display.print("Cell 2: ");
    display.println(adc2);
    display.println(" ");
    display.display();

    delay(200);
}

/**************************************************************************
OLED HELPER FUNCTIONS
**************************************************************************/
void clearLine(int line) {
    int startLine = line * 8;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            display.drawPixel(x, y, BLACK);
        }
    }
}