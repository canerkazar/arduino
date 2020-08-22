
#include "ACS712.h"


ACS712 sensor(ACS712_30A, A0);
#include <SPI.h>
//Connect pins 1-5 of nokia 5110 LCD to pins 3-7 on your arduino
//So RST would be arduino pin 3,CE would go to pin 4 and so on


#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display=Adafruit_PCD8544(7,6,5,4,3);
//---------------------------



//---------------------------




void setup() {
  Serial.begin(9600);
  display.begin();
}

void loop() {
  float U = 230;
  float I = sensor.getCurrentAC();
  float P = U * I;
  int x,y;
  x = analogRead(A5);
  x = map(x, 0, 1023, 0, 3200);
  y = analogRead(A6);
  y = map(y, 0, 1023, 0,1000);
  display.clearDisplay();
  display.drawFastVLine(32, 0, 39, BLACK);
  display.setCursor(0, 0);
  display.println("OCAK ");
  display.setCursor(35, 0);
  display.print(Ctemp);
  display.println(" C");
  display.drawFastHLine(0, 8, 83, BLACK);
  display.setCursor(0, 10);
  display.print("SINIR ");
  display.setCursor(35, 10);
  display.print(y);
  display.println(" C");
  display.drawFastHLine(0, 18, 83, BLACK);
  display.setCursor(0, 20);
  display.print("GUC");
  display.setCursor(35, 20);
  display.print(x);
  display.drawFastHLine(0, 28, 83, BLACK);
  display.setCursor(0, 30);
  display.print("SINIR");
  display.setCursor(35, 30);
  display.print(amperage);
  display.drawFastHLine(0, 38, 83, BLACK);
  display.display();
  if (P > x )
  {
    digitalWrite(13, HIGH);
    tone(12, 1000);
    delay(100000);
  }
  else {
    digitalWrite(13, LOW);
    noTone(12);
  }
  delay(200);
}













