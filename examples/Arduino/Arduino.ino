// Include the DIY Color Sensor library
#include <DIYcolorsensor.h>

// Define ADC (Analog-to-Digital Converter) prescaler settings for adjusting analog read speed
const unsigned char PS_16 = (1 << ADPS2);             // Prescaler = 16 (faster ADC conversion)
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Default prescaler = 128 (slower but more stable)

// Initialize the color sensor with the following pin configuration:
// - Pin 6: Red LED control
// - Pin 7: Green LED control
// - Pin 8: Blue LED control
// - A0: Analog input pin for reading reflected light
ColorSensor sensor(6, 7, 8, A0);

void setup() {
  // Initialize serial communication at 9600 baud for debugging
  Serial.begin(9600);

  // Configure ADC for faster readings (helps with quick color detection)
  ADCSRA &= ~PS_128;  // Clear the default prescaler (128)
  ADCSRA |= PS_16;    // Set a faster prescaler (16)

  /* Optional: Manual calibration for black level detection
     Uncomment and adjust these if you need to calibrate:
  sensor.setBlackMin(0, 0, 0);  // Set minimum RGB values for black
  sensor.setBlackMax(0, 0, 0);  // Set maximum RGB values for black
  */
}

void loop() {
  // Read raw RGB values from the sensor
  sensor.getColor();

  // Print the detected RGB values to the Serial Monitor
  sensor.printValues();
}
