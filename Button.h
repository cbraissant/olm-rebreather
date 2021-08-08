// header guards
#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button {
   private:
    byte pin;
    byte state;
    byte previousState;

    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;

   public:
    Button(byte pin);
    void init();
    void update();
    byte getState();
    bool isPressed();
};

#endif