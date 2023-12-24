#define color1 8 //R
#define color2 9 //G
#define color3 10 //B

#define pwmColor 7

#define analogA A0
#define analogB A1

unsigned int ldr = 0;
unsigned int pht = 0;

unsigned int LEDtime = 2;
unsigned int LEDtimeM = 250;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Code stated!");
  pinMode(color1, OUTPUT);
  pinMode(color2, OUTPUT);
  pinMode(color3, OUTPUT);
  pinMode(pwmColor, OUTPUT);

  pinMode(analogA, INPUT);
  pinMode(analogB, INPUT);
  
  analogWrite(pwmColor, 190);
}

void loop() {

  digitalWrite(color1 , 1);
  digitalWrite(color2 , 0);
  digitalWrite(color3 , 0);

  //delay(LEDtime);
  delayMicroseconds(LEDtimeM);
  
  digitalWrite(color1 , 0);
  digitalWrite(color2 , 1);
  digitalWrite(color3 , 0);

  //delay(LEDtime);
  delayMicroseconds(LEDtimeM);

  digitalWrite(color1 , 0);
  digitalWrite(color2 , 0);
  digitalWrite(color3 , 1);

  //delay(LEDtime);
  delayMicroseconds(LEDtimeM);/*

  digitalWrite(color1 , 0);
  digitalWrite(color2 , 0);
  digitalWrite(color3 , 0);

  delayMicroseconds(LEDtimeM);*/
}
