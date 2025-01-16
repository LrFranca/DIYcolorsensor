#include <DIYcolorsensor.h>

ColorSensor sensor(6, 7, 8, A0);
void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor.getColor();
  sensor.printValues();
}
