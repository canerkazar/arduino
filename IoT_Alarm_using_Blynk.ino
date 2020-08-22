#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
char auth[] = "wCWhMIlVyNvlC5IwaIN4rM8pJSu7w7LW";

char ssid[] = "***********"; // wifi adin
char pass[] = "***********"; // wifi sifresi

#define led 15 // D8
#define led1 3 // RX
#define led2 1 // TX
#define buzzer 14 // D5
#define buzzer1 12 // D6
#define buzzer2 13 // D7
#define pirPin 5  // NODEMCU D1 pini
#define pirPin1 4  // NODEMCU D2 pini
#define pirPin2 0  // NODEMCU D3 pini
int pirValue;
int pirValue1;
int pirValue2;
int pinValue;
int pinValue1;
int pinValue2;

BLYNK_WRITE(V0)
{
  pinValue = param.asInt();
}
BLYNK_WRITE(V1)
{
  pinValue1 = param.asInt();
}
BLYNK_WRITE(V2)
{
  pinValue2 = param.asInt();
}
BlynkTimer timer;

void sendSensor() // Timer fonsiyonu, belirlenen zaman araliklariyla sensor verilerini kontrol ediyor
{
  
  if (pinValue == HIGH)
  {
    pirValue = digitalRead(pirPin);
    if (pirValue == HIGH)
    {
      Serial.println("Hareket Algilandi - 1");
      Blynk.notify("Hareket Algilandi - 1");
      tone(buzzer, 1000);
      digitalWrite(led, HIGH);
    }
    else if (pirValue == LOW)
    {
      noTone(buzzer);
      digitalWrite(led, LOW);
    }
  }
  else if (pinValue == LOW)
  {
    noTone(buzzer);
    digitalWrite(led, LOW);
  }
// --------------------------------------------
   if (pinValue1 == HIGH)
  {
    pirValue1 = digitalRead(pirPin1);
    if (pirValue1 == HIGH)
    {
      Serial.println("Hareket Algilandi - 2");
      Blynk.notify("Hareket Algilandi - 2");
      tone(buzzer1, 1000);
      digitalWrite(led1, HIGH);
    }
    else if (pirValue1 == LOW)
    {
      noTone(buzzer1);
      digitalWrite(led1, LOW);
    }
  }
  else if (pinValue1 == LOW)
  {
    noTone(buzzer1);
    digitalWrite(led1, LOW);
  }
// --------------------------------------------
   if (pinValue2 == HIGH)
  {
    pirValue2 = digitalRead(pirPin2);
    if (pirValue2 == HIGH)
    {
      Serial.println("Hareket Algilandi - 3");
      Blynk.notify("Hareket Algilandi - 3");
      tone(buzzer2, 1000);
      digitalWrite(led2, HIGH);
    }
    else if (pirValue2 == LOW)
    {
      noTone(buzzer2);
      digitalWrite(led2, LOW);
    }
  }
  else if (pinValue2 == LOW)
  {
    noTone(buzzer2);
    digitalWrite(led2, LOW);
  }

}

void setup()
{
  pinMode(pirPin, INPUT);
  pinMode(pirPin1, INPUT);
  pinMode(pirPin2, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  digitalWrite(buzzer, LOW);
  digitalWrite(buzzer1, LOW);
  digitalWrite(buzzer2, LOW);

  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(115200);
  delay(10);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);

}

void loop()
{

  Blynk.run();
  timer.run();
}
