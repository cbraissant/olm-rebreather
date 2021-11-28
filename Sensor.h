#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_ADS1X15.h>
#include <Arduino.h>

#include "MovingAverage.h"

class Sensor {
   public:
    Sensor(Adafruit_ADS1115 &ads1115, int adc_channel, float adc_resolution);
    int16_t readValue();
    float readAverage();
    float readVoltage();
    float readPressure();
    void calibrate(float calibration_fO2);
    bool readCalibration();
    void updateAverage();
    int16_t calibration_value;

   private:
    Adafruit_ADS1115 *ads1115;
    MovingAverage *moving_average;
    int adc_channel;
    float adc_resolution;
    int is_calibrated;
    float calibrated_gain;
};

#endif
