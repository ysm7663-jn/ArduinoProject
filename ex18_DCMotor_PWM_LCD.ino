// 9V 배터리는 모터드라이브에 연결
// 보드에 직접 할 경우 보드의 전압 안정성에 의해 전압 변동이 생길 수 있어 정상적으로 반영이 안 됨

// DC 모터(Direct Current, 직류)는 +, - 상관없이 걸어놔도 상관없음

#include <Wire.h>                        // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C2.h>          // LCD 1602 I2C용 라이브러리

// 주소를 찾는 코드를 통해 주소를 찾아내면 됨
LiquidCrystal_I2C2 lcd(0x27, 16, 2);     // 접근주소: 0x3F or 0x27

int in1 = 7;
int in2 = 5;
int led = 11;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {

  lcd.begin();                    // lcd 초기화
  lcd.backlight();                // 백라이트 켜기

  int resistance = analogRead(A0);
  analogWrite(led, resistance/4);
  int motor = map(resistance, 0, 1023, 0, 255);
  analogWrite(in2, motor);

  lcd.setCursor(0,0);             // 1번째, 1라인  
  lcd.print("speed:");

  lcd.setCursor(7,0);
  lcd.print(resistance);

}
