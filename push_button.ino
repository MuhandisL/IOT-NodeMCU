/*
 * JUDUL: Push Button (Tombol)
 * FUNGSI: Input tombol manual untuk kontrol
 * PIN: D4 (Digital dengan internal pull-up)
 * RELAY: Toggle setiap tombol ditekan
 * 
 * Cara Kerja:
 * - Menggunakan INPUT_PULLUP (internal pull-up)
 * - Tombol ditekan = LOW
 * - Toggle relay setiap kali tombol ditekan
 * 
 * Blynk Virtual Pin:
 * V1 = Status tombol (1=ditekan, 0=lepas)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Push Button"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BUTTON_PIN D4
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

bool relayState = false;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  
  bool buttonState = digitalRead(BUTTON_PIN);
  
  // Kirim status tombol ke Blynk
  Blynk.virtualWrite(V1, buttonState == LOW ? 1 : 0);
  
  // Deteksi debounce
  if (buttonState != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  // Deteksi ketika tombol ditekan (LOW) setelah debounce
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState == LOW && lastButtonState == HIGH) {
      relayState = !relayState;
      digitalWrite(RELAY_PIN, relayState);
      Blynk.virtualWrite(V10, relayState);
      Serial.print("Tombol ditekan - Relay: ");
      Serial.println(relayState ? "ON" : "OFF");
      delay(100);
    }
  }
  
  lastButtonState = buttonState;
}
