#include <TinyGPS.h>
#include <SoftwareSerial.h>
SoftwareSerial Gsm(5, 6);
char phone_no[] = "***************"; //replace with phone no. to get sms
 
TinyGPS gps;  //Creates a new instance of the TinyGPS object
 
void setup()
{
  Serial.begin(9600);
  Gsm.begin(9600);  
 
}
 
void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
 
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      Serial.print(c);
      if (gps.encode(c)) 
        newData = true;  
    }
  }
 
  if (newData)      //If newData is true
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);   
    Gsm.print("AT+CMGF=1\r"); 
    delay(400);
    Gsm.print("AT+CMGS=\"");
    Gsm.print(phone_no);
    Gsm.println("\"");
    
    delay(300);
    Gsm.print("http://maps.google.com/maps?q=");
    
    //Gsm.print("Latitude = ");
    Gsm.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Gsm.print(",");
    Serial.print(",");
    Gsm.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    delay(200);
    Gsm.println((char)26); 
    delay(200);
    Gsm.println();
    delay(120000);
 
  }
 
  Serial.println(failed);
 
}
