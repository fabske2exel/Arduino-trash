#include <Servo.h>
#include <NewPing.h>
  
#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 2000

const int buttonPin = 2;
int buttonState = 0;
int led = 13;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo servo1;
Servo servo2;

void setup() { 
servo1.attach(10);
servo2.attach(9);
servo1.write(90);
servo2.write(90);
delay(500);
pinMode(buttonPin, INPUT);
pinMode(led, OUTPUT);
Serial.begin(9600);
} 
 
void loop() { 
  start:
  buttonState = digitalRead(buttonPin);
    
   delay(500);
   unsigned int uS = sonar.ping_cm();

if (uS < 60){
  servo1.write(180);
  servo2.write(0);
     Serial.print(uS);
   Serial.println("cm");
  digitalWrite(led, HIGH);
  }

else {
  servo1.write(90);
  servo2.write(90);
     Serial.print(uS);
   Serial.println("cm");
    digitalWrite(led, LOW);
}

if (buttonState == LOW) {
  servo1.write(180);
  servo2.write(0);
     Serial.print(uS);
   Serial.println("cm");
  delay(20000);
}

   Serial.print(uS);
   Serial.println("cm");
}
