// Include the DIY Color Sensor library
#include <DIYcolorsensor.h>

// Define ADC prescaler settings for faster analog readings
const unsigned char PS_16 = (1 << ADPS2);             // Prescaler = 16 (faster ADC)
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Default prescaler = 128 (slower but stable)

// Initialize the color sensor:
// - Pins 2, 3, 4 control RGB LEDs (for illumination)
// - A0 is the analog input for light detection
ColorSensor sensor(2, 3, 4, A0);

void setup() {
  // Start serial communication for debugging (9600 baud)
  Serial.begin(9600);

  // Adjust ADC prescaler for faster readings:
  ADCSRA &= ~PS_128;  // Clear the default prescaler (128)
  ADCSRA |= PS_16;    // Set a faster prescaler (16)

  /* Optional: Manually set black calibration values (min/max thresholds)
  sensor.setBlackMin(0, 0, 0);  // Minimum RGB for black
  sensor.setBlackMax(0, 0, 0);  // Maximum RGB for black
  */
}

void loop() {
  // Step 1: Read raw RGB values from the sensor
  sensor.getColor();

  // Step 2: Convert RGB to HSB (Hue, Saturation, Brightness)
  sensor.rgbToHSB(sensor.R_raw, sensor.G_raw, sensor.B_raw);

  // Step 3: Detect the color and print the result
  Serial.println(colorDetection(sensor.hue, sensor.saturation, sensor.brightness));
}

/**
 * Detects the color based on HSB values and raw RGB.
 * @param h Hue (0-360°)
 * @param s Saturation (0-1)
 * @param b Brightness (0-1)
 * @return byte - A number representing the detected color:
 *   0 = Black
 *   1 = Dark Gray
 *   2 = Blue
 *   3 = Green
 *   4 = Yellow
 *   5 = Red
 *   6 = White
 *   8 = Unknown
 */
byte colorDetection(float h, float s, float b) {
  byte color = 0; // Default: unknown/black

  // Check if all RGB values are very low → Black
  if (sensor.R_raw <= 15 && sensor.G_raw <= 15 && sensor.B_raw <= 15) {
    color = 0; // Black
  }
  // If saturation is low → Gray or White
  else if (s <= 0.6) {
    if (b <= 0.7) {
      color = 1; // Dark Gray
    } else {
      color = 6; // White
    }
  }
  // High saturation → Check hue for color
  else {
    if ((h >= 285 && h <= 360) || (h >= 0 && h <= 45)) {
      color = 5; // Red
    }
    else if (h >= 45 && h <= 105) {
      color = 4; // Yellow
    }
    else if (h >= 105 && h <= 165) {
      color = 3; // Green
    }
    else if (h >= 180 && h <= 285) {
      color = 2; // Blue
    }
    else {
      color = 8; // Unknown color
    }
  }
  return color;
}
