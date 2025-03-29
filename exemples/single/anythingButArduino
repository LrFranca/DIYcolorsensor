// Include the DIY Color Sensor library
#include <DIYcolorsensor.h>

// Initialize the color sensor with the following pin configuration:
// - Pin 6: Red LED control
// - Pin 7: Green LED control
// - Pin 8: Blue LED control
// - A0: Analog input pin for reading reflected light
ColorSensor sensor(6, 7, 8, A0);

void setup() {
  // Initialize serial communication at 9600 baud for debugging
  Serial.begin(9600);

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
