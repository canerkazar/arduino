#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
const int IN1 = 2;    //Right Motor (-)
const int IN2 = 3;    //Right Motor (+)
const int IN3 = 4;    //Left Motor (+)
const int IN4 = 5;
int data[2];
void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}
void loop()
{
  if (radio.available()) {
    bool done = false;
    while (!done) {
      done = radio.read(data, sizeof(data));
      if (data[1] > 160) {
        //left
        digitalWrite(IN1, LOW);
        digitalWrite(IN3, LOW);
      }
      if (data[1] < 60) {
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
      }
      if (data[0] > 330 && data[0] < 400) {
        //forward
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      }

      if (data[0] < 270) {
        //backward
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      }
      if (data[0] > 270 && data[0] < 330 && data[1] > 80 && data[1] < 160) {
        //stop car
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH);
      }
    }
  }
}
