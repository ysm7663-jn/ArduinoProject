#define clkPin 2
#define dtPin 3
#define swPin 4

int encoderVal = 0;
int currentStateCLK;
int previousStateCLK;

String encdir = "";

void setup() {
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  //pinMode(swPin, INPUT);
  //digitalWrite(swPin, HIGH);
  Serial.begin(9600);

  previousStateCLK = digitalRead(clkPin);
}

void loop() {
  currentStateCLK = digitalRead(clkPin);

  if(currentStateCLK != previousStateCLK) {
    if(digitalRead(dtPin) != currentStateCLK) {
      encoderVal--;
      encdir = "CCW";
    } else {
      encoderVal++;
      encdir = "CW";
    }
    Serial.print("Direction : ");
    Serial.print(encdir);
    Serial.print(" -- Value : ");
    Serial.println(encoderVal);
  }
  previousStateCLK = currentStateCLK;
}
