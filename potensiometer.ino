/*
 * JUDUL: Potensiometer
 * FUNGSI: Membaca perubahan resistansi manual
 * PIN: A0 (Analog)
 * RELAY: D0 (aktif saat nilai > 512)
 * 
 * Cara Kerja:
 * - Membaca tegangan dari pembagi tegangan
 * - Nilai 0-1024 tergantung posisi putaran
 * - Relay ON saat nilai > 512 (setengah putaran)
 * 
 * Blynk Virtual Pin:
 * V1 = Nilai potensiometer (0-1024)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Potensiometer"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define POT_PIN A0
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
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
  int potValue = analogRead(POT_PIN);
  
  Blynk.virtualWrite(V1, potValue);
  
  // Kontrol relay (relay ON jika potensiometer diputar > setengah)
  if (potValue > 512) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    Serial.println("RELAY ON - Potensiometer > 512");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
    Serial.println("RELAY OFF - Potensiometer < 512");
  }
  
  Serial.print("Potensiometer Value: ");
  Serial.println(potValue);
}
