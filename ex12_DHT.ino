#include <DHT11.h>

DHT11 dht(A0);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float temp, humi;

  int result = dht.read(humi, temp);

  if(result == 0){
    Serial.print("temperature : ");
    Serial.print(temp);
    Serial.print(" / humidity : ");
    Serial.print(humi);
    Serial.println();
  } else {
    Serial.println();
    Serial.print("Error No ");
    Serial.print(result);
    Serial.println();
  }

  delay(DHT11_RETRY_DELAY);

}
