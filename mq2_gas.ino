/*
 * JUDUL: MQ-2 Gas Sensor
 * FUNGSI: Mendeteksi gas berbahaya (LPG, smoke, methane, hydrogen)
 * PIN: A0 (Analog), D1 (Digital)
 * RELAY: D0 (aktif saat gas terdeteksi)
 * 
 * Cara Kerja:
 * - Mode Analog: membaca konsentrasi gas (0-1024)
 * - Mode Digital: output LOW saat gas terdeteksi
 * - Relay ON + notifikasi darurat saat gas terdeteksi
 * 
 * Blynk Virtual Pin:
 * V1 = Konsentrasi gas (0-1024)
 * V2 = Status digital (0/1)
 * V10 = Status relay alarm
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "MQ-2 Gas Sensor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define MQ2_ANALOG A0
#define MQ2_DIGITAL D1
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

// Threshold gas (sesuaikan, 400-600 cukup sensitif)
int gasThreshold = 400;

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(MQ2_DIGITAL, INPUT);
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
  int gasValue = analogRead(MQ2_ANALOG);
  int gasDetected = digitalRead(MQ2_DIGITAL);  // LOW = terdeteksi
  
  Blynk.virtualWrite(V1, gasValue);
  Blynk.virtualWrite(V2, gasDetected == LOW ? 1 : 0);
  
  // Jika gas terdeteksi (analog melebihi threshold ATAU digital LOW)
  if (gasValue > gasThreshold || gasDetected == LOW) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    Blynk.logEvent("gas_leak", "⚠️ GAS BERBAHAYA TERDETEKSI! ⚠️");
    Serial.println("🚨 GAS TERDETEKSI - Alarm ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
    Serial.println("✅ Gas aman - Alarm OFF");
  }
  
  Serial.print("Gas Value: ");
  Serial.print(gasValue);
  Serial.print(" | Threshold: ");
  Serial.println(gasThreshold);
}
