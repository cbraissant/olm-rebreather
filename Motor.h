// header guards
#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

// 28BYJ-48, using a VMA401 - ULN2003 interface board to drive the stepper.
// The 28BYJ-48 motor is a 4-phase, 8-beat motor
// One bipolar winding is on motor pins 1 & 3 and
// the other on motor pins 2 & 4.
// The step angle is 5.625ª and the
// operating Frequency is 100pps.

// The stepper has 8 beat per steps
// The operating frequency is 100pps
// Each step can be as fast as 1/100s or 10ms
// Each beat is 1/8th of the step, so 1/8*10 = 1.25ms or 1250ms
////////////////////////////////////////////////
class Motor {
   public:
    Motor(byte pin1, byte pin2, byte pin3, byte pin4);
    void rotate(bool direction);
    void clockwise();
    void anticlockwise();
    void loop();

   private:
    // pin numbers
    byte pin1;
    byte pin2;
    byte pin3;
    byte pin4;

    const bool CLOCKWISE = 0;
    const bool ANTICLOCKWISE = 1;

    int lookup_index = 0;

    // initiallise the motor
    void init();

    // time tracker
    unsigned long previous_millis = 0;
    unsigned long current_millis = 0;

    // motor specific variables
    int steps_per_rev = 512;          // number of steps per revolution
    int max_steps_per_seconds = 100;  // maximum frequency of the motor
    int min_delay_btw_steps = 1250;   // minimum deley between steps, in µs
    int step_counter = 0;             // counter of steps made

    int delay_btw_move = 2;  //variable to set stepper speed
    int count = 0;           // count of steps made

    // stepper lookup table (going through the table create a single step)
    int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
    void setOutput(int out);
};

#endif