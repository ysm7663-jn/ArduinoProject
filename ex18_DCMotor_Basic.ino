// 9V 배터리는 모터드라이브에 연결
// 보드에 직접 할 경우 보드의 전압 안정성에 의해 전압 변동이 생길 수 있어 정상적으로 반영이 안 됨

// DC 모터(Direct Current, 직류)는 +, - 상관없이 걸어놔도 상관없음

int in1 = 7;
int in2 = 5;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
    char in_data;
    in_data = Serial.read();
    if(in_data == '1') {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    } else if (in_data == '2') {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    } else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    }
}
