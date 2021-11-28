#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include <Arduino.h>

class MovingAverage {
   public:
    MovingAverage(int max_length);
    void writeValue(int new_value);
    float readAverage();
    void reset();

   private:
    int *readings;   // pointer to the array of values
    int index_next;  // index to the next value in the array
    int length;      // current length of the array
    int max_length;  // maximum length of the array
    int sum;         // sum of all the values in the array
};

#endif