#include <SoftwareSerial.h>
SoftwareSerial BT(0, 1);


int motorlc = 10; // left motor clockwise rotation
int motorla = 11; // left motor anticlockwise rotation
int motorrc = 12; // right motor clockwise rotation
int motorra = 13; // right motor anticlockwise rotatio
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#define REDPIN  3
#define GREENPIN 2
#define BLUEPIN 9
int red_f = 0, green_f = 0, blue_f = 0;
String readString;

void setup() {     // presenting pins as outputs

  pinMode(motorlc, OUTPUT);
  pinMode(motorla, OUTPUT);
  pinMode(motorrc, OUTPUT);
  pinMode(motorra, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  Serial.begin(9600);
  BT.begin(9600);
}
void loop() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  red_f = pulseIn(sensorOut, LOW);
  red_f = map(red_f, 0, 350, 0, 255);
  if (red_f <= 50 && green_f >= 125 && green_f <= 140 && blue_f <= 125 && blue_f >= 115)
  {
    digitalWrite(REDPIN, 0);
    digitalWrite(BLUEPIN, 1);
    digitalWrite(GREENPIN, 1);
  }
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  green_f = pulseIn(sensorOut, LOW);
  green_f = map(green_f, 0, 350, 0, 255);
  if (green_f >= 65 && green_f <= 85 && red_f >= 120 && red_f <= 145 && blue_f >= 50)
  {
    digitalWrite(GREENPIN, 0);
    digitalWrite(BLUEPIN, 1);
    digitalWrite(REDPIN, 1);
  }

  // Printing the value on the serial monito
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  blue_f = pulseIn(sensorOut, LOW);
  blue_f = map(blue_f, 0, 350, 0, 255);

  if (blue_f <= 55 && red_f >= 135 && red_f <= 180 && green_f >= 115 && green_f <= 130)
  {
    digitalWrite(BLUEPIN, 0);
    digitalWrite(GREENPIN, 1);
    digitalWrite(REDPIN, 1);
  }
  while (BT.available()) { // the code here is for bluetooth
    delay(3);
    char c = BT.read();
    readString += c;
  }
  if (readString.length() > 0) { // when a certain button is pressed the reaction will be...
    Serial.println(readString);
    if (readString == "Right") {

      digitalWrite(motorlc, HIGH);
      digitalWrite(motorla, LOW);
      digitalWrite(motorrc, HIGH);
      digitalWrite(motorra, LOW);
    }
    if (readString == "Left") {

      digitalWrite(motorlc, LOW);
      digitalWrite(motorla, HIGH);
      digitalWrite(motorrc, LOW);
      digitalWrite(motorra, HIGH);
    }
    if (readString == "Back") {

      digitalWrite(motorlc, HIGH);
      digitalWrite(motorla, LOW);
      digitalWrite(motorrc, LOW);
      digitalWrite(motorra, HIGH);
    }
    if (readString == "Forward") {

      digitalWrite(motorlc, LOW);
      digitalWrite(motorla, HIGH);
      digitalWrite(motorrc, HIGH);
      digitalWrite(motorra, LOW);
    }
    if (readString == "Stop") {

      digitalWrite(motorlc, LOW);
      digitalWrite(motorla, LOW);
      digitalWrite(motorrc, LOW);
      digitalWrite(motorra, LOW);

    }


  }
  readString = "";
}
