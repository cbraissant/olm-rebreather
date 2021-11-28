#include "MovingAverage.h"

MovingAverage::MovingAverage(int max_length) {
    readings = new int[max_length];
    reset();
}

void MovingAverage::writeValue(int new_value) {
    // update the array of values and its index
    readings[index_next] = new_value;
    index_next = ++index_next % max_length;

    if (length++ < max_length) {
        // update the sum
        sum = sum + new_value;
    } else {
        // if the array is full remove the oldest value
        sum = sum - readings[index_next] + new_value;
    }
}

float MovingAverage::readAverage() {
    return sum / length;
}

void MovingAverage::reset() {
    index_next = 0;
    length = 0;
    sum = 0;
}