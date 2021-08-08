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

   public:
    Led(byte pin);
    void init();
    void on();
    void off();
    void shift();
    bool getState();
};

// header guards
#endif