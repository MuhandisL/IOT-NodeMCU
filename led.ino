/*
 * JUDUL: LED (Light Emitting Diode)
 * FUNGSI: Output cahaya yang bisa dikontrol
 * PIN: D6 (Digital Output)
 * RELAY: Mengikuti status LED
 * 
 * Cara Kerja:
 * - Output HIGH = LED menyala
 * - Dapat dikontrol manual dari Blynk
 * - Relay menyala bersamaan dengan LED
 * 
 * Blynk Virtual Pin:
 * V1 = Kontrol LED (1=ON, 0=OFF)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "LED Control"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define LED_PIN D6
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}

// Kontrol dari Blynk Button
BLYNK_WRITE(V1) {
  int value = param.asInt();  // Nilai 0 atau 1 dari Blynk
  
  digitalWrite(LED_PIN, value);
  digitalWrite(RELAY_PIN, value);
  Blynk.virtualWrite(V10, value);
  
  Serial.print("LED dan Relay: ");
  Serial.println(value ? "ON" : "OFF");
}
