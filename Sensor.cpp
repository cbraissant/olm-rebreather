#include "Sensor.h"

#include <Adafruit_ADS1X15.h>

#include "MovingAverage.h"

Sensor::Sensor(Adafruit_ADS1115 &ads1115, int adc_channel, float adc_resolution) {
    this->ads1115 = &ads1115;
    this->adc_channel = adc_channel;
    this->adc_resolution = adc_resolution;
    this->is_calibrated = false;
    this->moving_average = new MovingAverage(20);
}

bool Sensor::readCalibration() {
    return is_calibrated;
}

int16_t Sensor::readValue() {
    return ads1115->readADC_SingleEnded(adc_channel);
}

float Sensor::readVoltage() {
    return readAverage() * adc_resolution;
}

float Sensor::readAverage() {
    return moving_average->readAverage();
}

void Sensor::updateAverage() {
    moving_average->writeValue(readValue());
}

void Sensor::calibrate(float calibration_fO2) {
    this->calibration_value = readAverage();
    this->calibrated_gain = calibration_fO2 / calibration_value;
    this->is_calibrated = true;
}

float Sensor::readPressure() {
    if (this->is_calibrated) {
        return readAverage() * calibrated_gain;
    } else {
        return 0.0;
    }
}