const int sensorPin = 2;  // 적외선 센서 신호 핀

unsigned long startTime = 0;    // 시작
unsigned long endTime = 0;      // 끝

float stickerDistance = 0.005;  // 두 스티커 간의 거리 (단위: 미터)
bool firstPass = true;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), detectSticker, FALLING);
}

void loop() {
  // 메인 루프는 빈 상태로 두고, 모든 처리는 인터럽트에서 진행합니다.
}

void detectSticker() {
  if (firstPass) {
    startTime = micros();  // 첫 번째 스티커가 통과할 때 시간 기록
    firstPass = false;
  } else {
    endTime = micros();  // 두 번째 스티커가 통과할 때 시간 기록
    unsigned long timeInterval = endTime - startTime;
    
    // 속도 계산 (거리 / 시간, 시간은 초 단위로 변환해야 함)
    float timeInSeconds = timeInterval / 1000000.0;
    float speed = stickerDistance / timeInSeconds;  // 속도 단위: m/s
    
    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.println(" m/s");
    
    // 다음 측정을 위해 타이머를 다시 설정
    startTime = endTime;  // 두 번째 스티커를 첫 번째로 간주하고 시작
    firstPass = false;
  }
}