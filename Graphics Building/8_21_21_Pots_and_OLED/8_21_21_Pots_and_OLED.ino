#include <Wire.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_GFX.h>

#define OLED_RESET -1

Adafruit_SH1106 display(OLED_RESET);

const int muxIn = 16;

const int muxPin0 = 38;
const int muxPin1 = 39;
const int muxPin2 = 40;
const int muxPin3 = 41;

uint8_t sigValue[8];



void setup() {

  Serial.begin(9600);

  display.begin(SH1106_SWITCHCAPVCC, 0x3C);

  display.display();
  display.clearDisplay();
  display.setRotation(2);

  pinMode(muxPin0, OUTPUT);
  pinMode(muxPin1, OUTPUT);
  pinMode(muxPin2, OUTPUT);
  pinMode(muxPin3, OUTPUT);

}

void loop() {

  Serial.println();
  Serial.println("These be the values");
  Serial.println("===========================");
  Serial.println();

  for (int i = 0; i < 8; i++) {

    sigValue[i] = readMux(i);

    Serial.print(sigValue[i]);
    Serial.print("\t");

  }

  textStrips();
  envelope();

  display.display();

  display.clearDisplay();

  Serial.println();
}

uint8_t readMux(uint8_t channel) {

  digitalWrite(muxPin0, bitRead(channel, 0));
  digitalWrite(muxPin1, bitRead(channel, 1));
  digitalWrite(muxPin2, bitRead(channel, 2));
  digitalWrite(muxPin3, bitRead(channel, 3));

  int muxValue = map(analogRead(muxIn), 0, 1023, 0, 127);
  // return the  analog value
  return muxValue;

}

void textStrips() {

  uint8_t stripX[] = {7, 39, 71, 104};
  uint8_t topStripY = 1;
  uint8_t topParamY = 13;

  uint8_t bottomStripY = 55;
  uint8_t bottomParamY = 44;

  display.fillRect(0, 0, 128, 10, WHITE);
  display.fillRect(0, 53, 128, 10, WHITE);
  display.setTextSize(0);
  display.setTextColor(INVERSE);

  //top text strip
  display.setCursor(stripX[0], topStripY);  display.println(F("atk"));
  display.setCursor(stripX[1], topStripY); display.print(F("dcy"));
  display.setCursor(stripX[2], topStripY); display.print(F("sus"));
  display.setCursor(stripX[3], topStripY);  display.print(F("rls"));

  display.setCursor(stripX[0], topParamY);  display.println(sigValue[0]);
  display.setCursor(stripX[1], topParamY); display.print(sigValue[1]);
  display.setCursor(stripX[2], topParamY); display.print(sigValue[2]);
  display.setCursor(stripX[3], topParamY);  display.print(sigValue[3]);

  //bottom text strip
  display.setCursor(stripX[0], bottomStripY);  display.print(F("a %"));
  display.setCursor(stripX[1], bottomStripY); display.print(F("d %"));
  display.setCursor(stripX[2], bottomStripY); display.print(F("s %"));
  display.setCursor(stripX[3], bottomStripY);  display.print(F("r %"));

  display.setCursor(stripX[0], bottomParamY);  display.print(sigValue[4]);
  display.setCursor(stripX[1], bottomParamY); display.print(sigValue[5]);
  display.setCursor(stripX[2], bottomParamY); display.print(sigValue[6]);
  display.setCursor(stripX[3], bottomParamY);  display.print(sigValue[7]);

}

void envelope() {

  uint8_t startPoint = 11;
  uint8_t paramWindow = 28;
  uint8_t envCeiling = 23;
  uint8_t envFloor = 38;

  uint8_t atkParam = (sigValue[0] / 5) + startPoint;
  uint8_t decayParam = (sigValue[1] / 5) + atkParam;
  uint8_t susParamH = (sigValue[2] / 5) + decayParam; //H for horizontal
  uint8_t rlsParam = (sigValue[3] / 5) + susParamH;

    // not necessary for this env
    // V for vertical
  //  uint8_t susParamV =  (-sigValue [2] / 8) + envFloor

  uint8_t atkAmt = (-sigValue [4] / 8) + envFloor;
  uint8_t decayAmt = (-sigValue [5] / 8) + envFloor;
  uint8_t susAmt = (-sigValue [6] / 8) + envFloor;
  uint8_t rlsAmt = (-sigValue [7] / 8) + envFloor;

  display.drawLine(startPoint, envFloor, atkParam, atkAmt, WHITE);
  display.drawLine(atkParam, atkAmt, decayParam, decayAmt, WHITE);
  display.drawLine(decayParam, decayAmt, susParamH, susAmt, WHITE);
  display.drawLine(susParamH, susAmt, rlsParam, rlsAmt, WHITE);



}
