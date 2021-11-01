#ifndef Sensor_h
#define Sensor_h

#include <Adafruit_ADS1X15.h>
#include <Arduino.h>
#include <RunningAverage.h>

class Sensor {
   private:
    int adc_multiplier;
    int adc_channel;
    int calibration_FO2;
    int sensor_gain;
    float sensor_mv_per_bit;
    bool sensor_is_calibrated;
    RunningAverage sensor_ra;
    Adafruit_ADS1115 ads1115;

   public:
    Sensor(int adc_channel, int adc_multiplier);
    void adjust_gain();
    void init();

    // calibrate the sensor and set the sensor gain
    void calibrate(int calibration_FO2);

    // returns the different values of the sensor
    int16_t get_adc_value();
    float get_mV();
    float get_PO2();
};

#endif