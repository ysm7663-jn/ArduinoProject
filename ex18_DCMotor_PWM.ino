// 9V 배터리는 모터드라이브에 연결
// 보드에 직접 할 경우 보드의 전압 안정성에 의해 전압 변동이 생길 수 있어 정상적으로 반영이 안 됨

// DC 모터(Direct Current, 직류)는 +, - 상관없이 걸어놔도 상관없음

int in1 = 7;
int in2 = 5;
int led = 11;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // pinMode(led, OUTPUT); led에 대한 핀모드는 설정하지 않음
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
    int resistance = analogRead(A0);
    analogWrite(led, resistance/4);
    int motor = map(resistance, 0, 1023, 0, 255);
    analogWrite(in2, motor);
    Serial.println(resistance);
}
