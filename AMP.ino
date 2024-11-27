// 앰프 감지 설정
const int sensorPin = 2;           // 감지 센서가 연결된 핀
volatile bool isDetected = false;   // 감지 상태를 나타내는 변수
volatile int count = 0;             // 감지 횟수를 저장하는 변수
unsigned long lastDetectionTime = 0; // 마지막 감지 시간을 저장
const unsigned long lockoutDelay = 500; // 감지 후 추가 감지를 막는 시간 (500ms)

void setup() {

  // 감지 센서 설정
  Serial.begin(9600);
  // sensor 감지 설정
  pinMode(sensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPin), countDetection, FALLING);
}

void loop() {
  // loop는 비워 둡니다.
}

// 감지 시 카운트 증가
void countDetection() {
  unsigned long currentTime = millis();

  // lockoutDelay 시간 이후에만 감지 처리
  if (currentTime - lastDetectionTime > lockoutDelay) { 
    isDetected = true; // 감지 상태로 설정
    lastDetectionTime = currentTime;
    count++;  // 감지 시 카운트 증가
    Serial.print("감지 횟수: ");
    Serial.println(count);
    delay(500);
  }
}
