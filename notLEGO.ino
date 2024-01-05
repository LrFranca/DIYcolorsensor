// Variáveia para armazenar os resultados

unsigned long tempo_inicio;
unsigned long tempo_fim;
int valueR = 0;
int valueG = 0;
int valueB = 0;

// constante para configuração do prescaler
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
int timeMaxLight = 300;
void setup() {
Serial.begin(9600);
pinMode(A0, INPUT);
pinMode(8, OUTPUT);
pinMode(10, OUTPUT);
pinMode(9, OUTPUT);
// configura o preescaler do ADC
ADCSRA &= ~PS_128; //limpa configuração da biblioteca do arduino

// valores possiveis de prescaler só deixar a linha com prescaler desejado
// PS_16, PS_32, PS_64 or PS_128
//ADCSRA |= PS_128; // 64 prescaler
//ADCSRA |= PS_64; // 64 prescaler
// ADCSRA |= PS_32; // 32 prescaler
 //ADCSRA |= PS_16; // 16 prescaler
  ADCSRA |= 4; // 16 prescaler
}

void loop() { 
// leitura
tempo_inicio = micros(); //marca tempo de inicio de leitura
getRawDATA(A0);
tempo_fim = micros(); //le tempo no fim da conversão
digitalWrite(10, 0);
//exibe valor lido e tempo de conversão
Serial.print("Values:");
Serial.print("valueR : ");Serial.println(valueR);
Serial.print("valueG : ");Serial.println(valueG);
Serial.print("valueB : ");Serial.println(valueB);
Serial.println();
Serial.print(" Cycle timing : ");
Serial.print(tempo_fim - tempo_inicio);
Serial.println("uS");
delay(500);
}
void getRawDATA(byte analogPin){
digitalWrite(10, 0);
digitalWrite(8, 1);
delayMicroseconds(timeMaxLight);
valueR = analogRead(analogPin); //le valor convertido
digitalWrite(8, 0);
digitalWrite(9, 1);
delayMicroseconds(timeMaxLight);
valueG = analogRead(analogPin); //le valor convertido
digitalWrite(9, 0);
digitalWrite(10, 1);
delayMicroseconds(timeMaxLight);
valueB = analogRead(analogPin); //le valor convertido
}
