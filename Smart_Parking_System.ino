#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Ultrasonic.h>
Ultrasonic ultrasonic(A0, A1);
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 5 //define green LED pin
#define LED_R 4 //define red LED
#define BUZZER 2 //buzzer pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name


void setup()
{

  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(6); //servo pin
  myServo.write(80); //servo start position
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop()
{
  long int door_sensor = ultrasonic.Ranging(CM);
  int i;
  if (door_sensor > 10)
  {
    delay(3000);

    myServo.write(80);
    delay(15);

  }



  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "10 F9 F8 65") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
    digitalWrite(LED_G, LOW);
    for (int i = 80; i <= 170; i++)
    {
      myServo.write(i);
      delay(15);

    }
    delay(3000);
    for (int i = 170; i >= 80; i--)
    {
      Serial.print("2 ");
      Serial.println(door_sensor);
      myServo.write(i);
      if (door_sensor < 10)
      {
        Serial.print("3 ");
        Serial.println(door_sensor);
        myServo.write(170);
        delay(15);

      }
      delay(15);
    }



  }
  else
  {
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_R, LOW
    );
    noTone(BUZZER);

  }



}



