#include  <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"     //Modül ile ilgili kütüphaneleri ekliyoruz
int mesaj[1];      //mesaj isminde bir dizi tanımlıyoruz
RF24 verici(9, 10);    //kütüphane tarafından kullanılacak pinleri tanımlıyoruz
const uint64_t kanal = 0xE8E8F0F0E1LL; //kanalı tanımlıyoruz



int smokeA0 = A0;
int sensorThres = 300; //  Duman sensörü eşik değeri

void setup() {
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
  verici.begin();       //nrf yi başlatıyoruz
  verici.openWritingPipe(kanal);  //kanal id sı tanımlanıyor
}
void loop() {
  int analogSensor = analogRead(smokeA0); // Analog değeri değişkene atıyoruz.
  // Analog değer belirlediğimiz eşik değerini geçerse 1 mesajını yolluyor.
  if (analogSensor > sensorThres)
  {
    mesaj[0] = 123;
    verici.write(mesaj, 1);   //mesaj değişkeni yollanıyor
  }

  delay(100);
}
