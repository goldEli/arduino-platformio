#include <Arduino.h>

const int SEGMENT_PINS[] = {32, 33, 25, 26, 27, 14, 12, 15};
const int DIGIT_PINS[] = {19, 18, 17, 16};

void setup()
{
  for (int i = 0; i < sizeof(SEGMENT_PINS) / sizeof(SEGMENT_PINS[0]); i++)
  {
    pinMode(SEGMENT_PINS[i], OUTPUT);
  }
  for (int i = 0; i < sizeof(DIGIT_PINS) / sizeof(DIGIT_PINS[0]); i++)
  {
    pinMode(DIGIT_PINS[i], OUTPUT);
  }

  for (int i = 0; i < sizeof(DIGIT_PINS) / sizeof(DIGIT_PINS[0]); i++)
  {
    digitalWrite(DIGIT_PINS[i], LOW);
    for (int j = 0; j < sizeof(SEGMENT_PINS) / sizeof(SEGMENT_PINS[0]); j++)
    {
      sleep(1000);
      digitalWrite(SEGMENT_PINS[j], HIGH);
    }
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  // delay(10); // this speeds up the simulation
}