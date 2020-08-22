
//motorların tanımları

int Sol_Motor1 = 6;
int Sol_Motor2 = 9;
int Sag_Motor1 = 5;
int Sag_Motor2 = 10;


#include <Ultrasonic.h>

Ultrasonic ultrasonic_arka(13, 12), ultrasonic_sol_arka(2, 3), ultrasonic_sol_on(8, 11), ultrasonic_on(4, 7);
// ultrasomik sensörlerin tanımlamamalrı

#define Sol 0 //sol yön komutu
#define Sag 1 //sağ yön komutu
#define Ileri 2 //ileri yön komutu
#define Geri 3 //geri yön komutu
#define minimum_limit 17 //Arabanın genişliği (cm)
#define minimum_limit1 23 //arabanın uzunluğu (cm)

byte park_durumu = 0;

volatile int val;

int sayac = 0;
int guncel_durum = 0;
int onceki_durum = 0;
void say(int saydir)
{
  for (int i = 0 ; i <= saydir; i + 1)
  {
    val = digitalRead(sinyalpin);
    if (val == LOW) {

      guncel_durum = 0;
    }
    else {

      guncel_durum = 1;
    }

    if (guncel_durum != onceki_durum)
    {
      if (guncel_durum == 1)
      {
        sayac = sayac + 1;
        Serial.println(sayac);
        i = i + 1;
      }
      else
      {
        i = i ;
      }

      onceki_durum = guncel_durum;

    }
    if (i == saydir)
    {

      digitalWrite(Sol_Motor1, LOW);
      digitalWrite(Sol_Motor2, LOW);
      digitalWrite(Sag_Motor1, LOW);
      digitalWrite(Sag_Motor2, LOW);

    }

  }

}


void motor_pinSetup()
{

  digitalWrite(Sol_Motor1, LOW);
  digitalWrite(Sol_Motor2, LOW);
  digitalWrite(Sag_Motor1, LOW);
  digitalWrite(Sag_Motor2, LOW);

}

// Hareket fonksiyonları
void Robot_Hareket(byte motor)
{
  if (motor == Ileri)
  {
    analogWrite(Sol_Motor1, 100);
    digitalWrite(Sol_Motor2, LOW);
    analogWrite(Sag_Motor1, 100);
    digitalWrite(Sag_Motor2, LOW);



  }
  if (motor == Geri)
  {
    digitalWrite(Sol_Motor1, LOW);
    analogWrite(Sol_Motor2, 120);
    digitalWrite(Sag_Motor1, LOW);
    analogWrite(Sag_Motor2, 120);


  }
  if (motor == Sol)
  {
    digitalWrite(Sol_Motor1, LOW);
    analogWrite(Sol_Motor2, 150);
    analogWrite(Sag_Motor1, 150);
    digitalWrite(Sag_Motor2, LOW);


  }

  if (motor == Sag)
  {
    analogWrite(Sol_Motor1, 150);
    digitalWrite(Sol_Motor2, LOW);
    digitalWrite(Sag_Motor1, LOW);
    analogWrite(Sag_Motor2, 150);


  }

}

void Robot_Dur()
{
  digitalWrite(Sol_Motor1, LOW);
  digitalWrite(Sol_Motor2, LOW);
  digitalWrite(Sag_Motor1, LOW);
  digitalWrite(Sag_Motor2, LOW);

}

// Park yeri araması
bool Park_Yeri_Kontrol()
{

  long on_Sensor = ultrasonic_on.Ranging(CM);
  long sag_Sensor = ultrasonic_sol_on.Ranging(CM);
  long sag_arka_Sensor = ultrasonic_sol_arka.Ranging(CM);

  if ( (sag_Sensor <= minimum_limit) && (sag_arka_Sensor <= minimum_limit) && (park_durumu == 0))
  {
    Robot_Hareket(Ileri);
    park_durumu = 1; Serial.println(park_durumu);
  }

  if ((sag_Sensor > minimum_limit) && (sag_Sensor < minimum_limit1) && (sag_arka_Sensor > minimum_limit) && (sag_arka_Sensor < minimum_limit1) && (park_durumu == 1))
  {
    Robot_Hareket(Ileri);
    park_durumu = 2; Serial.println(park_durumu);
  }

  if ((sag_Sensor >= minimum_limit1) && (sag_arka_Sensor >= minimum_limit1) && (park_durumu == 1))
  {
    /* Dik Park Etme Kararı */
    Robot_Dur() ;
    delay(500);
    park_durumu = 10; Serial.println(park_durumu);
  }

  if ((sag_Sensor <= minimum_limit) && (sag_arka_Sensor <= minimum_limit) && (park_durumu == 2))
  {
    /* Paralel Park Etme Kararı */
    park_durumu = 3; Serial.println(park_durumu);
  }

  return park_durumu;
}

void Park_bul()
{
  Park_Yeri_Kontrol();
  if (park_durumu == 3 )
  {
    Robot_Dur(); Serial.println(park_durumu);
    delay(400);
    park_durumu = 4;
  }
  if (park_durumu == 4 )
  {

    Robot_Hareket(Geri);

    Robot_Dur(); Serial.println(park_durumu);
    delay(500);
    Robot_Hareket(Sag);

    Robot_Dur();
    delay(500);
    park_durumu = 5;
  }
  if (park_durumu == 5)
  {

    Robot_Hareket(Geri);
    long arka_Sensor = ultrasonic_arka.Ranging(CM); Serial.println(arka_Sensor);

    if (arka_Sensor > 0 && arka_Sensor <= 13)
    {
      Robot_Dur();
      delay(400);
      park_durumu = 6;
    }
    return arka_Sensor;
  }

  if (park_durumu == 6)
  {
    Robot_Hareket(Sol);
    long sag_Sensor = ultrasonic_sol_on.Ranging(CM); Serial.println(sag_Sensor);
    long sag_arka_Sensor = ultrasonic_sol_arka.Ranging(CM); Serial.println(sag_arka_Sensor);

    if (sag_Sensor == sag_arka_Sensor)
    {
      Robot_Dur();
      park_durumu = 7;
    }

    return sag_Sensor, sag_arka_Sensor;
  }
  if (park_durumu == 7)
  {
    long on_Sensor = ultrasonic_on.Ranging(CM);

    if (on_Sensor <= 10)
    {
      Robot_Dur();
      park_durumu = 8;
    }
    else
    {
      Robot_Hareket(Ileri);
    }
    return on_Sensor;
  }
  if (park_durumu == 10)
  {

    Robot_Hareket(Sol);

    Robot_Dur();
    delay(500);
    park_durumu = 7;


  }

}

void setup()
{
  Serial.begin(9600);

  attachInterrupt(5, say, CHANGE);
  pinMode(Sol_Motor1, OUTPUT);
  pinMode(Sol_Motor2, OUTPUT);
  pinMode(Sag_Motor1, OUTPUT);
  pinMode(Sag_Motor2, OUTPUT);

}

void loop()
{
  Park_bul();
}
