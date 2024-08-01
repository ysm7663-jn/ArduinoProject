/*
#include <AccelStepper.h>               // 스텝모터 라이브러리 불러옴

AccelStepper accelStepper(2048, 11, 9, 10, 8);   // 스텝모터 객체 선언(INT4, INT2, INT3, INT1) 순

int in1 = 7;
int in2 = 6;
int in3 = 5;
int in4 = 4;

void setup() {
  accelStepper.setMaxSpeed(1000);                 // rpm : 1분당 도는 횟수, 너무 큰값을 하면 안 돌아감 (아두이노 기준 max 15~16)
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()) {
    char in_data;
    in_data = Serial.read();

    if(in_data == '1') {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      accelStepper.move(200);                // steps, 2048로 두면 정회전 한바퀴
      accelStepper.run();
      delay(1000);
    } else if(in_data == '2') {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      accelStepper.move(200);                // steps, 2048로 두면 정회전 한바퀴
      accelStepper.run();
      delay(1000);
    } else if(in_data == '3') {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      accelStepper.move(-200);                // -steps, -2048로 두면 역회전 한바퀴
      accelStepper.run();
      delay(1000);
    } else if(in_data == '4') {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      accelStepper.move(-200);                // -steps, -2048로 두면 역회전 한바퀴
      accelStepper.run();
      delay(1000);
    } else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
  }

}
*/

#include <AccelStepper.h>

// ULN2003 드라이버 보드의 핀 번호
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

// AccelStepper 인스턴스 생성
// 4핀 방식을 사용하여 스텝 모터 제어
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

void setup() {
  // 모터 최대 속도 설정
  stepper.setMaxSpeed(2000);
  // 가속도 설정
  stepper.setAcceleration(1000);
}

void loop() {
  // 현재 위치에서 상대적으로 2048 스텝 앞으로 이동 (한 바퀴)
  stepper.move(2048);
  // 이동 시작
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  delay(1000); // 1초 대기

  // 현재 위치에서 상대적으로 2048 스텝 뒤로 이동 (한 바퀴)
  stepper.move(-2048);
  // 이동 시작
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  delay(1000); // 1초 대기
}
