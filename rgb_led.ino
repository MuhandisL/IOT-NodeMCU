/*
 * JUDUL: RGB LED
 * FUNGSI: Menghasilkan warna cahaya yang dapat diatur (Merah, Hijau, Biru)
 * PIN: D1 (Merah), D2 (Hijau), D3 (Biru) - PWM
 * RELAY: D0 (aktif saat LED menyala)
 * 
 * Blynk Virtual Pin:
 * V1 = Color Picker (nilai warna 0xRRGGBB)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "RGB LED"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define RED_PIN D1
#define GREEN_PIN D2
#define BLUE_PIN D3
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

bool ledOn = false;

void setup() {
  Serial.begin(115200);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}

// Konversi nilai 0-255 ke PWM NodeMCU (0-1023)
int convertPWM(int value) {
  return map(value, 0, 255, 0, 1023);
}

// Kontrol dari Blynk Color Picker
BLYNK_WRITE(V1) {
  int color = param.asInt();  // Nilai warna format 0xRRGGBB
  
  int red = (color >> 16) & 0xFF;
  int green = (color >> 8) & 0xFF;
  int blue = color & 0xFF;
  
  analogWrite(RED_PIN, convertPWM(red));
  analogWrite(GREEN_PIN, convertPWM(green));
  analogWrite(BLUE_PIN, convertPWM(blue));
  
  // Nyalakan relay jika LED menyala (ada warna)
  if (red > 0 || green > 0 || blue > 0) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    ledOn = true;
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
    ledOn = false;
  }
  
  Serial.print("RGB Color: R=");
  Serial.print(red);
  Serial.print(" G=");
  Serial.print(green);
  Serial.print(" B=");
  Serial.println(blue);
}
