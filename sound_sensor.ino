/*
 * JUDUL: Sound Sensor (Sensor Suara)
 * FUNGSI: Mendeteksi suara (clap switch / deteksi kebisingan)
 * PIN: A0 (Analog), D2 (Digital)
 * RELAY: D0 (toggle setiap kali suara keras terdeteksi)
 * 
 * Blynk Virtual Pin:
 * V1 = Level suara (analog, 0-1024)
 * V2 = Status digital (1=suara terdeteksi)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Sound Sensor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define SOUND_ANALOG A0
#define SOUND_DIGITAL D2
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

int soundThreshold = 600;
bool relayState = false;
unsigned long lastClapTime = 0;

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(SOUND_DIGITAL, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(200L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendSensorData() {
  int soundLevel = analogRead(SOUND_ANALOG);
  int soundDetected = digitalRead(SOUND_DIGITAL);
  
  Blynk.virtualWrite(V1, soundLevel);
  Blynk.virtualWrite(V2, soundDetected == LOW ? 1 : 0);
  
  // Clap detection (toggle relay)
  if ((soundLevel > soundThreshold || soundDetected == LOW) && 
      (millis() - lastClapTime > 500)) {  // Debounce 500ms
    
    relayState = !relayState;
    digitalWrite(RELAY_PIN, relayState);
    Blynk.virtualWrite(V10, relayState);
    lastClapTime = millis();
    
    Serial.print("👏 Suara terdeteksi! Relay: ");
    Serial.println(relayState ? "ON" : "OFF");
  }
  
  Serial.print("Level suara: ");
  Serial.println(soundLevel);
}
