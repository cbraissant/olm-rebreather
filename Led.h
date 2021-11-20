/*
    This library handle the LEDs connected to the Arduino Board
*/

// header guards
#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
   private:
    byte pin;
    bool state = false;
    unsigned long previous_millis = 0;
    unsigned long current_millis = 0;

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