// Based on http://www.arduino.cc/en/Tutorial/Debounce
// and https://roboticsbackend.com/arduino-object-oriented-programming-oop/
#include "Button.h"

Button::Button(byte pin) {
    this->pin = pin;
    previousState = LOW;
    init();
}

void Button::init() {
    pinMode(pin, INPUT);
}

void Button::update() {
    // You can handle the debounce of the button directly
    // in the class, so you don't have to think about it
    // elsewhere in your code
    byte newReading = digitalRead(pin);

    // 
    if (newReading != previousState) {
        lastDebounceTime = millis();
    }

    if (millis() - lastDebounceTime > debounceDelay) {
        state = newReading;
    }

    previousState = newReading;
}