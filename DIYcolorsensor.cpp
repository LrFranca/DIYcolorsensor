#include <Arduino.h>
#include "DIYcolorsensor.h"

ColorSensor::ColorSensor(byte r, byte g, byte b, byte p, float RmS, float GmS, float BmS) : r_pin(r), g_pin(g), b_pin(b), pht(p) {

    pinMode(r_pin, OUTPUT);
    pinMode(g_pin, OUTPUT);
    pinMode(b_pin, OUTPUT);
    pinMode(pht, INPUT);
    Rm = RmS;
    Gm = GmS;
    Bm = BmS;
}

void ColorSensor::rgbToHSB(uint16_t r, uint16_t g, uint16_t b) {
    float R = float(r) / 255.0;
    float G = float(g) / 255.0;
    float B = float(b) / 255.0;

    float max_val = max(R, max(G, B));
    float min_val = min(R, min(G, B));
    float delta = max_val - min_val;

    brightness = max_val;

    if (max_val == 0) {
        saturation = 0;
    } else {
        saturation = delta / max_val;
    }

    if (delta != 0) {
        if (max_val == R) {
            hue = 60 * fmod((G - B) / delta, 6);
        } else if (max_val == G) {
            hue = 60 * ((B - R) / delta + 2);
        } else {
            hue = 60 * ((R - G) / delta + 4);
        }
    }

    if (hue < 0) {
        hue += 360;
    }
}

void ColorSensor::getRGB() {
    inicial = micros();
    
    digitalWrite(r_pin, HIGH);
    delayMicroseconds(riseTime);
    reflectedOnR = analogRead(pht);
    digitalWrite(r_pin, LOW);
    delayMicroseconds(fallTime);
    reflectedOffR = analogRead(pht);
    minusR = reflectedOnR - reflectedOffR;
    R_raw = (minusR <= margin_no_color) ? 0 : Rm * (minusR - margin_no_color);

    digitalWrite(g_pin, HIGH);
    delayMicroseconds(riseTime);
    reflectedOnG = analogRead(pht);
    digitalWrite(g_pin, LOW);
    delayMicroseconds(fallTime);
    reflectedOffG = analogRead(pht);
    minusG = reflectedOnG - reflectedOffG;
    G_raw = (minusG <= margin_no_color) ? 0 : Gm * (minusG - margin_no_color);

    digitalWrite(b_pin, HIGH);
    delayMicroseconds(riseTime);
    reflectedOnB = analogRead(pht);
    digitalWrite(b_pin, LOW);
    delayMicroseconds(fallTime);
    reflectedOffB = analogRead(pht);
    minusB = reflectedOnB - reflectedOffB;
    B_raw = (minusB <= margin_no_color) ? 0 : Bm * (minusB - margin_no_color);
    final = micros();
}

byte ColorSensor::getColor() {
    getRGB();

    if ((R_raw <= 10) && (G_raw <= 10) && (B_raw <= 10)) {
        color = 0;
    } else if ((R_raw >= blackMin[0]) && (G_raw >= blackMin[1]) && (B_raw >= blackMin[2]) &&
               (R_raw <= blackMax[0]) && (G_raw <= blackMax[1]) && (B_raw <= blackMax[2])) {
        color = 1;
    } else if ((R_raw >= greenMin[0]) && (G_raw >= greenMin[1]) && (B_raw >= greenMin[2]) &&
               (R_raw <= greenMax[0]) && (G_raw <= greenMax[1]) && (B_raw <= greenMax[2]) &&
               ((G_raw > R_raw) && (G_raw > B_raw))) {
        color = 3;
    } else if ((R_raw >= redMin[0]) && (G_raw >= redMin[1]) && (B_raw >= redMin[2]) &&
               (R_raw <= redMax[0]) && (G_raw <= redMax[1]) && (B_raw <= redMax[2]) &&
               ((R_raw > G_raw) && (R_raw > B_raw))) {
        color = 5;
    } else if ((R_raw >= whiteMin[0]) && (G_raw >= whiteMin[1]) && (B_raw >= whiteMin[2]) &&
               (R_raw <= whiteMax[0]) && (G_raw <= whiteMax[1]) && (B_raw <= whiteMax[2])) {
        color = 6;
    } else if ((R_raw >= yellowMin[0]) && (G_raw >= yellowMin[1]) && (B_raw >= yellowMin[2]) &&
               (R_raw <= yellowMax[0]) && (G_raw <= yellowMax[1]) && (B_raw <= yellowMax[2])) {
        color = 4;
    } else if ((R_raw >= blueMin[0]) && (G_raw >= blueMin[1]) && (B_raw >= blueMin[2]) &&
               (R_raw <= blueMax[0]) && (G_raw <= blueMax[1]) && (B_raw <= blueMax[2])) {
        color = 2;
    } else if ((R_raw >= silverMin[0]) && (G_raw >= silverMin[1]) && (B_raw >= silverMin[2]) &&
               (R_raw <= silverMax[0]) && (G_raw <= silverMax[1]) && (B_raw <= silverMax[2])) {
        color = 7;
    } else {
        color = 8;
    }
    return color;
}

void ColorSensor::printValues() {
    Serial.print("Red: ");
    Serial.print(R_raw);
    Serial.print("  |  Green: ");
    Serial.print(G_raw);
    Serial.print("  |  Blue: ");
    Serial.println(B_raw);
    Serial.print("Frequency: ");
    Serial.print(1000000 / (final - inicial));
    Serial.println("Hz");

    Serial.print("Color: ");
    Serial.println(color);
    Serial.println();
}

int ColorSensor::darkness() {
    digitalWrite(g_pin, HIGH);
    delayMicroseconds(riseTime);
    reflectedOnG = analogRead(pht);
    digitalWrite(g_pin, LOW);
    delayMicroseconds(fallTime);
    reflectedOffG = analogRead(pht);
    minusG = reflectedOnG - reflectedOffG;
    return (minusG <= margin_no_color) ? 0 : minusG - margin_no_color;
}

bool ColorSensor::isBlack() {
    return darkness() <= cutOffValue;
}

