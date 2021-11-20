#include "Led.h"

Led::Led(byte pin) {
    this->pin = pin;
    this->init();
}

void Led::init() {
    pinMode(pin, OUTPUT);
    this->off();
}

void Led::off() {
    this->state = false;
    digitalWrite(pin, LOW);
}

void Led::on() {
    this->state = true;
    digitalWrite(pin, HIGH);
}

bool Led::getState() {
    return this->state;
}

void Led::shift() {
    if (digitalRead(pin) == LOW) {
        this->on();
    } else {
        this->off();
    }
}

void Led::blink(int interval) {
    this->current_millis = millis();
    if (this->current_millis - this->previous_millis >= interval) {
        this->previous_millis = this->current_millis;
        this->shift();
    }
}
