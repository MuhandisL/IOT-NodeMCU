/*
 * Sensor: LDR (Light Dependent Resistor)
 * Fungsi: Membaca intensitas cahaya
 * Pin: A0 (Analog)
 * Relay: D0 (aktif saat gelap)
 * 
 * Cara Kerja:
 * - analogRead(A0) membaca nilai 0-1023
 * - Nilai kecil = terang, nilai besar = gelap
 * - Relay ON saat nilai > threshold (gelap)
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "LDR Sensor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define LDR_PIN A0
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

int threshold = 500;  // Sesuaikan dengan kondisi ruangan
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendSensorData() {
  int ldrValue = analogRead(LDR_PIN);
  
  // Kirim ke Blynk
  Blynk.virtualWrite(V1, ldrValue);
  
  // Kontrol relay
  if (ldrValue > threshold) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    Serial.println("RELAY ON - Gelap");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
    Serial.println("RELAY OFF - Terang");
  }
  
  // Konversi ke persen
  int lightPercent = map(ldrValue, 0, 1024, 100, 0);
  Blynk.virtualWrite(V2, lightPercent);
  
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
}
