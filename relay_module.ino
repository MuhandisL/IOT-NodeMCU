/*
 * JUDUL: Relay Module
 * FUNGSI: Mengontrol perangkat listrik (lampu, pompa, kipas)
 * PIN: D1 (Digital Output)
 * RELAY: D1 itu sendiri (bisa juga D2)
 * 
 * ⚠️ PERINGATAN PENTING ⚠️
 * NodeMCU output 3.3V, relay 5V butuh level shifter!
 * Gunakan transistor NPN (2N2222) sebagai driver:
 * 
 * NodeMCU D1 ── 1kΩ ── Base (NPN)
 * Emitter NPN ── GND
 * Collector NPN ── Relay IN
 * Relay VCC ── 5V external
 * Relay GND ── GND NodeMCU
 * 
 * Blynk Virtual Pin:
 * V1 = Kontrol relay (1=ON, 0=OFF)
 * V2 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Relay Control"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define RELAY_PIN D1

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Relay OFF (untuk relay aktif LOW)
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}

// Kontrol manual dari Blynk
BLYNK_WRITE(V1) {
  int value = param.asInt();
  
  if (value == 1) {
    digitalWrite(RELAY_PIN, LOW);   // Relay ON (aktif LOW)
    Blynk.virtualWrite(V2, 1);
    Serial.println("RELAY ON - Perangkat menyala");
  } else {
    digitalWrite(RELAY_PIN, HIGH);  // Relay OFF
    Blynk.virtualWrite(V2, 0);
    Serial.println("RELAY OFF - Perangkat mati");
  }
}

// Contoh kontrol otomatis berdasarkan suhu (jika ada sensor suhu)
/*
void autoControl() {
  float temperature = getTemperature();  // fungsi pembaca suhu
  if (temperature > 30.0) {
    digitalWrite(RELAY_PIN, LOW);   // Relay ON
    Blynk.virtualWrite(V2, 1);
  } else {
    digitalWrite(RELAY_PIN, HIGH);  // Relay OFF
    Blynk.virtualWrite(V2, 0);
  }
}
*/
