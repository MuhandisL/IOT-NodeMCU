/*
 * JUDUL: BMP280 - Sensor Tekanan Udara dan Suhu
 * FUNGSI: Mengukur tekanan udara (hPa) dan suhu
 * PIN: I2C (D1=SCL, D2=SDA)
 * RELAY: D0 (aktif saat tekanan turun drastis -> tanda badai)
 * 
 * Library yang diperlukan:
 * - Adafruit BMP280 Library
 * 
 * Blynk Virtual Pin:
 * V1 = Tekanan udara (hPa)
 * V2 = Suhu (°C)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "BMP280 Sensor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

BlynkTimer timer;
float pressure = 0;
float temperature = 0;
float lastPressure = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  // Inisialisasi BMP280 (alamat I2C 0x76 atau 0x77)
  if (!bmp.begin(0x76)) {
    Serial.println("❌ BMP280 tidak ditemukan!");
  } else {
    Serial.println("✅ BMP280 terhubung");
  }
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendSensorData() {
  pressure = bmp.readPressure() / 100.0F;  // Konversi ke hPa
  temperature = bmp.readTemperature();
  
  // Kirim ke Blynk
  Blynk.virtualWrite(V1, pressure);
  Blynk.virtualWrite(V2, temperature);
  
  // Deteksi perubahan tekanan (potensi badai)
  if (lastPressure != 0) {
    float pressureDrop = lastPressure - pressure;
    
    if (pressureDrop > 3.0) {  // Turun lebih dari 3 hPa
      digitalWrite(RELAY_PIN, HIGH);
      Blynk.virtualWrite(V10, 1);
      Blynk.logEvent("storm_warning", "⚠️ Tekanan turun! Potensi badai");
      Serial.println("🌧️ PERINGATAN: Tekanan udara turun drastis!");
    } else {
      digitalWrite(RELAY_PIN, LOW);
      Blynk.virtualWrite(V10, 0);
    }
  }
  
  lastPressure = pressure;
  
  Serial.print("Tekanan: ");
  Serial.print(pressure);
  Serial.print(" hPa | Suhu: ");
  Serial.print(temperature);
  Serial.println(" °C");
}
