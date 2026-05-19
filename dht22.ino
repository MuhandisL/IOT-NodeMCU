/*
 * JUDUL: DHT22 - Sensor Suhu dan Kelembaban (Akurasi Tinggi)
 * FUNGSI: Mengukur suhu dan kelembaban udara dengan akurasi lebih baik
 * PIN: D4 (Digital 1-wire)
 * RELAY: D0 (aktif saat suhu > 30°C)
 * 
 * Perbedaan dengan DHT11:
 * - Akurasi lebih tinggi (±0.5°C vs ±2°C)
 * - Range lebih luas (-40°C s/d 80°C)
 * - Pembacaan lebih stabil
 * - Harga lebih mahal
 * 
 * Library yang diperlukan:
 * - DHT sensor library by Adafruit
 * 
 * Blynk Virtual Pin:
 * V5 = Kelembaban (%)
 * V6 = Suhu (°C)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "DHT22 Sensor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN D4
#define DHTTYPE DHT22
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

float humidity = 0;
float temperature = 0;

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, sendSensorData);  // DHT22 butuh interval 2 detik
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendSensorData() {
  // Baca sensor
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();  // Celcius
  
  // Cek apakah pembacaan valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("❌ Gagal membaca DHT22!");
    Blynk.virtualWrite(V5, -1);
    Blynk.virtualWrite(V6, -1);
    return;
  }
  
  // Kirim ke Blynk
  Blynk.virtualWrite(V5, humidity);
  Blynk.virtualWrite(V6, temperature);
  
  // Kontrol relay berdasarkan suhu (nyalakan kipas jika suhu > 30°C)
  if (temperature > 30.0) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    Serial.println("🔥 Suhu panas! Kipas ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
  }
  
  // Kirim notifikasi jika suhu sangat panas
  if (temperature > 35.0) {
    Blynk.logEvent("high_temp", "⚠️ Suhu sangat panas! >35°C");
  }
  
  // Kirim notifikasi jika kelembaban sangat tinggi
  if (humidity > 80.0) {
    Blynk.logEvent("high_humidity", "⚠️ Kelembaban sangat tinggi! >80%");
  }
  
  // Tampilkan di Serial Monitor
  Serial.print("🌡️ Suhu DHT22: ");
  Serial.print(temperature);
  Serial.print("°C | 💧 Kelembaban: ");
  Serial.print(humidity);
  Serial.println("%");
}

// Kontrol manual relay dari Blynk (opsional)
BLYNK_WRITE(V1) {
  int value = param.asInt();
  if (value == 1) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    Serial.println("Relay ON (manual dari Blynk)");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
    Serial.println("Relay OFF (manual dari Blynk)");
  }
}
