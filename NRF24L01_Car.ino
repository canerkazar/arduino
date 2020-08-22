
#include <SPI.h>      //SPI library for communicate with the nRF24L01+
#include "RF24.h"     //The main library of the nRF24L01+


const int IN1 = 8;    //Right Motor (-)
const int IN2 = 5;    //Right Motor (+)
const int IN3 = 6;    //Left Motor (+)
const int IN4 = 7;    //Right Motor (-)

//Define variable for the motors speeds

//Define packet for the direction (X axis and Y axis)
int data[2];

//Define object from RF24 library - 9 and 10 are a digital pin numbers to which signals CE and CSN are connected
RF24 radio(9, 10);

//Create a pipe addresses for the communicate
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
  //Define the motor pins as OUTPUT

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  radio.begin();                    //Start the nRF24 communicate
  radio.openReadingPipe(1, pipe);   //Sets the address of the transmitter to which the program will receive data.
  radio.startListening();
}

void loop(void) {
  if (radio.available())
  {
    bool done = false;
    while (!done)
    {
      radio.read(data, sizeof(data));

      if (data[0] > 380) {
        //forward

        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      }

      else   if (data[0] < 310) {
        //backward

        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      }

      else if (data[1] > 180) {
        //left

        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      }

      else   if (data[1] < 110) {

        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      }

      if (data[0] > 330 && data[0] < 360 && data[1] > 130 && data[1] < 160) {
        //stop car
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
      }
      delay(10);
    }
  }
}
