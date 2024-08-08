#include <Stepper.h>

const int STEPS_PER_REV = 200;  // 1.8' 모터가 360도가 되기 위해 필요한 스텝 수
const int SPEED_CONTROL = A0;

// 생성자 
// 360'를 회전하기 위해 필요한 스텝 수, A핀 번호, B핀 번호, /A핀 번호, /B핀 번호
Stepper stepper_NEMA17(STEPS_PER_REV, 8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorReading = analogRead(SPEED_CONTROL);

  int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
  Serial.println(motorSpeed);
  if(motorSpeed > 0) {
    stepper_NEMA17.setSpeed(motorSpeed);  // rpm : 1분 당 회전 수 설정
    stepper_NEMA17.step(STEPS_PER_REV / 100); // 출력할 스탭 수, -면 반대 방향으로 회전
  }
}
