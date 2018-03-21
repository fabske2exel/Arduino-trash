/*
 * smart trash by Fabian Exel (mailto: fabian.exel@gmx.de)
 * Final version - 1.10
 * 
 * Includes:
 * automatical door opener
 * level led
 * level piezo
 * serial communication
 */

#include <NewPing.h>
  
#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define ECHO 8
#define TRIGGER 7
#define MAX_DISTANCE 1000

#define piezoPin 13                                                             // Piezo-Element an Pin 13
#define toneDuration 500                                                        // Ton-Dauer
#define tonePause 550                                                           // Pausenlänge zwischen den Tönen
#define pause 500
int tones[] = {523, 659, 587, 698, 659, 784, 698, 880, tonePause, tonePause, 555, 666, 777, 888, tonePause, tonePause, 543, 654, 765, 876,
               523, 659, 587, 698, 659, 784, 698, 880, tonePause, tonePause, 555, 666, 777, 888, tonePause, tonePause, 543, 654, 765, 876,
              };
int elements = sizeof(tones) / sizeof(tones[0]);

const int buttonPin = 6;    // Pin button
const int motor1Pin = 5;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 4;    // H-bridge leg 2 (pin 7, 2A)
const int enablePin = 9;    // H-bridge enable pin
int buttonState = 0;
int button = 0;
int lenght = 60;
int fuel = 4;     //
int att = 10;     // PinLED
int drive = 1000;
int piezo = 13;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing stand(TRIGGER, ECHO, MAX_DISTANCE / 5);

void setup() {
pinMode(piezo, OUTPUT);
pinMode(buttonPin, INPUT);
pinMode(LED_BUILTIN, OUTPUT);
pinMode(att, OUTPUT);
digitalWrite(att, LOW);
Serial.begin(9600);
pinMode(motor1Pin, OUTPUT);
pinMode(motor2Pin, OUTPUT);
pinMode(enablePin, OUTPUT);       // set enablePin high so that motor can turn on:
digitalWrite(enablePin, HIGH);
digitalWrite(buttonPin, HIGH);
digitalWrite(LED_BUILTIN, HIGH);
delay(500);
digitalWrite(LED_BUILTIN, LOW);
Serial.print("Start");
} 
 
void loop() { 
   buttonState = digitalRead(buttonPin);  
   delay(250);
   unsigned int uS = sonar.ping_cm();

if (uS < 3 || uS > 1900){
  Serial.println("");
  Serial.print("Keine Messergebnisse");
  uS = lenght + 1;
  delay(drive);  
}

if (buttonState == LOW) {
    Serial.println("");  
    Serial.print("button pressed to open");
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
    digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
    delay(drive);
    digitalWrite(motor2Pin, LOW);
    delay(drive);
delay(60000);
    digitalWrite(motor1Pin, HIGH);
    digitalWrite(motor2Pin, LOW);
    delay(drive);
    digitalWrite(motor1Pin, LOW);
    delay(drive);
    digitalWrite(LED_BUILTIN, LOW);
    }
else{

if (uS < lenght){
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
  digitalWrite(motor2Pin, HIGH);  // set leg 2 of the H-bridge high
  delay(drive);
  digitalWrite(motor2Pin, LOW);
  delay(drive);
  digitalWrite(motor1Pin, HIGH);
  digitalWrite(motor2Pin, LOW);
  delay(drive);
  digitalWrite(motor1Pin, LOW);
  delay(drive);
  digitalWrite(LED_BUILTIN, LOW);
  }
else {
    digitalWrite(LED_BUILTIN, LOW);
}
  Serial.println("");
   Serial.print(uS);
   Serial.println("cm Abstand");
  delay(250);
   unsigned int Su = sonar.ping_cm();
   if (Su < 3 || Su > 100){
    Serial.print("");
    Serial.print("Keine fuellstands Ergebnisse");
    Su = lenght + 1;
    delay(drive);
   }
   if (Su < fuel){
    digitalWrite(att, HIGH);
    Serial.println("");
    Serial.println("voll");
      for (int i = 0; i < elements; i++) {
    tone(piezoPin, tones[i], toneDuration);                                     // Ton spielen
    delay(tonePause);                                                           // Pause zwischen den Tönen
    Serial.println("play music!");
  }
   }
  digitalWrite(LED_BUILTIN, LOW);
   Serial.println("");   
   Serial.print(Su);
   Serial.print("cm fuellhoehe");
}}
