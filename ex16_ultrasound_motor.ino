#include <Servo.h>      // Servo.h 라이브러리 활용

#define trig 10
#define echo 9
#define led 7

// 서브모터 선언
Servo servo;    // 서브모터 객체
int value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  servo.attach(13);
}

void loop() {
  
  digitalWrite(trig, HIGH);   // 초음파 ON
  delayMicroseconds(10);      // 10 micro초 대기
  digitalWrite(trig, LOW);    // 초음파 OFF

  int duration = pulseIn(echo, HIGH);
  int dis = duration / 29 / 2;

  if(dis < 10) {
    digitalWrite(led, HIGH);
    value += 180;
  } else if (dis > 15) {
    digitalWrite(led, LOW);
    value = 0;
  }

  servo.write(value);

}
