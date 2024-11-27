// Include the Arduino Stepper Library
#include <Stepper.h>
 
// Define Constants
 
// Number of steps per output rotation
const int STEPS_PER_REV = 200;

// The pins used are 1,2,3,4 
// Connected to L298N Motor Driver In1, In2, In3, In4 
// Pins entered in sequence 1-2-3-4 for proper step sequencing
 
Stepper stepper_NEMA17(STEPS_PER_REV, 8, 9, 10, 11);
 
void setup() {
  //int motorSpeed = map(60, 0, 1023, 0, 100);
  stepper_NEMA17.setSpeed(60);
  Serial.begin(9600);
}
 
void loop() {
    // step 1/100 of a revolution:
    Serial.println("clockwise");
    stepper_NEMA17.step(STEPS_PER_REV);
    delay(500);
  
    Serial.println("counterClockwise");
    stepper_NEMA17.step(-STEPS_PER_REV);
    delay(500);
}