// vss : LCD GND
// vdd : LCD 5V
// vo : 글자 대비값
// RS : 레지스터
// RW : 읽기 쓰기
// E : 쓰기모드 활성화
// D0 ~ D7 데이터핀
// A : 배경 밝기 전원
// K : 배경 밝기 GND

// LCD : (열, 행)

#include <Wire.h>                        // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C2.h>        // LCD 1602 I2C용 라이브러리

// 주소를 찾는 코드를 통해 주소를 찾아내면 됨
LiquidCrystal_I2C2 lcd(0x27, 16, 2);     // 접근주소: 0x3F or 0x27

void setup()
{
  lcd.begin();
  // Print a message to the LCD.
  lcd.backlight();                // 백라이트 켜기
  lcd.setCursor(0,0);             // 1번째, 1라인
  lcd.print("Hello, world!");
  lcd.setCursor(0,1);             // 1번째, 2라인
  lcd.print("Enjoy - Eduino");
}

void loop() {

}
