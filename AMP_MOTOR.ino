// Include the Arduino Stepper Library
#include <Stepper.h>

// 모터 회전 
const int STEPS_PER_REV = 15;

// Motor 핀 설절
Stepper stepper_NEMA17(STEPS_PER_REV, 8, 9, 10, 11);

// Sensor configuration
const int sensorPin = 2;              // 감지 센서가 연결된 핀
volatile bool isDetected = false;     // 감지 상태를 나타내는 플래그
unsigned long lastDetectionTime = 0;  // 마지막 감지 시간을 저장
const unsigned long lockoutDelay = 500; // 감지 후 추가 감지를 막는 시간 (500ms)

// 감지 카운트
volatile int count = 0;

void setup() {
  Serial.begin(9600);

  // Sensor 설정
  pinMode(sensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPin), countDetection, FALLING);

  // 모터 초기화
  stepper_NEMA17.setSpeed(60); // 기본 속도 설정
}

void loop() {
  // 감지 시 모터 회전 작업 수행
  if (isDetected) {
    isDetected = false; // 감지 상태 초기화
    // 모터 회전
    stepper_NEMA17.step(STEPS_PER_REV);
    Serial.print("감지 횟수: ");
    Serial.println(count);
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
