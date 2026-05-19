/*
 * JUDUL: Rain Sensor (Sensor Hujan)
 * FUNGSI: Mendeteksi hujan dan intensitasnya
 * PIN: A0 (Analog), D3 (Digital)
 * RELAY: D0 (aktif saat hujan terdeteksi -> jemuran otomatis)
 * 
 * Blynk Virtual Pin:
 * V1 = Intensitas hujan (analog, 0-1024)
 * V2 = Status digital (1=hujan, 0=tidak)
 * V10 = Status relay (penutup jemuran)
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Rain Sensor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define RAIN_ANALOG A0
#define RAIN_DIGITAL D3
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

// Threshold hujan (nilai analog > threshold = hujan)
int rainThreshold = 500;

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(RAIN_DIGITAL, INPUT);
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
  int rainIntensity = analogRead(RAIN_ANALOG);
  int rainDetected = digitalRead(RAIN_DIGITAL);  // LOW = hujan
  
  Blynk.virtualWrite(V1, rainIntensity);
  Blynk.virtualWrite(V2, rainDetected == LOW ? 1 : 0);
  
  // Jika hujan terdeteksi
  if (rainDetected == LOW || rainIntensity > rainThreshold) {
    digitalWrite(RELAY_PIN, HIGH);  // Aktifkan penutup jemuran
    Blynk.virtualWrite(V10, 1);
    Blynk.logEvent("rain_detected", "🌧️ Hujan terdeteksi! Jemuran ditutup");
    Serial.println("🌧️ HUJAN TERDETEKSI! Relay ON - Jemuran ditutup");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
    Serial.println("☀️ Tidak hujan - Relay OFF");
  }
  
  Serial.print("Intensitas hujan: ");
  Serial.println(rainIntensity);
}
