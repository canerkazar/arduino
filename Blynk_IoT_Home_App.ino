#define BLYNK_PRINT Serial
#include <BlynkSimpleShieldEsp8266.h>
#include <ESP8266_Lib.h>
#include <DHT.h>
#include <Servo.h>

char auth[] = "BLYNK_AUTH KODU"; // Cihaz kodu
char ssid[] = "WIFI_ADI";
char pass[] = "WIFI_SIFRE";


#define ESP8266_BAUD 115200
ESP8266 wifi(&Serial);

#define DHTPIN 2
#define pirPin 7
#define Gaz 8
#define motor A0
#define DHTTYPE DHT11

int durum = 0;
int g_durum = 0;
int sicaklik_ref = 25;
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
Servo oda1;
Servo oda2;
Servo kapi;

void sendSensor() // Timer fonsiyonu, belirlenen zaman araliklariyla sensor verilerini kontrol ediyor
{
  float h = dht.readHumidity(); // nemi okuyoruz, DHT Kutuphanesinden
  float t = dht.readTemperature(); // sicakligi okuyoruz, DHT Kutuphanesinden
  durum = digitalRead(pirPin); // hareket var mi kontrol ediyoruz
  g_durum = !digitalRead(Gaz); // gaz kacagi var mi onu kontrol ediyoruz. Burada bir unlem var onun sebebi sensorun gaz yokken 1 gaz varken 0 degerini vermesi o ! isareti tersini aldiriyor. Yani bize gaz varken 1 yokken 0 verisi geliyor.
  if (sicaklik_ref < t) // eger belirledigimiz referans sicaklik (25 derece), ortam sicakligindan kucukse motoru calistiriyor (yani ortam sicaksa 25 dereceden klima calisiyor ve ortam soguyor)
  {
    digitalWrite(motor, HIGH);
  }
  else if (sicaklik_ref > t) // 25 dereceden kucukse motoru durduruyor. Bu kontrol yapilmali cunku sistem hiç durmaz
  {
    digitalWrite(motor, LOW);
  }
  if (isnan(h) || isnan(t)) { // DHT yanlis okuma yaparsa hicbir sey gonderme
    Serial.println("Hata");
    return;
  }
  // sanal pinler. Bunlar web ve mobil uygulama icin gerekli
  Blynk.virtualWrite(V5, h); // sanal pin olusturduk ve bu pine nemi yazdiriyoruz
  Blynk.virtualWrite(V6, t); // sanal pin olusturduk ve bu pine sicakligi yazdiriyoruz
  Blynk.virtualWrite(V7, durum); // sanal pin olusturduk ve bu pine hareketi yazdiriyoruz
  Blynk.virtualWrite(V8, g_durum); // sanal pin olusturduk ve bu pine gaz durumunu yazdiriyoruz
}

void setup()
{
  // seri haberlesmeyi baslattik bu sistemin bilgisayar ile haberlesmesini sagliyor
  Serial.begin(9600);
  pinMode(pirPin, INPUT); // hareket pinini giris pini olarak tanimladik
  pinMode(Gaz, INPUT); // gaz pinini cikis pini olarak tanimladik
  pinMode(motor, OUTPUT); // motoru cikis pini olarak tanimladik
  oda1.attach(3); // oda1 perdesi icin servo motoru tanimladik
  oda2.attach(5); // oda2 perdesi icin servo motoru tanimladik
  kapi.attach(6); // Kapi icin servo motoru tanimladik
  Serial.begin(ESP8266_BAUD); // esp kendi basina ayri bir sistem oldugu icin onun icinde haberlesecegi bir baudrate baslangici yapiyoruz (115200)
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass); // web ve mobil uygulamamiz icin sisteme wifi ve cihaz kodu bilgilerini giriyoruz
  dht.begin(); // dht kutuphanesini baslatiyoruz
  timer.setInterval(1000L, sendSensor); // bu fonsiyon sistemin kac saniyede bir sensorlerdeki verileri olcecegini belirliyor (1000ms = 1 saniye demek) burada 1 saniyede bir guncelleme yapıyor anlamina geliyor
}

void loop()
{
  Blynk.run(); // ESP8266_Lib.h kutuphanesindeki run komutunu calistirdik ve sistemimiz internete baglanmaya hazir oluyor ve telefondaki blynk uygulamasiyla baglanti kurmaya basliyor
  timer.run(); // basta yazdigim timeri baslatiyor
}

BLYNK_WRITE(V1) // burada bylnk uygulamasindaki açı verilerini servoya yazirdigimiz icin WRITE komutu kullanildi
{
  oda1.write(param.asInt()); // param.asInt(); fonsiyonu blynk uygulamasindaki tanimlanan deger demek (gondermek istedigimiz tanimli deger)
}

BLYNK_WRITE(V2)
{
  oda2.write(param.asInt());
}
BLYNK_WRITE(V3)
{
  kapi.write(param.asInt());
}

BLYNK_WRITE(V4) {
  sicaklik_ref = param.asInt();
}
