// 주황 : 데이터 핀 
// 빨강 : VCC
// 갈색 : GND

#include <Servo.h>

#define touchSensor 2

Servo servo;

int value = 0;

void setup() {
  servo.attach(7);
  pinMode(touchSensor, INPUT);
  Serial.begin(9600);
}

// Serial.available 사용 시 No Line Ending 으로 설정해야 정상적인 테스트 가능

void loop() {
    // 터치가 됐을 경우 모터 회전
    int touchYn = digitalRead(touchSensor);
    Serial.println(touchYn);
    delay(1000);
    if(touchYn == 1){
      value += 30;
      servo.write(value);
    } 
/*
  if(Serial.available()) {
    char in_data;
    in_data = Serial.read();
    if(in_data == '1'){
      value += 30;
      if(value == 210){
        value = 0;
      }
    } else {
      value = 0;
    }
    servo.write(value);
  }
  */
}
