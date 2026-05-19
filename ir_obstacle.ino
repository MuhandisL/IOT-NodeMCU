/*
 * JUDUL: IR Obstacle Sensor (Penghalang Infrared)
 * FUNGSI: Mendeteksi penghalang di depan sensor
 * PIN: D7 (Digital)
 * RELAY: D0 (aktif 500ms saat ada penghalang)
 * 
 * Blynk Virtual Pin:
 * V1 = Status penghalang (1=ada penghalang, 0=tidak)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "IR Obstacle Sensor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define IR_PIN D7
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

BlynkTimer timer;
unsigned long lastTriggerTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(IR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(200L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendSensorData() {
  int obstacle = digitalRead(IR_PIN);  // LOW = ada penghalang
  
  Blynk.virtualWrite(V1, obstacle == LOW ? 1 : 0);
  
  if (obstacle == LOW) {
    // Cegah trigger berulang terlalu cepat
    if (millis() - lastTriggerTime > 1000) {
      digitalWrite(RELAY_PIN, HIGH);
      Blynk.virtualWrite(V10, 1);
      Serial.println("🚧 Penghalang terdeteksi! Relay ON");
      lastTriggerTime = millis();
      delay(500);
      digitalWrite(RELAY_PIN, LOW);
      Blynk.virtualWrite(V10, 0);
    }
  }
}
