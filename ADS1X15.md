# Arduino Code
The Adafruit_ADS1X15 library supports both single-ended and differential readings as well as comparator operations on both the ADS1015 and ADS1115 breakout boards.  The library uses the wiring library for I2C communication, so wiring.h must be included.

## Construction and Initialization:

`Adafruit_ADS1015();`
Construct an instance of an ADS1015

`Adafruit_ADS1115();`
Construct an instance of an ADS1115

`begin();`
Initialize the ADC for operation using the default address and I2C bus.

`begin(0x49);`
Initialize the ADC for operation using specified address of 0x49.

 
### Example:

The following examples assume an ADS1015 and use a 3 mV/bit scaling factor. For the higher-resolution ADS1115, the scaling factor would be 188uV/bit.

```cpp
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1015 ads1015;  	// Construct an ads1015 
Adafruit_ADS1115 ads1115;	// Construct an ads1115 

void setup(void)
{
  ads1015.begin();  // Initialize ads1015 at the default address 0x48
  ads1115.begin(0x49);  // Initialize ads1115 at address 0x49
}
```


## Single Ended Conversion:

`uint16_t readADC_SingleEnded(uint8_t channel);`
Perform a single-ended analog to digital conversion on the specified channel.

### Example:
```cpp
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1015 ads1015;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV)");
  ads1015.begin();
}

void loop(void)
{
  int16_t adc0, adc1, adc2, adc3;

  adc0 = ads1015.readADC_SingleEnded(0);
  adc1 = ads1015.readADC_SingleEnded(1);
  adc2 = ads1015.readADC_SingleEnded(2);
  adc3 = ads1015.readADC_SingleEnded(3);
  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("AIN2: "); Serial.println(adc2);
  Serial.print("AIN3: "); Serial.println(adc3);
  Serial.println(" ");
  
  delay(1000);
}
```


## Differential Conversion:
`int16_t readADC_Differential_0_1(void);`
Perform a differential analog to digital conversion on the voltage between channels 0 and 1.

`int16_t readADC_Differential_2_3(void);` 
Perform a differential analog to digital conversion on the voltage between channels 2 and 3.

### Example:
```cpp
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1015 ads1015;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV)");
  ads1015.begin();
}

void loop(void)
{
  int16_t results;

  results = ads1015.readADC_Differential_0_1();
  Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.print(results * 3); Serial.println("mV)");

  delay(1000);
}
```


### Comparator Operation:
Comparator mode allows you to compare an input voltage with a threshold level and generate an alert signal (on the ALRT pin) if the threshold is exceeded.  This pin can be polled with a digital input pin, or it can be configured to generate an interrupt.

`void startComparator_SingleEnded(uint8_t channel, int16_t threshold);`
Set the threshold and channel for comparator operation.

`int16_t getLastConversionResults();`
Get the last conversion result and clear the comparator.

### Example:
```cpp
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1015 ads1015;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Single-ended readings from AIN0 with >3.0V comparator");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV)");
  Serial.println("Comparator Threshold: 1000 (3.000V)");
  ads1015.begin();
  
  // Setup 3V comparator on channel 0
  ads1015.startComparator_SingleEnded(0, 1000);
}

void loop(void)
{
  int16_t adc0;

  // Comparator will only de-assert after a read
  adc0 = ads1015.getLastConversionResults();
  Serial.print("AIN0: "); Serial.println(adc0);
  
  delay(100);
}
```


## Adjusting Gain
To boost small signals, the gain can be adjusted on the ADS1x15 chips in the following steps:
- GAIN_TWOTHIRDS (for an input range of +/- 6.144V)
- GAIN_ONE (for an input range of +/-4.096V)
- GAIN_TWO (for an input range of +/-2.048V)
- GAIN_FOUR (for an input range of +/-1.024V)
- GAIN_EIGHT (for an input range of +/-0.512V)
- GAIN_SIXTEEN (for an input range of +/-0.256V)

`adsGain_t getGain(void)`
Reads the current gain value (default = 2/3x)

`void setGain(adsGain_t gain)`
Sets the gain for the ADS1x15

```cpp
ads1015.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV (default)
ads1015.setGain(GAIN_ONE);     // 1x gain   +/- 4.096V  1 bit = 2mV
ads1015.setGain(GAIN_TWO);     // 2x gain   +/- 2.048V  1 bit = 1mV
ads1015.setGain(GAIN_FOUR);    // 4x gain   +/- 1.024V  1 bit = 0.5mV
ads1015.setGain(GAIN_EIGHT);   // 8x gain   +/- 0.512V  1 bit = 0.25mV
ads1015.setGain(GAIN_SIXTEEN); // 16x gain  +/- 0.256V  1 bit = 0.125mV
```

### Example
If we had an analog sensor with an output voltage ~1V (a TMP36, for example), we could set the gain on the ADC to GAIN_FOUR, which would give us a +/-1.024V range. This would push the 1V input signal over the entire 12-bit or 16-bit range of the ADC, compared to the very limited range 1V would cover without adjusting the gain settings

```cpp
// Set the gain to 4x, for an input range of +/- 1.024V
// 1-bit = 0.5V on the ADS1015 with this gain setting
ads1015.setGain(GAIN_FOUR);
```