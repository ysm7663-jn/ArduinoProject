#include <AccelStepper.h>

#define CLK 2
#define DT 3
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

int count;              // 회전 카운터 측정
int currentStateCLK;    // CLK의 현재 신호상태 저장
int lastStateCLK;       // 직전 CLK의 신호상태 저장
String currentDir = ""; // 현재 회전 방향 출력

void setup() {
  Serial.begin(9600);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  lastStateCLK = digitalRead(CLK);

  stepper.setMaxSpeed(2000);      // 모터 최대 속도 설정
  stepper.setAcceleration(1000);  // 가속도 설정
}

void loop() {

  currentStateCLK = digitalRead(CLK);

  if(currentStateCLK != lastStateCLK && currentStateCLK == 1) {
    if(digitalRead(DT) != currentStateCLK){
      count++;
      currentDir = "시계방향 회전";
      stepper.move(4096);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }
    } else {
      count--;
      currentDir = "반시계 방향 회전";
      stepper.move(-4096);
      while (stepper.distanceToGo() != 0) {
        stepper.run();
      }
    }
    Serial.print("회전방향: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(count);
  }

  lastStateCLK = currentStateCLK;

  delay(1);

}
