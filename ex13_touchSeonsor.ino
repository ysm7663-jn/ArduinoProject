#define TouchSensor 2 

int led = 8;

void setup() {
  Serial.begin(9600);
  pinMode(TouchSensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int touchCnt = digitalRead(TouchSensor);

  if(touchCnt == 1){
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

}
