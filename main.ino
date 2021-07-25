#include <Adafruit_GFX.h>      // Graphics core library
#include <Adafruit_SSD1306.h>  // Monochrome OLED
#include <SPI.h>               // Serial Peripheral Interface communication

#include "Led.h"  // Led outputs

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
Declaration for LED modules
**************************************************************************/
#define LED_1_PIN 7
#define LED_2_PIN 6
#define LED_3_PIN 5

Led led1(LED_1_PIN);
Led led2(LED_2_PIN);
Led led3(LED_3_PIN);

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
    display.setTextSize(TEXT_SIZE);
    display.setTextColor(WHITE, BLACK);

    // the library initialise the buffer of the screen with the adafruit logo
    // therefore a cleardisplay() is necessary
    display.clearDisplay();  // clear the screen
    display.display();       // update the screen

    // welcome message
    display.setCursor(0, 0);
    display.println("Olm Rebreater");
    display.println("Swiss Made");
    display.display();
    display.clearDisplay();
}

/**************************************************************************
MAIN LOOP
**************************************************************************/
void loop() {
    led1.shift();
    delay(200);
    led2.shift();
    delay(200);
    led3.shift();
    delay(200);
}
