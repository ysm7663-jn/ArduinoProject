int sw = 10;

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  pinMode(sw, INPUT_PULLUP);
}

void loop() {

  if(digitalRead(sw) == LOW) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }

  /*
  if(Serial.available()) {
    String sig = Serial.readStringUntil('\n');
    Serial.println(sig);
    if(sig == "2") {
      digitalWrite(8, LOW);
    } else {
      digitalWrite(8, HIGH);
    }
  }
  */

}
