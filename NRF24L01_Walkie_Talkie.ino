
#include <RF24.h>
#include <SPI.h>
#include <RF24Audio.h>
#include "printf.h"
#include <MusicPlayer.h>

RF24 radio(8,7);   
RF24Audio rfAudio(radio,0); 
const uint8_t callDetector = 3;

MusicPlayer myPlayer = MusicPlayer(melodyPin);
int PwrRngrs[] = { E7,E7,D7,E7,G7,E7 };
unsigned int duration[] = { E, E, S, E, E, E  };
int melodyPin = 5;
const uint8_t melodyLength = 6;
unsigned long notify = 500;


void setup() {      
  Serial.begin(115200);
  
  printf_begin();
  radio.begin();
  radio.printDetails();
  rfAudio.begin();

  pinMode(callDetector, INPUT);

  rfAudio.receive();
}


void loop()
{
  unsigned long strt = 0;
  unsigned long fin = 0;

 
  while(!digitalRead(callDetector));
  strt = millis();
  while(digitalRead(callDetector));
  fin = millis();
  if ((fin - strt) < notify) myPlayer.playMelody(PwrRngrs, duration, melodyLength);

}
