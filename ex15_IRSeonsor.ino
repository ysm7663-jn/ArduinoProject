#include <IRremote.h>   // IRremote.h 라이브러리 활용 
#include <Servo.h>      // Servo.h 라이브러리 활용

// LCD 선언
//#define LED1 7
//#define LED2 6

// 적외선 센서 선언
IRrecv irrecv(9);       // 적외선 센서 핀 D9에 연결
decode_results results; // 적외선 수신번호를 저장

// 16738455, 0 / 16724175, 1 / 16718055, 2 / 16743045, 3 / 16716015, 4 / 16726215, 5
// 16734885, 6 / 16728765, 7 / 16730805, 8 / 16732845, 9 / 16750695, 100+  / 16756815, 200+ 
// 16769055, - / 16754775, + / 16748655, EQ / 16720605, << / 16712445, >>
// 16761405 <> / 16753245, ch- / 16736925, ch / 16769565, ch+

// 서브모터 선언
Servo servo;    // 서브모터 객체
int value = 0;

void setup() {
  Serial.begin(9600);   
  //pinMode(LED1, OUTPUT);
  //pinMode(LED2, OUTPUT);
  servo.attach(7);
  irrecv.enableIRIn();  // 적외선 센서 활성화
}

void loop() {
  if(irrecv.decode(&results)){  // 적외선 신호를 받았다면
    Serial.println(results.value); // 적외선 신호값 출력

    // 버튼을 통한 LCD 활용
    /*
    if(results.value == 16738455){  // 0
      digitalWrite(LED1, HIGH);
    } 

    if(results.value == 16724175){  // 1
      digitalWrite(LED2, HIGH);
    }
    */

    // 서브모터 작동 활용
    if(results.value == 16738455) { // 0
      value += 30;
    }

    if(results.value == 16724175) { // 1
      value += 60;
    }

    if(results.value == 16718055) { // 2
      value += 90;
    }

    if(results.value == 16743045) { // 3
      value += 90;
    }

    if(results.value == 16716015) { // 4
      value += 180;
    }

    if(results.value == 16726215) { // 5
      value = 0;
    }
    
    Serial.print("value :: ");
    Serial.println(value);

    servo.write(value);

    irrecv.resume();  // 계속해서 다음 신호 받기

  }
}
