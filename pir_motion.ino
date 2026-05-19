/*
 * JUDUL: PIR Motion Sensor (Sensor Gerak)
 * FUNGSI: Mendeteksi gerakan manusia
 * PIN: D3 (Digital)
 * RELAY: D0 (aktif 5 detik saat ada gerakan)
 * 
 * Cara Kerja:
 * - Sensor passive infrared mendeteksi panas tubuh
 * - Output HIGH saat ada gerakan
 * - Relay ON selama 5 detik kemudian OFF
 * 
 * Blynk Virtual Pin:
 * V1 = Status gerakan (1=motion, 0=no motion)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "PIR Motion"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define PIR_PIN D3
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(500L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendSensorData() {
  int motion = digitalRead(PIR_PIN);
  
  Blynk.virtualWrite(V1, motion);
  
  if (motion == HIGH) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    Serial.println("🚶 Gerakan Terdeteksi! Relay ON");
    delay(5000);  // Relay ON selama 5 detik
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
    Serial.println("Relay OFF setelah 5 detik");
  }
}
