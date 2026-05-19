/*
 * JUDUL: Flame Sensor (Sensor Api)
 * FUNGSI: Mendeteksi api atau sumber api
 * PIN: D2 (Digital)
 * RELAY: D0 (aktif saat api terdeteksi)
 * 
 * Cara Kerja:
 * - Sensor mendeteksi sinar infrared dari api
 * - Output LOW saat ada api
 * - Respon cepat untuk safety (delay kecil)
 * 
 * Blynk Virtual Pin:
 * V1 = Status api (1=detected, 0=no flame)
 * V10 = Status relay alarm
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Flame Sensor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define FLAME_PIN D2
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(FLAME_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(200L, sendSensorData);  // Respon cepat!
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendSensorData() {
  int flameDetected = digitalRead(FLAME_PIN);  // LOW = ada api
  
  Blynk.virtualWrite(V1, flameDetected == LOW ? 1 : 0);
  
  if (flameDetected == LOW) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    Blynk.logEvent("fire_alarm", "🔥 API TERDETEKSI! 🔥");
    Serial.println("🚨⚠️ API TERDETEKSI! SEGERA TINDAKAN! ⚠️🚨");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
  }
}
