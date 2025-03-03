#include <Arduino.h>

const int SEGMENT_PINS[] = {32, 33, 25, 26, 27, 14, 12, 15}; // A B C D E F G DP
const int DIGIT_PINS[] = {19, 18, 17, 16};                   // 位选控制

// 0-9 的段码定义（共阴极数码管）
const uint8_t NUMBERS[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

// 要显示的数字 1 2 3 4
const int DISPLAY_DIGITS[4] = {1, 2, 3, 4};

// 显示单个数字
void displayDigit(int digit, int number)
{
  // 熄灭所有数码管位
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(DIGIT_PINS[i], HIGH);
  }

  // 取出数字对应的段码并点亮
  uint8_t segments = NUMBERS[number];
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(SEGMENT_PINS[i], (segments >> i) & 0x01);
  }

  // 选中当前位（共阴极：低电平点亮）
  digitalWrite(DIGIT_PINS[digit], LOW);

  // 保持一点时间，确保稳定显示
  delay(5);

  // 熄灭当前位，避免重影
  digitalWrite(DIGIT_PINS[digit], HIGH);
}

void setup()
{
  // 设置段码引脚为输出
  for (int i = 0; i < 8; i++)
  {
    pinMode(SEGMENT_PINS[i], OUTPUT);
  }
  // 设置位选引脚为输出
  for (int i = 0; i < 4; i++)
  {
    pinMode(DIGIT_PINS[i], OUTPUT);
    digitalWrite(DIGIT_PINS[i], HIGH); // 初始熄灭所有位
  }
}

void loop()
{
  for (int i = 0; i < 4; i++)
  {
    displayDigit(i, DISPLAY_DIGITS[i]); // 显示当前位
    // delay(5);                           // 稍作停留（20ms 扫描整个数码管 4 次，50Hz 视觉无闪烁）
  }
}
