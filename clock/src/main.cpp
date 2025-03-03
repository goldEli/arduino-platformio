#include <Arduino.h>

#include <WiFi.h>
#include <time.h>

// WiFi 配置
const char* ssid = "";
const char* password = "";

// 数码管引脚
const int SEGMENT_PINS[] = {32, 33, 25, 26, 27, 14, 12};  // A B C D E F G DP
const int DIGIT_PINS[] = {19, 18, 17, 16};  // 位选
const int TWO_DOT_PIN = 15;  // 小数点

bool colonState = false;  // `:` 闪烁状态

// 0-9 段码定义（共阴极）
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

// 存储当前时间的数组 {H1, H2, M1, M2}
int displayDigits[4] = {2, 0, 4, 4};  


// 获取系统时间并更新数码管显示
void updateTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("无法获取时间");
    return;
  }
  
  // 解析时间（时:分）
  int hour = timeinfo.tm_hour;
  int minute = timeinfo.tm_min;

  // 拆分为 4 个数字
  displayDigits[0] = hour / 10;
  displayDigits[1] = hour % 10;
  displayDigits[2] = minute / 10;
  displayDigits[3] = minute % 10;

  Serial.printf("当前时间: %02d:%02d\n", hour, minute);
}

// 点亮所有数码管
void waitingDisplay() {
  for (int i = 0; i < sizeof(DIGIT_PINS) / sizeof(DIGIT_PINS[0]); i++)
  {
    digitalWrite(DIGIT_PINS[i], LOW);
    for (int j = 0; j < sizeof(SEGMENT_PINS) / sizeof(SEGMENT_PINS[0]); j++)
    {
      digitalWrite(SEGMENT_PINS[j], HIGH);
    }
  }

  // digitalWrite(TWO_DOT_PIN, HIGH);
}

// 显示单个数字
void displayDigit(int digit, int number) {
  // 关闭所有位选
  for (int i = 0; i < 4; i++) {
    digitalWrite(DIGIT_PINS[i], HIGH);
  }

  // 设置段码（控制 DP 小数点）
  uint8_t segments = NUMBERS[number]; 
  for (int i = 0; i < sizeof(SEGMENT_PINS) / sizeof(SEGMENT_PINS[0]); i++) {
    digitalWrite(SEGMENT_PINS[i], (segments >> i) & 0x01);
  }

  // 选中当前位
  digitalWrite(DIGIT_PINS[digit], LOW);
  delay(5);
  digitalWrite(DIGIT_PINS[digit], HIGH);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("正在连接WiFi...");
  // 设置数码管引脚为输出
  pinMode(TWO_DOT_PIN, OUTPUT);
  for (int i = 0; i < sizeof(SEGMENT_PINS) / sizeof(SEGMENT_PINS[0]); i++) pinMode(SEGMENT_PINS[i], OUTPUT);
  for (int i = 0; i < 4; i++) pinMode(DIGIT_PINS[i], OUTPUT);
  waitingDisplay();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi 连接成功！");

  // 设置 NTP 时间
  configTime(8 * 3600, 0, "pool.ntp.org");



  updateTime();  // 初始化时更新时间
}


void loop() {
  // 每 1 秒更新时间
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 1000) {
    lastUpdate = millis();
    updateTime();
    colonState = !colonState;  // 每秒切换 `:` 状态
    digitalWrite(TWO_DOT_PIN, colonState ? LOW : HIGH);  // 共阴极：低电平点亮
  }


  // 显示数码管（动态扫描）
  for (int i = 0; i < 4; i++) {
    displayDigit(i, displayDigits[3-i]);
    // delay(5);
  }

}
