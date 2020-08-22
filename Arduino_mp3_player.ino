#include <SD.h>                  
#define SD_ChipSelectPin 4  
#include <TMRpcm.h>       
#include <SPI.h>
TMRpcm tmrpcm;   
 int SW1; 
 int SW2;
 int SW3;
 int SW4;
void setup(){
 pinMode(14,INPUT); 
 pinMode(15,INPUT);  
 pinMode(16,INPUT);  
 pinMode(17,INPUT);  
 
  tmrpcm.speakerPin = 9; 
 
  if (!SD.begin(SD_ChipSelectPin)) { 
  return;   
  }
 tmrpcm.volume(1);
 tmrpcm.play("1.wav"); 
}
 
void loop(){  
 SW1=digitalRead(14); 
 SW2=digitalRead(15);
 SW3=digitalRead(16);
 SW4=digitalRead(17);
  
     if (SW1 == LOW) { 
      tmrpcm.play("6.wav");
    } else if(SW2 == LOW){ 
      tmrpcm.play("4.wav");
    } else if(SW3 == LOW){ 
      tmrpcm.play("5.wav");
    } else if(SW4 == LOW){  
      tmrpcm.play("3.wav");
    }
  
}
