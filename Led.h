/*
    This library handle the LEDs connected to the Arduino Board
*/

// header guards
#ifndef Led_h
#define Led_h

#include <Arduino.h>

class Led {
   private:
    byte pin;
    bool state = false;
    unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();

   public:
    Led(byte pin);
    void init();
    void on();
    void off();
    void shift();
    bool getState();
    void blink(int interval);
};

// header guards
#endif