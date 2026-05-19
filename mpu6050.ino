/*
 * JUDUL: MPU6050 - Gyroscope + Accelerometer
 * FUNGSI: Mendeteksi gerakan, orientasi, dan goncangan
 * PIN: I2C (D1=SCL, D2=SDA)
 * RELAY: D0 (aktif 2 detik saat terjadi goncangan)
 * 
 * Library yang diperlukan:
 * - MPU6050 by Electronic Cats
 * 
 * Blynk Virtual Pin:
 * V1 = Nilai magnitude percepatan
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "MPU6050 Sensor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

BlynkTimer timer;
int16_t ax, ay, az;
int16_t gx, gy, gz;

// Threshold goncangan (sesuaikan)
const int shakeThreshold = 15000;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  // Inisialisasi MPU6050
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("❌ MPU6050 tidak terhubung!");
  } else {
    Serial.println("✅ MPU6050 terhubung");
  }
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(200L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendSensorData() {
  // Baca data accelerometer
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);
  
  // Hitung magnitude percepatan
  int magnitude = sqrt(ax*ax + ay*ay + az*az);
  
  // Kirim ke Blynk
  Blynk.virtualWrite(V1, magnitude);
  
  // Deteksi goncangan
  if (magnitude > shakeThreshold) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    Blynk.logEvent("shake_detected", "⚠️ GONCANGAN TERDETEKSI!");
    Serial.println("🚨 Goncangan terdeteksi! Relay ON");
    delay(2000);
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
  }
  
  // Tampilkan di Serial Monitor
  Serial.print("Magnitude: ");
  Serial.print(magnitude);
  Serial.print(" | Ax:");
  Serial.print(ax);
  Serial.print(" Ay:");
  Serial.print(ay);
  Serial.print(" Az:");
  Serial.println(az);
}
