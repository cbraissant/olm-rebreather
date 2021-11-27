#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_ADS1X15.h>
#include <Arduino.h>

class Sensor {
   public:
    Sensor(Adafruit_ADS1115 &ads1115, int adc_channel, int adc_resolution);
    int16_t read_value();
    float read_mV();
    float read_pO2();
    bool isCalibrated();

   private:
    Adafruit_ADS1115 *ads1115;
    int adc_channel;
    int adc_resolution;
    int is_calibrated;
};

#endif
