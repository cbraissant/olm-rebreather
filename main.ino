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
LED modules
**************************************************************************/
#define LED_1_PIN 7
#define LED_2_PIN 6
#define LED_3_PIN 5

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
    delay(2000);
    display.clearDisplay();
    display.setTextSize(1);
    display.display();
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