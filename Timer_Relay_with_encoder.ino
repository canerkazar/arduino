#define role A1
#define lm35 A0
const int PinSW = 4; 
const int PinDT = 2;  
const int PinCLK = 3;  
int sicaklikVolt;
float sicaklikC;

long TimeOfLastDebounce = 0;
int DelayofDebounce = 0.01;
float checkTemp = 10000.00;

int PreviousCLK;
int PreviousDATA;
int butonState = 1;
int displaycounter = 0;
#define led1 13
#define led2 12
#define led3 11
#define led4 10
#define led5 9
#define led6 8
#define led7 7
#define led8 6
#define led9 5


void setup() {
  pinMode (A4, OUTPUT);
  digitalWrite(A4, HIGH);
  PreviousCLK = digitalRead(PinCLK);
  PreviousDATA = digitalRead(PinDT);


  pinMode(PinSW, INPUT_PULLUP);
  pinMode (role, OUTPUT);
  for (int x = 5; x <= 13; x++) {
    pinMode(x, OUTPUT);
  }
  for (int x = 5; x <= 13; x++) {
    digitalWrite(x, LOW);
  }
  Serial.begin(115200);
  analogReference(INTERNAL);
}
void loop() {





  if (digitalRead(PinSW) == LOW) {
    digitalWrite(A4, !digitalRead(A4));
    delay(1000);
    butonState = digitalRead(A4);

  }

  if (butonState == 0)
  {
    if ((millis() - TimeOfLastDebounce) > DelayofDebounce) {

      check_rotary();  
      if (displaycounter < 1) displaycounter = 1;
      if (displaycounter > 18) displaycounter = 18;
      PreviousCLK = digitalRead(PinCLK);
      PreviousDATA = digitalRead(PinDT);
      TimeOfLastDebounce = millis();
    }
    sicaklik_olc();
    if (sicaklikC <= checkTemp)
    {
      digitalWrite(role, HIGH);
    }
    else if (sicaklikC > checkTemp)
    {
      digitalWrite(role, LOW);
    }
    if (displaycounter == 1 || displaycounter == 2)
    {
      if (digitalRead(role) == HIGH)
      {
        ledPrgOnOff(500, 500, led1);
      }
      else if (digitalRead(role) == LOW)
      {
        digitalWrite(led1, HIGH);
      }
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      digitalWrite(led9, LOW);
      checkTemp = 35;
    }
    else if (displaycounter == 3 || displaycounter == 4)
    {
      digitalWrite(led1, HIGH);
      if (digitalRead(role) == HIGH)
      {
        ledPrgOnOff(500, 500, led2);
      }
      else if (digitalRead(role) == LOW)
      {
        digitalWrite(led2, HIGH);
      }
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      digitalWrite(led9, LOW);
      checkTemp = 40;
    }
    else if (displaycounter == 5 || displaycounter == 6)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      if (digitalRead(role) == HIGH)
      {
        ledPrgOnOff(500, 500, led3);
      }
      else if (digitalRead(role) == LOW)
      {
        digitalWrite(led3, HIGH);
      }
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      digitalWrite(led9, LOW);
      checkTemp = 45;
    }
    else if (displaycounter == 7 || displaycounter == 8)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      if (digitalRead(role) == HIGH)
      {
        ledPrgOnOff(500, 500, led4);
      }
      else if (digitalRead(role) == LOW)
      {
        digitalWrite(led4, HIGH);
      }
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      digitalWrite(led9, LOW);
      checkTemp = 50;
    }
    else if (displaycounter == 9 || displaycounter == 10)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      if (digitalRead(role) == HIGH)
      {
        ledPrgOnOff(500, 500, led5);
      }
      else if (digitalRead(role) == LOW)
      {
        digitalWrite(led5, HIGH);
      }
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      digitalWrite(led9, LOW);
      checkTemp = 55;
    }
    else if (displaycounter == 11 || displaycounter == 12)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      if (digitalRead(role) == HIGH)
      {
        ledPrgOnOff(500, 500, led6);
      }
      else if (digitalRead(role) == LOW)
      {
        digitalWrite(led6, HIGH);
      }
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      digitalWrite(led9, LOW);
      checkTemp = 60;
    }
    else if (displaycounter == 13 || displaycounter == 14)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      if (digitalRead(role) == HIGH)
      {
        ledPrgOnOff(500, 500, led7);
      }
      else if (digitalRead(role) == LOW)
      {
        digitalWrite(led7, HIGH);
      }
      digitalWrite(led8, LOW);
      digitalWrite(led9, LOW);
      checkTemp = 65;
    }
    else if (displaycounter == 15 || displaycounter == 16)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(led7, HIGH);
      if (digitalRead(role) == HIGH)
      {
        ledPrgOnOff(500, 500, led8);
      }
      else if (digitalRead(role) == LOW)
      {
        digitalWrite(led8, HIGH);
      }
      digitalWrite(led9, LOW);
      checkTemp = 70;
    }
    else if (displaycounter == 17 || displaycounter == 18)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(led7, HIGH);
      digitalWrite(led8, HIGH);
      if (digitalRead(role) == HIGH)
      {
        ledPrgOnOff(500, 500, led9);
      }
      else if (digitalRead(role) == LOW)
      {
        digitalWrite(led9, HIGH);
      }
      checkTemp = 75;
    }



  }
  if (butonState == 1) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    digitalWrite(led9, LOW);
    digitalWrite(role, LOW);
  }



}

