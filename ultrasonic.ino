/*
 * JUDUL: Ultrasonic HC-SR04
 * FUNGSI: Mengukur jarak (cm) - bisa untuk level air atau parking sensor
 * PIN: D5 (Trig), D6 (Echo)
 * RELAY: D0 (aktif jika jarak < 20 cm)
 * 
 * Cara Kerja:
 * - Memancarkan gelombang ultrasonik
 * - Mengukur waktu pantul
 * - Jarak = (waktu × kecepatan suara) / 2
 * 
 * Blynk Virtual Pin:
 * V1 = Jarak (cm)
 * V2 = Level air / persentase (jika digunakan untuk tangki)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Ultrasonic Sensor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define TRIG_PIN D5
#define ECHO_PIN D6
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

BlynkTimer timer;

// Parameter untuk tangki (sesuaikan dengan tinggi tangki Anda)
const int maxDistance = 50;   // Tinggi maksimum tangki (cm)
const int minDistance = 5;    // Tinggi minimum (cm)

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(500L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

long measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;  // konversi ke cm
  return distance;
}

void sendSensorData() {
  int distance = measureDistance();
  
  // Validasi pembacaan
  if (distance <= 0 || distance > 400) {
    Serial.println("❌ Pembacaan jarak tidak valid!");
    return;
  }
  
  Blynk.virtualWrite(V1, distance);
  
  // Untuk level air (invers: jarak kecil = tangki penuh)
  int waterLevelPercent = map(distance, maxDistance, minDistance, 0, 100);
  if (waterLevelPercent < 0) waterLevelPercent = 0;
  if (waterLevelPercent > 100) waterLevelPercent = 100;
  Blynk.virtualWrite(V2, waterLevelPercent);
  
  // Relay ON jika jarak < 20 cm (misal: tangki hampir penuh)
  if (distance < 20) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    Serial.println("⚠️ Jarak < 20cm! Relay ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
  }
  
  Serial.print("📏 Jarak
