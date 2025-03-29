
#include <DIYcolorsensor.h>
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

ColorSensor sensor(2, 3, 4, A0);

void setup() {
  Serial.begin(9600);
  ADCSRA &= ~PS_128;
  ADCSRA |= PS_16;
  
  /*
  In case you wanna set those values manually:
  sensor.setBlackMin(0, 0, 0); 
  sensor.setBlackMax(0, 0, 0);
  */
}
void loop() {
  sensor.getColor();
  sensor.rgbToHSB(sensor.R_raw, sensor.G_raw , sensor.B_raw);
  Serial.println(colorDetection(sensor.hue, sensor.saturation, sensor.brightness));
}

byte colorDetection(float h, float s, float b){
  byte color = 0;
  if(sensor.R_raw <= 15 && sensor.G_raw <= 15 && sensor.B_raw <= 15){
    color = 0;
  }
  else if(s <= 0.6){
    if(b <= 0.7){
      color = 1;
    }
    else{
      color = 6;
    }
  }
  else{
    if ((h >= 285 && h <= 360) || (h >= 0  && h <= 45)){//red 
      color = 5;
    }
    else if(h >= 45 && h <= 105){ // yellow
      color = 4;
    }
    else if( h >= 105 && h <= 165){
      color = 3;
    }
    else if (h >= 180 && h <= 285){
      color = 2;
    }
    else{
      color = 8;
    }
  } 
  return color;
}