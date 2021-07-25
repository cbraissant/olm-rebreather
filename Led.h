/*
    This library handle the LED connected to the Arduino Board
*/

// header guards
#ifndef Led_h
#define Led_h

#include <Arduino.h>

class Led {
   private:
    byte pin;
    byte state = LOW;

   public:
    Led(byte pin);
    void init();
    void on();
    void off();
    void shift();
    byte getState();
};

// header guards
#endif