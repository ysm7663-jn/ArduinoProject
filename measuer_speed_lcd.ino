#include <Wire.h>                        // I2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C2.h>          // LCD 1602 I2C용 라이브러리

LiquidCrystal_I2C2 lcd(0x27, 16, 2);     // 접근주소: 0x3F or 0x27

const int irSensorPin = 2;  // IR 센서가 연결된 핀
volatile bool firstPass = true;
unsigned long startTime = 0;
unsigned long endTime = 0;
unsigned long lastInterruptTime = 0;

float stickerDistance = 0.1;  // 두 스티커 간의 거리 (단위: 미터)

volatile float speed_mpm = 0; // 속도를 저장할 변수
volatile bool speedCalculated = false; // 속도가 계산되었는지 플래그

void setup() {
  Serial.begin(9600);
  pinMode(irSensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(irSensorPin), detectSticker, CHANGE);
  
  // LCD 초기화
  lcd.begin();              // LCD 16x2 크기로 초기화
  lcd.backlight();          // 백라이트 켜기
  lcd.setCursor(0, 0);
  lcd.print("Speed Meter");
}

void loop() {
  // 속도가 계산되었다면 LCD에 출력
  if (speedCalculated) {
    speedCalculated = false; // 다시 false로 설정하여 다음 인터럽트를 대기

    // LCD에 출력
    lcd.clear();                  // LCD 화면 초기화
    lcd.setCursor(0, 0);          // 1번째 줄 첫 번째 칸
    lcd.print("Speed: ");
    lcd.print(speed_mpm);         // 속도 출력
    lcd.setCursor(0, 1);          // 2번째 줄 첫 번째 칸
    lcd.print("m/min");

    // Serial 모니터에도 출력
    Serial.print("Speed: ");
    Serial.print(speed_mpm);
    Serial.println(" m/min");
    Serial.println("---------------------------");
  }
}

// 인터럽트 핸들러에서 스티커 감지
void detectSticker() {
  unsigned long interruptTime = micros(); // 현재 시간 (마이크로초 단위)

  // 디바운싱 (100ms 이상 간격을 두고 실행)
  if (interruptTime - lastInterruptTime > 100000) {  // 100ms = 100000마이크로초
    if (firstPass) {
      startTime = interruptTime;
      firstPass = false;
      Serial.print("StartTime : ");
      Serial.println(startTime);
    } else {
      endTime = interruptTime;
      unsigned long timeInterval = endTime - startTime;

      float timeInSeconds = timeInterval / 1000000.0; // 시간 간격을 초 단위로 변환

      if (timeInSeconds > 0 && timeInSeconds < 1.0) {
        float speed_mps = stickerDistance / timeInSeconds; // m/s 단위 속도 계산
        float speed_mpm_tmp = speed_mps * 60.0; // m/min 단위로 변환

        // 유효한 속도 범위 내에서만 계산
        if (speed_mpm_tmp > 0 && speed_mpm_tmp < 200.0) {
          speed_mpm = speed_mpm_tmp; // 계산된 속도를 저장
          speedCalculated = true;    // 속도가 계산되었음을 표시
          
          Serial.print("EndTime : ");
          Serial.println(endTime);
          Serial.print("Time Interval: ");
          Serial.println(timeInSeconds);
        }
      }
      firstPass = true; // 다음 측정을 위해 첫 번째 스티커로 다시 설정
    }
    lastInterruptTime = interruptTime;
  }
}