#include <Arduino.h>
#define RED_PIN 32
#define YELLOW_PIN 33
#define GREEN_PIN 25

bool sleepState = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello, ESP32!");
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void marquee(int p, int d) {
  digitalWrite(p, HIGH);
  delay(d);
  digitalWrite(p, LOW);
  delay(d);
}

void sleep(int d) {
  delay(d);
}

void loop() {
  if (!sleepState) {
    sleep(1000 * 60 * 30);
    sleepState = !sleepState;
  }
  marquee(RED_PIN, 100);
  marquee(YELLOW_PIN, 100);
  marquee(GREEN_PIN, 100);
}