#define analogA A0
#define color3 10

unsigned int LEDtimeM = 333;
unsigned int pht = 0;

void setup() {
    Serial.begin(9600);
    
    pinMode(analogA, INPUT);
    pinMode(color3, OUTPUT);

    digitalWrite(color3 , 0);
    delay(1000);
    int phtREF_OFF = analogRead(analogA);

    digitalWrite(color3 , 1);
    delay(1000);
    int phtREF_ON = analogRead(analogA);
    
    digitalWrite(color3 , 0);
    delayMicroseconds(LEDtimeM);
    int phtOFF1 = analogRead(analogA);
    
    digitalWrite(color3 , 1);
    delayMicroseconds(LEDtimeM);
    int phtON1  = analogRead(analogA);
    
    digitalWrite(color3 , 0);
    delayMicroseconds(LEDtimeM);
    int phtOFF2 = analogRead(analogA);
    
    digitalWrite(color3 , 1);
    delayMicroseconds(LEDtimeM);
    int phtON2  = analogRead(analogA);

    digitalWrite(color3 , 0);

  Serial.print("PhotoTransisor reference values:   "); Serial.print("ON: "); Serial.print(phtREF_ON); Serial.print("   OFF: "); Serial.println(phtREF_OFF);
  Serial.print("PhotoTransisor OFF 1 : ") ; Serial.println(phtOFF1);
  Serial.print("PhotoTransisor ON  1 : ") ; Serial.println(phtON1);
  Serial.print("PhotoTransisor OFF 2 : ") ; Serial.println(phtOFF2);
  Serial.print("PhotoTransisor ON  2 : ") ; Serial.println(phtON2);
  Serial.println();
  
  //delay(1000);
  //Serial.print("PhotoTransisor OFF value: ") ; Serial.println(analogRead(analogA));
  
}
void loop() {


}
