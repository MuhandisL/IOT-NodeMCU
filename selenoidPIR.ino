/*
=========================================
PIR + RELAY + SOLENOID + BLYNK
NodeMCU ESP8266
=========================================

PIR    -> D3
Relay  -> D0

Relay mengontrol solenoid 12V
=========================================
*/

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "PIR Motion"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "NamaWiFi";
char pass[] = "PasswordWiFi";

// PIN
#define PIR_PIN D3
#define RELAY_PIN D0

void setup() {

  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // relay OFF awal
  digitalWrite(RELAY_PIN, HIGH);

  // konek Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("System Ready");
}

void loop() {

  Blynk.run();

  int motion = digitalRead(PIR_PIN);

  // kirim status PIR ke Blynk
  Blynk.virtualWrite(V1, motion);

  // jika ada gerakan
  if (motion == HIGH) {

    Serial.println("Gerakan Terdeteksi");
    Serial.println("Relay ON");
    Serial.println("Solenoid Aktif");

    // relay ON (active LOW)
    digitalWrite(RELAY_PIN, LOW);

    Blynk.virtualWrite(V10, 1);

    // aktif 5 detik
    delay(5000);

    // relay OFF
    digitalWrite(RELAY_PIN, HIGH);

    Blynk.virtualWrite(V10, 0);

    Serial.println("Relay OFF");
    Serial.println("Solenoid Mati");
  }

  delay(500);
}