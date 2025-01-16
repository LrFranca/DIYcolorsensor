#ifndef DIYCOLORSENSOR_H
#define DIYCOLORSENSOR_H

#include <Arduino.h>

class ColorSensor {
private:
    const unsigned char PS_16 = (1 << ADPS2);
    const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    byte r_pin, g_pin, b_pin, pht;
    float Rm, Gm, Bm;
    int reflectedOffR, reflectedOnR, reflectedOffG, reflectedOnG, reflectedOffB, reflectedOnB;
    int blackMin[3], blackMax[3];
    int blueMin[3], blueMax[3];
    int greenMin[3], greenMax[3];
    int redMin[3], redMax[3];
    int yellowMin[3], yellowMax[3];
    int whiteMin[3], whiteMax[3];
    int silverMin[3], silverMax[3];

    int minusR, minusG, minusB;
    byte color;
    unsigned long inicial, final;

public:
    unsigned long fallTime = 350;
    unsigned long riseTime = 350;
    int cutOffValue = 150;
    byte margin_no_color = 3;
    float brightness;
    float saturation;
    float hue;
    int R_raw;
    int G_raw;
    int B_raw;

    ColorSensor(byte r, byte g, byte b, byte p, float RmS = 1, float GmS = 1, float BmS = 1);

    void setBlackMin(int r, int g, int b);
    void setBlackMax(int r, int g, int b);
    void setBlueMin(int r, int g, int b);
    void setBlueMax(int r, int g, int b);
    void setGreenMin(int r, int g, int b);
    void setGreenMax(int r, int g, int b);
    void setRedMin(int r, int g, int b);
    void setRedMax(int r, int g, int b);
    void setYellowMin(int r, int g, int b);
    void setYellowMax(int r, int g, int b);
    void setWhiteMin(int r, int g, int b);
    void setWhiteMax(int r, int g, int b);
    void setSilverMin(int r, int g, int b);
    void setSilverMax(int r, int g, int b);

    void rgbToHSB(uint16_t r, uint16_t g, uint16_t b);
    void getRGB();
    byte getColor();
    void printValues();
    int darkness();
    bool isBlack();
};

#endif // DIYCOLORSENSOR_H
