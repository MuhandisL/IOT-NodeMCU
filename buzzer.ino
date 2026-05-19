/*
 * JUDUL: Buzzer
 * FUNGSI: Menghasilkan suara (alarm/notifikasi)
 * PIN: D5 (Digital Output)
 * RELAY: Menyala bersamaan dengan buzzer
 * 
 * Cara Kerja:
 * - Output HIGH = bunyi (untuk buzzer aktif HIGH)
 * - Dapat menghasilkan nada dengan tone()
 * - Bisa dikontrol manual dari Blynk
 * 
 * Blynk Virtual Pin:
 * V1 = Kontrol manual buzzer (1=ON, 0=OFF)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Buzzer"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BUZZER_PIN D5
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(10000L, alarmPattern);  // Alarm setiap 10 detik
}

void loop() {
  Blynk.run();
  timer.run();
}

// Pola alarm: bip 3 kali
void alarmPattern() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    delay(300);
    
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
    delay(300);
  }
  Serial.println("Alarm berbunyi - 3x beep");
}

// Kontrol manual dari Blynk
BLYNK_WRITE(V1) {
  int value = param.asInt();
  if (value == 1) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    Serial.println("Buzzer ON (manual)");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
    Serial.println("Buzzer OFF (manual)");
  }
}

// Untuk menghasilkan nada tertentu (opsional)
void playTone(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
  digitalWrite(RELAY_PIN, HIGH);
  Blynk.virtualWrite(V10, 1);
  delay(duration);
  digitalWrite(RELAY_PIN, LOW);
  Blynk.virtualWrite(V10, 0);
  noTone(BUZZER_PIN);
}
