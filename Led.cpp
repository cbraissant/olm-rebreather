#include "Led.h"

Led::Led(byte pin) {
    // Use 'this->' to make the difference between the
    // 'pin' attribute of the class and the
    // local variable 'pin' created from the parameter.
    this->pin = pin;
    init();
}

void Led::init() {
    pinMode(pin, OUTPUT);
    off();
}

void Led::off() {
    digitalWrite(pin, LOW);
}

void Led::on() {
    digitalWrite(pin, HIGH);
}

void Led::shift() {
    if (digitalRead(pin) == LOW) {
        on();
    } else {
        off();
    }
}