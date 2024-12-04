// Include the Arduino Stepper Library
#include <Stepper.h>

// LCD
#include <Wire.h>
#include <U8x8lib.h>
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE); 

// 모터 회전 설정
const int STEPS_PER_REV = 15;

// Motor 핀 설정
Stepper stepper_NEMA17(STEPS_PER_REV, 8, 9, 10, 11);

// Sensor configuration
const int sensorPin = 2;              // 감지 센서가 연결된 핀
volatile bool isDetected = false;     // 감지 상태를 나타내는 플래그
unsigned long lastDetectionTime = 0;  // 마지막 감지 시간을 저장
const unsigned long lockoutDelay = 500; // 감지 후 추가 감지를 막는 시간 (500ms)

// Solenoid
const int solPin = 3;   // 솔레노이드 연결 핀 

// 감지 카운트
volatile int count = 0;

void setup() {
  Serial.begin(9600);

  // Sensor 설정
  pinMode(sensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPin), countDetection, FALLING);

  // 모터 초기화
  stepper_NEMA17.setSpeed(60); // 기본 속도 설정

  // Solenoid 설정
  pinMode(solPin, OUTPUT);
  digitalWrite(solPin, LOW); // 초기 상태에서 솔레노이드를 비활성화

  // LCD세팅
  u8x8.begin();  
  u8x8.setPowerSave(0); 
  u8x8.setFont(u8x8_font_7x14B_1x2_f);

  // 초기화 시 카운트 값 LCD에 표시
  oled_str(0, 0, "Count:");
  oled_str(7, 0, String(count)); // count 값을 LCD에 출력
}

void loop() {
  // 감지 시 작업 수행
  if (isDetected) {
    isDetected = false; // 감지 상태 초기화

    // LCD 표출
    oled_str(7, 0, String(count));
  
    // 1. 솔레노이드 활성화
    digitalWrite(solPin, HIGH);
    delay(1000); // 1초 대기 (솔레노이드가 작동되도록)

    // 2. 모터 회전
    stepper_NEMA17.step(STEPS_PER_REV);
    Serial.print("감지 횟수: ");
    Serial.println(count);

    // 3. 모터 회전 완료 후 솔레노이드 비활성화
    delay(1000); // 1초 대기
    digitalWrite(solPin, LOW);
    
  }
}

// 감지 이벤트 처리
void countDetection() {
  unsigned long currentTime = millis();

  // lockoutDelay 시간 이후에만 감지 처리
  if (currentTime - lastDetectionTime > lockoutDelay) {
    isDetected = true; // 감지 플래그 설정
    lastDetectionTime = currentTime; // 마지막 감지 시간 갱신
    count++; // 감지 카운트 증가
  }
}

// 문자 출력
void oled_str(int x, int y, String cmds){  
  int str_len=cmds.length() + 1;
  char char_array1[str_len]; 
  cmds.toCharArray(char_array1, str_len);
  u8x8.drawString(x,y,char_array1);
}