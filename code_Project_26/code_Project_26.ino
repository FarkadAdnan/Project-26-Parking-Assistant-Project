/*
 By:Farkad Adnan
 E-mail: farkad.hpfa95@gmail.com
 inst : farkadadnan
 #farkadadnan , #farkad_adnan , فرقد عدنان#
 FaceBook: كتاب عالم الاردوينو
 inst : arduinobook
 #كتاب_عالم_الاردوينو  #كتاب_عالم_الآردوينو 
 */
#include <NewPing.h> 
#include <EEPROM.h> 

const int G1 = 9;
const int G2 = 8;
const int G3 = 7;
const int G4 = 6;
const int G5 = 5;
const int G6 = 4;
const int G7 = 3;
const int G8 = 2;
const int R1 = 13;
const int R2 = 12;
const int R3 = 11;
const int R4 = 10;
const int trigPin = A0;
const int echoPin = A1;
const int buttonPin = A2; 
NewPing sonar(trigPin, echoPin, 300);

const int minDeviation = 5; 
const int timeout = 10; 
const int ledDistance = 6; 
const int calibrationDelay = 750;

int idealDistance = 5;
int rawSonar; 
int distance; 
int prevDistance = 0;
unsigned long lastMoved = 0; 


void setup() { 
  pinMode(G1, OUTPUT); 
  pinMode(G2, OUTPUT);
  pinMode(G3, OUTPUT);
  pinMode(G4, OUTPUT);
  pinMode(G5, OUTPUT);
  pinMode(G6, OUTPUT);
  pinMode(G7, OUTPUT);
  pinMode(G8, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  if (EEPROM.read(0) != 255) {
    idealDistance = EEPROM.read(0);
  }
  Serial.begin(9600);
}
void loop() { 
  delay(100); 
  rawSonar = sonar.ping_median(5);
  if (rawSonar != 0) { 
    distance = rawSonar / US_ROUNDTRIP_IN; 
    distance -= idealDistance; 
  }
  else {
    setLEDs(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  }
  if (abs(distance - prevDistance) >= minDeviation) { 
    lastMoved = 0;
    prevDistance = distance;
    if (distance < ledDistance * 9 && distance >= ledDistance * 8) {
      setLEDs(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
    else if (distance < ledDistance * 8 && distance >= ledDistance * 7) { 
      setLEDs(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
    else if (distance < ledDistance * 7 && distance >= ledDistance * 6) { 
      setLEDs(1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
    else if (distance < ledDistance * 6 && distance >= ledDistance * 5) { 
      setLEDs(1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0);
    }
    else if (distance < ledDistance * 5 && distance >= ledDistance * 4) {
      setLEDs(1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
    }
    else if (distance < ledDistance * 4 && distance >= ledDistance * 3) {
      setLEDs(1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0);
    }
    else if (distance < ledDistance * 3 && distance >= ledDistance * 2) { 
      setLEDs(1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0);
    }
    else if (distance < ledDistance * 2 && distance >= ledDistance) { 
      setLEDs(1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0);
    }
    else if (distance <= idealDistance) { 
      setLEDs(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1);
    }
  }
  else { 
    if (lastMoved == 0) {
      lastMoved = millis(); //set the timer
    }

    if (lastMoved != 0 && millis() - lastMoved >= timeout * 1000) { 
      setLEDs(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); 
      lastMoved = 0; 
    }
  }
  if (digitalRead(buttonPin) == LOW) { 
    calibrationCountdown(); 
    rawSonar = sonar.ping_median(30);
    if (rawSonar != 0) { 
      distance = rawSonar / US_ROUNDTRIP_IN;
      EEPROM.write(0, distance);
      idealDistance = distance; 
      flashGreen(); 
    }
    else { 
      flashRed();
    }
  }
}


void calibrationCountdown() {
  setLEDs(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); 
  //turn off all the leds
  setLEDs(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  //turn on the first led
  delay(calibrationDelay); //pause for a bit
  setLEDs(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); 
  //continue the pattern...
  delay(calibrationDelay);
  setLEDs(1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); 
  //continue the pattern...
  delay(calibrationDelay);
  setLEDs(1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0); 
  delay(calibrationDelay);
  setLEDs(1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
  delay(calibrationDelay);
  setLEDs(1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0);
  delay(calibrationDelay);
  setLEDs(1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0);
  delay(calibrationDelay);
  setLEDs(1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0);
  delay(calibrationDelay);
}


void flashGreen() {
  setLEDs(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); 
  setLEDs(1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0); 
  delay(500); 
  setLEDs(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  delay(500);
  setLEDs(1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0);
  delay(500);
  setLEDs(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); 
}

void flashRed() {
  setLEDs(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); 
  setLEDs(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1); 
  delay(500);
  setLEDs(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); 
  delay(500);
  setLEDs(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1); 
  delay(500); //wait
  setLEDs(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
void setLEDs(int led1, int led2, int led3, int led4, int led5, int led6, int led7, int led8, int led9, int led10, int led11, int led12) {
  digitalWrite(G1, led1);
  digitalWrite(G2, led2);
  digitalWrite(G3, led3);
  digitalWrite(G4, led4);
  digitalWrite(G5, led5);
  digitalWrite(G6, led6);
  digitalWrite(G7, led7);
  digitalWrite(G8, led8);
  digitalWrite(R1, led9);
  digitalWrite(R2, led10);
  digitalWrite(R3, led11);
  digitalWrite(R4, led12);
}
