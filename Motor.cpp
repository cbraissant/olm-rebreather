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

void Motor::setOutput(int index) {
    digitalWrite(pin1, bitRead(lookup[index], 0));
    digitalWrite(pin2, bitRead(lookup[index], 1));
    digitalWrite(pin3, bitRead(lookup[index], 2));
    digitalWrite(pin4, bitRead(lookup[index], 3));
}

void Motor::rotate(bool direction) {
    current_millis = millis();
    if (current_millis - previous_millis >= delay_btw_move) {
        previous_millis = current_millis;

        // the lookup_index is the index to loop through the lookup_table
        // to turn clockwise, the value of the index must decrease
        // and turn anticlockwise, it must increase
        if (direction == CLOCKWISE) {
            lookup_index = lookup_index + 1;
        } else if (direction == ANTICLOCKWISE) {
            lookup_index = lookup_index - 1;
        }
        // it's value should be 0 <= i <= 7
        // using a modulo 8 is the best way to loop through the index
        lookup_index = lookup_index % 8;

        setOutput(lookup_index);
    }
}

void Motor::clockwise() {
    rotate(CLOCKWISE);
}

void Motor::anticlockwise() {
    rotate(ANTICLOCKWISE);
}