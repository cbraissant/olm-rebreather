#include "Sensor.h"

#include <Adafruit_ADS1X15.h>

Sensor::Sensor(int adc_channel, int adc_multiplier) {
    this->adc_multiplier = adc_multiplier;
    this->adc_channel = adc_channel;
    this->sensor_is_calibrated = false;
    init();
}

void Sensor::adjust_gain() {
    switch (this->adc_multiplier) {
        case (0):
            ads1115.setGain(GAIN_TWOTHIRDS);
            this->sensor_mv_per_bit = 0.1875;
            break;
        case (1):
            ads1115.setGain(GAIN_ONE);
            this->sensor_mv_per_bit = 0.125;
            break;
        case (2):
            ads1115.setGain(GAIN_TWO);
            this->sensor_mv_per_bit = 0.0625;
            break;
        case (4):
            ads1115.setGain(GAIN_FOUR);
            this->sensor_mv_per_bit = 0.03125;
            break;
        case (8):
            ads1115.setGain(GAIN_EIGHT);
            this->sensor_mv_per_bit = 0.015625;
            break;
        case (16):
            ads1115.setGain(GAIN_SIXTEEN);
            this->sensor_mv_per_bit = 0.0078125;
            break;
        default:
            ads1115.setGain(GAIN_TWO);
            this->sensor_mv_per_bit = 0.0625;
    }
}

void Sensor::init() {
    this->adjust_gain();
    ads1115.begin();
}

int16_t Sensor::get_adc_value() {
    return this->ads1115.readADC_SingleEnded(this->adc_channel);
}

float Sensor::get_mV() {
    return this->get_adc_value() * this->sensor_mv_per_bit;
}

float Sensor::get_PO2() {
    if (this->sensor_is_calibrated) {
        return this->get_mV() / this->sensor_gain;
    } else {
        return 0.0;
    }
}

void Sensor::calibrate(int calibration_FO2) {
    this->sensor_is_calibrated = true;
}
