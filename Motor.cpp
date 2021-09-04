#include "Motor.h"

Motor::Motor(byte pin1, byte pin2, byte pin3, byte pin4) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->pin3 = pin3;
    this->pin4 = pin4;
    init();
}

void Motor::init() {
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
}

void Motor::setOutput(int out) {
    digitalWrite(pin1, bitRead(lookup[out], 0));
    digitalWrite(pin2, bitRead(lookup[out], 1));
    digitalWrite(pin3, bitRead(lookup[out], 2));
    digitalWrite(pin4, bitRead(lookup[out], 3));
}

void Motor::rotateSteps(int steps) {
}

void Motor::clockwise() {
    for (int i = 7; i >= 0; i--) {
        setOutput(i);
        delayMicroseconds(motorSpeed);
    }
}

void Motor::anticlockwise() {
    for (int i = 0; i < 8; i++) {
        setOutput(i);
        delayMicroseconds(motorSpeed);
    }
}