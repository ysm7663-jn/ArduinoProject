// 뒤집었을 때 핀이 상단에 위치
// 핀
// GND / OUT / VCC

// 드라이버 영역 (시계방향 최소)
// 왼쪽 : 감지 범위 설정(최대 7m)
// 오른쪽 : 딜레이 시간 설정(0.3s ~ 5m)

#define sensor 3
#define LED 7

void setup() {
  pinMode(sensor, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(sensor);
  if(sensorValue == 1){
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  Serial.println(sensorValue);
  delay(100);

}
