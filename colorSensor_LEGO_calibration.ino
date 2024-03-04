//#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>

//Adafruit_SSD1306 display(128, 64, &Wire, -1);
class colorSensor {
private:

  int reflectedOffR;
  int reflectedOnR;
  int reflectedOffG;
  int reflectedOnG;
  int reflectedOffB;
  int reflectedOnB;
  int minusR = 0;
  int minusG = 0;
  int minusB = 0;
  int R_raw;
  int G_raw;
  int B_raw;
  byte pht;
  byte r_pin;
  byte g_pin;
  byte b_pin;
  int blackMin[3] = { 5, 10, 10 };
  int blackMax[3] = { 90, 90, 90 };     //85 85 85
  int blueMin[3] = { 20, 70, 110 };     //{20, 70, 120};
  int blueMax[3] = { 200, 250, 420 };   //200 230 350
  int greenMin[3] = { 15, 80, 30 };     //15 80 30
  int greenMax[3] = { 100, 470, 180 };  //{100, 330, 180};
  int redMin[3] = { 60, 15, 10 };       //100 , 15, 10
  int redMax[3] = { 500, 150, 120 };
  int yellowMin[3] = { 150, 140, 30 };
  int yellowMax[3] = { 545, 350, 160 };  //{545, 350, 180};
  int whiteMin[3] = { 140, 180, 100 };   //200 200 200
  int whiteMax[3] = { 740, 740, 740 };
  const unsigned char PS_16 = (1 << ADPS2);
  const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

public:
  colorSensor(byte analogUser, byte r, byte g, byte b) {

    pht = analogUser;
    r_pin = r;
    g_pin = g;
    b_pin = b;
    R_raw = 0;
    G_raw = 0;
    B_raw = 0;
  }

  void setColorSensor() {
    ADCSRA &= ~PS_128;
    ADCSRA |= PS_16;
    pinMode(r_pin, OUTPUT);
    pinMode(g_pin, OUTPUT);
    pinMode(b_pin, OUTPUT);
    pinMode(pht, INPUT);
  }

  void getRawDATA() {
    unsigned long fallTime = 350;  //200 //100 //400
    unsigned long riseTime = 350;  //200 //300 //400
    byte margin_no_color = 3;

    digitalWrite(r_pin, HIGH);
    delayMicroseconds(riseTime);
    reflectedOnR = analogRead(pht);
    digitalWrite(r_pin, LOW);
    delayMicroseconds(fallTime);
    reflectedOffR = analogRead(pht);
    minusR = reflectedOnR - reflectedOffR;
    if (minusR <= margin_no_color) {
      R_raw = 0;
    } else {
      R_raw = minusR - margin_no_color;
    }

    digitalWrite(g_pin, HIGH);
    delayMicroseconds(riseTime);
    reflectedOnG = analogRead(pht);
    digitalWrite(g_pin, LOW);
    delayMicroseconds(fallTime);
    reflectedOffG = analogRead(pht);
    minusG = reflectedOnG - reflectedOffG;
    if (minusG <= margin_no_color) {
      G_raw = 0;
    } else {
      G_raw = minusG - margin_no_color;
    }

    digitalWrite(b_pin, HIGH);
    delayMicroseconds(riseTime);
    reflectedOnB = analogRead(pht);
    digitalWrite(b_pin, LOW);
    delayMicroseconds(fallTime);
    reflectedOffB = analogRead(pht);
    minusB = reflectedOnB - reflectedOffB;
    if (minusB <= margin_no_color) {
      B_raw = 0;
    } else {
      B_raw = minusB - margin_no_color;
    }
  }

  byte getColor() {

    getRawDATA();
    if ((R_raw <= 10) && (G_raw <= 10) && (B_raw <= 10)) {
      return 0;

    } else if ((R_raw >= blackMin[0]) && (G_raw >= blackMin[1]) && (B_raw >= blackMin[2]) && (R_raw <= blackMax[0]) && (G_raw <= blackMax[1]) && (B_raw <= blackMax[2])) {
      return 1;
    } else if ((R_raw >= blueMin[0]) && (G_raw >= blueMin[1]) && (B_raw >= blueMin[2]) && (R_raw <= blueMax[0]) && (G_raw <= blueMax[1]) && (B_raw <= blueMax[2]) && ((B_raw > R_raw) && (B_raw > G_raw))) {
      return 2;
    } else if ((R_raw >= greenMin[0]) && (G_raw >= greenMin[1]) && (B_raw >= greenMin[2]) && (R_raw <= greenMax[0]) && (G_raw <= greenMax[1]) && (B_raw <= greenMax[2]) && ((G_raw > R_raw) && (G_raw > B_raw))) {
      return 3;
    } else if ((R_raw >= redMin[0]) && (G_raw >= redMin[1]) && (B_raw >= redMin[2]) && (R_raw <= redMax[0]) && (G_raw <= redMax[1]) && (B_raw <= redMax[2]) && ((R_raw > G_raw) && (R_raw > B_raw))) {
      return 5;
    } else if ((R_raw >= yellowMin[0]) && (G_raw >= yellowMin[1]) && (B_raw >= yellowMin[2]) && (R_raw <= yellowMax[0]) && (G_raw <= yellowMax[1]) && (B_raw <= yellowMax[2])) {
      return 4;
    } else if ((R_raw >= whiteMin[0]) && (G_raw >= whiteMin[1]) && (B_raw >= whiteMin[2]) && (R_raw <= whiteMax[0]) && (G_raw <= whiteMax[1]) && (B_raw <= whiteMax[2])) {
      return 6;
    } else {
      return 7;
    }
  }

    void printPHT() {
    Serial.print("R = ");
    Serial.print(R_raw);
    Serial.print(", G = ");
    Serial.print(G_raw);
    Serial.print(", B = ");
    Serial.print(B_raw);
    Serial.print(", color = ");
    Serial.println(getColor());
  }
};
colorSensor sensor(A0, 8, 9, 10);

void setup() {
  sensor.setColorSensor();
  //setOled();
  Serial.begin(9600);
}

void loop() {
  bool print = false;
  //getColor();
  //show();
  //Serial.println(sensor.getColor());
  sensor.printPHT();
}
