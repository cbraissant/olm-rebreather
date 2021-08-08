#include "Led.h"

Led::Led(byte pin) {
    this->pin = pin;
    init();
}

void Led::init() {
    pinMode(pin, OUTPUT);
    off();
}

void Led::off() {
    state = false;
    digitalWrite(pin, LOW);
}

void Led::on() {
    state = true;
    digitalWrite(pin, HIGH);
}

bool Led::getState() {
    return state;
}

void Led::shift() {
    if (digitalRead(pin) == LOW) {
        on();
    } else {
        off();
    }
}