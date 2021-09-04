// header guards
#ifndef Motor_h
#define Motor_h

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
    void rotateSteps(int steps);
    void clockwise();
    void anticlockwise();
    void loop();

   private:
    // pin numbers
    byte pin1;
    byte pin2;
    byte pin3;
    byte pin4;

    // initiallise the motor
    void init();

    // motor specific variables
    int number_of_steps = 512;        // number of steps per revolution
    int max_steps_per_seconds = 100;  // maximum frequency of the motor
    int min_delay_btw_steps = 1250;   // minimum deley between steps, in µs
    int step_counter = 0;             // counter of steps made

    int motorSpeed = 1000;   //variable to set stepper speed
    int count = 0;           // count of steps made
    int countsperrev = 512;  // number of steps per full revolution

    // stepper lookup table (going through the table create a single step)
    int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
    void setOutput(int out);
};

#endif