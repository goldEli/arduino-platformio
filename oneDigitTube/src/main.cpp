#include <Arduino.h>

// 点亮一位数码管
// a  b  c  d  e  f  g  dp
// 32 33 25 26 27 14 12 4
const int seg_pins[] = {32, 33, 25, 26, 27, 14, 12, 4}; // a, b, c, d, e, f, g, dp

// 0-9 的段码（共阴极）
const byte digitCodes[10] = {
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

void displayDigit(int num)
{
  if (num < 0 || num > 9)
    return; // 确保输入有效
  byte code = digitCodes[num];
  for (int i = 0; i < 8; i++)
  {
    // 逐位输出
    digitalWrite(seg_pins[i], (code >> i) & 1);
  }
}

void setup()
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(seg_pins[i], OUTPUT);
  }
}

void loop()
{
  // 不需要执行任何内容
  for (int i = 0; i <= 9; i++)
  {
    displayDigit(i);
    delay(1000); // 显示 1 秒
  }
}
