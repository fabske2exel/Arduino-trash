#include <Servo.h>
#include <NewPing.h>
  
#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 2000

const int buttonPin = 2;
int buttonState = 0;
int led = 13;
int incomingByte;
int fuel = 12;
int sensor = A0;
int value = 0;
int full = 11;

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
  pinMode(full, OUTPUT);
  digitalWrite(full, LOW);
  pinMode(fuel, OUTPUT);
  digitalWrite(fuel, HIGH);
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
} 
  
void loop() { 
  start:
value = analogRead(sensor);
digitalWrite(full, LOW);

if (value > 50){
  Serial.print("full");
  digitalWrite(full, HIGH);
}
  
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 'H') {
      Serial.print("High");
        servo1.write(180);
        servo2.write(0);
          if (Serial.available() > 0) {
            incomingByte = Serial.read();
            if (incomingByte == 'L') {
               Serial.print("Low");
               servo1.write(90);
               servo2.write(90);
    }}}
    if (incomingByte == 'L') {
      Serial.print("Low");
        servo1.write(90);
        servo2.write(90);
          if (Serial.available() > 0) {
            incomingByte = Serial.read();
            if (incomingByte == 'H') {
               Serial.print("High");
               servo1.write(180);
               servo2.write(0);
    }}}
  }  
  
buttonState = digitalRead(buttonPin);
 delay(500);
   unsigned int uS = sonar.ping_cm();
   
if (buttonState == LOW) {
  uS = 50;
}

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
  delay(100);
}
