/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6chj2M2ia"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "j9O-pU5RGUJwBObO69q2LM_0Nox0p6BC"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <Servo.h>

#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN D6
#define DHTTYPE DHT11

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "iPhone";
char pass[] = "satuduatiga";

Servo S;
int hujan = D4; // Pin D4
int cahaya = D8; // Pin D8

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  S.attach(D2); // Pin D2
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  // Inisialisasi sensor suhu
  dht.begin();
}
void loop() {
  Blynk.run();
  int cahayaValue = 0;
  int hujanValue = 0;
  float temperature = 0.0;

  hujanValue = digitalRead(hujan);
  cahayaValue = digitalRead(cahaya);
  Serial.println(cahayaValue);

  // Baca nilai suhu
  float t = dht.readTemperature();
  temperature = t;

  // Baca nilai suhu dan Kirim nilai suhu ke Blynk
  Blynk.virtualWrite(V2, temperature);

  Blynk.virtualWrite(V6, cahayaValue);
  if (cahayaValue == LOW) {
    Serial.println("Terdapat Cahaya");
    Blynk.virtualWrite(V6, "Terdapat Cahaya");
    Serial.print(cahayaValue);

    Blynk.virtualWrite(V5, hujanValue);
    Serial.println(hujanValue);
    if (hujanValue == LOW) {
      S.write(120);
      Serial.println("Terdapat Air");
      Blynk.virtualWrite(V5, "Ada Air");
    } else {
      S.write(0);
      Serial.println("Tidak Ada Air");
      Blynk.virtualWrite(V5, "Tidak Ada Air");
    }
       
  } else {
    S.write(120);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Tidak ada cahaya");
    Blynk.virtualWrite(V6, "Tidak ada cahaya");
  }

  delay(1000);
  Blynk.run();
}
