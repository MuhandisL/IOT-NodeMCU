/*
 * JUDUL: Touch Sensor (Sensor Sentuh Kapasitif)
 * FUNGSI: Mendeteksi sentuhan
 * PIN: D5 (Digital)
 * RELAY: D0 (toggle setiap kali disentuh)
 * 
 * Blynk Virtual Pin:
 * V1 = Status sentuhan (1=tersentuh, 0=tidak)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Touch Sensor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define TOUCH_PIN D5
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

bool relayState = false;
bool lastTouchState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(TOUCH_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(100L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendSensorData() {
  int touchState = digitalRead(TOUCH_PIN);  // HIGH = disentuh
  
  Blynk.virtualWrite(V1, touchState);
  
  // Deteksi edge rising (saat disentuh)
  if (touchState == HIGH && lastTouchState == LOW) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      relayState = !relayState;
      digitalWrite(RELAY_PIN, relayState);
      Blynk.virtualWrite(V10, relayState);
      lastDebounceTime = millis();
      
      Serial.print("✋ Sensor disentuh! Relay: ");
      Serial.println(relayState ? "ON" : "OFF");
    }
  }
  
  lastTouchState = touchState;
}
