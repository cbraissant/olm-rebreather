#include "Sensor.h"

#include <Adafruit_ADS1X15.h>

Sensor::Sensor(Adafruit_ADS1115 &ads1115, int adc_channel, int adc_resolution) {
    this->ads1115 = &ads1115;
    this->adc_channel = adc_channel;
    this->adc_resolution = adc_resolution;
    this->is_calibrated = false;
}

bool Sensor::isCalibrated() {
    return is_calibrated;
}

int16_t Sensor::read_value() {
    return ads1115->readADC_SingleEnded(adc_channel);
}

float Sensor::read_mV() {
    return this->read_value() * this->adc_resolution;
}


// float Sensor::get_PO2() {
//     if (this->is_calibrated) {
//         return this->read_mV() / this->sensor_gain;
//     } else {
//         return 0.0;
//     }
// }

// void Sensor::calibrate(int calibration_FO2) {
//     this->is_calibrated = true;
// }