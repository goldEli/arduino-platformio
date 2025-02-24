#include <Arduino.h>
// #define RED_PIN 32
// #define yellowPin 33
// #define greenPin 25
// #define BUTTON_PIN 34

const int ledPin = 32;    // LED 连接 D13
const int yellowPin = 33; // 黄灯连接 D12
const int greenPin = 25;  // 绿灯连接 D11
const int buttonPin = 34;  // 按钮连接 D2
bool ledState = false;    // 记录 LED 是否闪烁
bool lastButtonState = HIGH; // 记录上一次按钮状态
unsigned long lastToggleTime = 0; // 记录 LED 切换时间
unsigned long lastBlinkTime = 0;  // 记录 LED 闪烁时间
const unsigned long delayTime = 1000 * 60 * 30; // 60秒（1分钟）
const unsigned long blinkInterval = 500; // LED 闪烁间隔（500ms）

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP); // 内部上拉电阻
    digitalWrite(ledPin, LOW); // 初始状态 LED 关闭
    digitalWrite(yellowPin, LOW); // 初始状态 LED 关闭
    digitalWrite(greenPin, LOW); // 初始状态 LED 关闭
    Serial.begin(9600);

    // 启动后延迟一分钟，然后 LED 开始闪烁
    Serial.println("启动，LED 将在 60 秒后开始闪烁...");
    delay(delayTime);
    ledState = true;
    lastBlinkTime = millis(); // 记录闪烁开始时间
    Serial.println("LED 开始闪烁");
}

void loop() {
    bool currentButtonState = digitalRead(buttonPin);

    // 按钮按下时，熄灭 LED，并开始计时
    if (currentButtonState == LOW && lastButtonState == HIGH) {
        ledState = false;
        digitalWrite(ledPin, LOW); // LED 关闭
        digitalWrite(yellowPin, LOW); 
        digitalWrite(greenPin, LOW);
        lastToggleTime = millis(); // 记录熄灭时间
        Serial.println("按钮按下，LED 熄灭");
    }

    // 如果 LED 关闭，且经过 60 秒，重新开始闪烁
    if (!ledState && (millis() - lastToggleTime >= delayTime)) {
        ledState = true;
        lastBlinkTime = millis(); // 记录闪烁开始时间
        Serial.println("60 秒已到，LED 重新开始闪烁");
    }

    // 处理 LED 闪烁
    if (ledState) {
        if (millis() - lastBlinkTime >= blinkInterval) {
            digitalWrite(ledPin, !digitalRead(ledPin)); // 取反 LED 状态
            digitalWrite(greenPin, !digitalRead(greenPin)); // 取反 LED 状态
            digitalWrite(yellowPin, !digitalRead(yellowPin)); // 取反 LED 状态
            lastBlinkTime = millis(); // 更新闪烁时间
        }
    }

    lastButtonState = currentButtonState; // 更新按钮状态
}
