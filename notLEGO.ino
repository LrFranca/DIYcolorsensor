const int RED_PIN = 8;
const int GREEN_PIN = 9;
const int BLUE_PIN = 10;
int phtPin;

unsigned long tempo_inicio;
unsigned long tempo_fim;
int valueR = 0;
int valueG = 0;
int valueB = 0;


// constante para configuração do prescaler
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

class colorSensor {
private:

  unsigned long interval;
  unsigned long previousTime;
  unsigned long currentTime;
  int color;
  int phtValueR;
  int phtValueG;
  int phtValueB;
  int whiteValueR;
  int whiteValueG;
  int whiteValueB;
  float redRatio;
  float greenRatio;
  float blueRatio;
  int pastReading1;
  int pastReading2;
  int pastReading3;
  int pastReading4;
  int pastReading5;
  int readingIndex;
  int timeMaxLight;

public:
  colorSensor(int pPin, unsigned long i) {
    phtPin = pPin;
    timeMaxLight = i;
    previousTime = 0;
    currentTime = 0;
    color = 0;
    phtValueR = 0;
    phtValueG = 0;
    phtValueB = 0;
    whiteValueR = 0;
    whiteValueG = 0;
    whiteValueB = 0;
    redRatio = 0;
    greenRatio = 0;
    blueRatio = 0;
  }

  void blink() {
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(RED_PIN, HIGH);
    delayMicroseconds(timeMaxLight);
    phtValueR = analogRead(phtPin);
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    delayMicroseconds(timeMaxLight);
    phtValueG = analogRead(phtPin);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
    delayMicroseconds(timeMaxLight);
    phtValueB = analogRead(phtPin);
  }

  void printPHT() {
    Serial.print("PHT values: R = ");
    Serial.print(phtValueR);
    Serial.print(", G = ");
    Serial.print(phtValueG);
    Serial.print(", B = ");
    Serial.println(phtValueB);
  }

  void calibrate() {
    blink();
    whiteValueR = phtValueR;
    whiteValueG = phtValueG;
    whiteValueB = phtValueB;
    int averageSUM = whiteValueR + whiteValueG + whiteValueB;
    redRatio = averageSUM / (whiteValueR * 3);
    greenRatio = averageSUM / (whiteValueG * 3);
    blueRatio = averageSUM / (whiteValueB * 3);
  }

  void printCalibratedPHT() {
    float calibratedR = phtValueR * redRatio;
    float calibratedG = phtValueG * greenRatio;
    float calibratedB = phtValueB * blueRatio;
    Serial.print("Calibrated PHT values: R = ");
    Serial.print(calibratedR);
    Serial.print(", G = ");
    Serial.print(calibratedG);
    Serial.print(", B = ");
    Serial.println(calibratedB);
  }

  int getColor() {
    blink();
    float calibratedR = phtValueR * redRatio;
    float calibratedG = phtValueG * greenRatio;
    float calibratedB = phtValueB * blueRatio;
    return 0;
  }
};

colorSensor sensor(A0, 300);

void setup() {
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(phtPin, INPUT);
  ADCSRA &= ~PS_128;
  ADCSRA |= PS_16;
  sensor.calibrate();
}

void loop() {

  tempo_inicio = micros();  //marca tempo de inicio de leitura
  sensor.getColor();
  tempo_fim = micros();  //le tempo no fim da conversão
  digitalWrite(10, 0);
  sensor.printPHT();
  Serial.println();
  Serial.print("Timing cycle : ");
  Serial.print(tempo_fim - tempo_inicio);
  Serial.println("µS");
  delay(500);
}
void getRawDATA(byte analogPin) {
  digitalWrite(10, 0);
  digitalWrite(8, 1);
  delayMicroseconds(300);
  valueR = analogRead(analogPin);  //le valor convertido
  digitalWrite(8, 0);
  digitalWrite(9, 1);
  delayMicroseconds(300);
  valueG = analogRead(analogPin);  //le valor convertido
  digitalWrite(9, 0);
  digitalWrite(10, 1);
  delayMicroseconds(300);
  valueB = analogRead(analogPin);  //le valor convertido
}