void sicaklik_olc()
{ unsigned long CM = millis();
  static unsigned long PM = 0;
  static boolean LS;
  static boolean OL = 1;
  static boolean OFL = 0;

  if (OL)
  {
    if (CM - PM >= 1000)
    {
      sicaklikVolt = analogRead(lm35);
      sicaklikC = sicaklikVolt / 9.31;
      PM = CM;
    }
  }
  
   

  
}



void check_rotary() {

  if ((PreviousCLK == 0) && (PreviousDATA == 1)) {
    if ((digitalRead(PinCLK) == 1) && (digitalRead(PinDT) == 0)) {
      displaycounter++;

    }
    if ((digitalRead(PinCLK) == 1) && (digitalRead(PinDT) == 1)) {
      displaycounter--;

    }
  }

  if ((PreviousCLK == 1) && (PreviousDATA == 0)) {
    if ((digitalRead(PinCLK) == 0) && (digitalRead(PinDT) == 1)) {
      displaycounter++;

    }
    if ((digitalRead(PinCLK) == 0) && (digitalRead(PinDT) == 0)) {
      displaycounter--;

    }
  }

  if ((PreviousCLK == 1) && (PreviousDATA == 1)) {
    if ((digitalRead(PinCLK) == 0) && (digitalRead(PinDT) == 1)) {
      displaycounter++;

    }
    if ((digitalRead(PinCLK) == 0) && (digitalRead(PinDT) == 0)) {
      displaycounter--;

    }
  }

  if ((PreviousCLK == 0) && (PreviousDATA == 0)) {
    if ((digitalRead(PinCLK) == 1) && (digitalRead(PinDT) == 0)) {
      displaycounter++;

    }
    if ((digitalRead(PinCLK) == 1) && (digitalRead(PinDT) == 1)) {
      displaycounter--;

    }
  }
}

void ledPrgOnOff(long offPeriod, long onPeriod, byte ledPin )
{
  unsigned long currentMillis = millis();
  static unsigned long previousMillis = 0;
  static boolean ledState;
  static boolean onLED = 1;
  static boolean offLED = 0;

  if (onLED)
  {
    if (currentMillis - previousMillis >= offPeriod)
    {
      ledState = HIGH;
      onLED = 0;
      offLED = 1;
      previousMillis = currentMillis;
    }
  }
  if (offLED)
  {
    if (currentMillis - previousMillis >= onPeriod)
    {
      ledState = LOW;
      onLED = 1;
      offLED = 0;
      previousMillis = currentMillis;
    }
  }
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}
