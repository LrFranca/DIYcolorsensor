#include <DIYcolorsensor.h>

const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

ColorSensor sensor(6, 7, 8, A0);

void setup() {
  Serial.begin(9600);
}
void loop() {
  sensor.getColor();
  sensor.printValues();
}
