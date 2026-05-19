/*
 * JUDUL: Soil Moisture Sensor (Kelembaban Tanah)
 * FUNGSI: Mengukur kelembaban tanah untuk irigasi otomatis
 * PIN: A0 (Analog)
 * RELAY: D0 (aktif saat tanah kering -> nyalakan pompa)
 * 
 * Cara Kerja:
 * - Tanah basah = resistansi kecil = nilai kecil
 * - Tanah kering = resistansi besar = nilai besar
 * - Relay ON (pompa menyala) saat tanah kering
 * 
 * Blynk Virtual Pin:
 * V1 = Nilai mentah (0-1024)
 * V2 = Persentase kelembaban (0-100%)
 * V10 = Status relay (pompa)
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Soil Moisture"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define SOIL_PIN A0
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

// Threshold tanah kering (sesuaikan dengan sensor Anda)
// Biasanya 700-800 untuk tanah kering
int dryThreshold = 700;

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
  int soilValue = analogRead(SOIL_PIN);
  
  // Kirim nilai mentah ke Blynk
  Blynk.virtualWrite(V1, soilValue);
  
  // Konversi ke persen (0% kering, 100% basah)
  int moisturePercent = map(soilValue, 1024, 0, 0, 100);
  if (moisturePercent < 0) moisturePercent = 0;
  if (moisturePercent > 100) moisturePercent = 100;
  Blynk.virtualWrite(V2, moisturePercent);
  
  // Kontrol relay (pompa)
  if (soilValue > dryThreshold) {
    digitalWrite(RELAY_PIN, HIGH);  // Nyalakan pompa
    Blynk.virtualWrite(V10, 1);
    Blynk.logEvent("soil_dry", "Tanah Kering! Pompa menyala");
    Serial.println("⚠️ Tanah KERING - Pompa ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Matikan pompa
    Blynk.virtualWrite(V10, 0);
    Serial.println("✅ Tanah BASAH - Pompa OFF");
  }
  
  Serial.print("Soil Value: ");
  Serial.print(soilValue);
  Serial.print(" | Kelembaban: ");
  Serial.print(moisturePercent);
  Serial.println("%");
}
