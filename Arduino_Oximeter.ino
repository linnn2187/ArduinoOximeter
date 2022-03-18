#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <LiquidCrystal_I2C.h>

#define REPORTING_PERIOD_MS 1000  // 數據顯示間隔 (毫秒)
PulseOximeter pox;
uint32_t tsLastReport = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD I2C 位址和長寬
void setup() {
  // initial LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Arduino Oximeter");
  delay(1000);
  // initial MAX30100
  if (!pox.begin()) {
    lcd.setCursor(0, 1);
    lcd.print("Failed to init!");
    while (true) {}
  }
}
void loop() {
  pox.update();  // update MAX30100 讀數
  // 每隔指定的時間讀一次讀數, 並顯示在 LCD 上
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    float bpm = pox.getHeartRate();
    uint8_t spo2 = pox.getSpO2();
    lcd.clear();
    lcd.home();
    lcd.print("  Bpm : " + String(bpm));  // 顯示脈搏 bpm
    lcd.setCursor(0, 1);
    lcd.print("  SpO2: " + String(spo2) + "%");  // 顯示血氧濃度
    tsLastReport = millis();
  }
}
