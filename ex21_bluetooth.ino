#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11);  // 10: 수신, 11: 송신

void setup() {
    BT.begin(9600);
    pinMode(12, OUTPUT);
    analogWrite(9, 0);
}

void loop() {
  if(BT.available()) {
      int value = BT.read();
      if(value == 'a') {
        digitalWrite(12, HIGH);
      }

      if(value == 'b') {
        digitalWrite(12, LOW);
      }
  }
}