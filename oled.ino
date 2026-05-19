/*
 * JUDUL: OLED I2C Display (SSD1306)
 * FUNGSI: Menampilkan teks dan data sensor
 * PIN: I2C (D1=SCL, D2=SDA)
 * RELAY: D0 (tidak langsung dikontrol, hanya ditampilkan)
 * 
 * Library yang diperlukan:
 * - Adafruit SSD1306 by Adafruit
 * - Adafruit GFX Library
 * 
 * Blynk Virtual Pin:
 * - (Display lokal saja, tidak kirim data ke Blynk)
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "OLED Display"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define RELAY_PIN D0

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

BlynkTimer timer;
int ldrValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  // Inisialisasi OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("❌ SSD1306 tidak ditemukan!");
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, updateDisplay);
  timer.setInterval(500L, readSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}

void readSensor() {
  ldrValue = analogRead(A0);  // Contoh baca LDR
}

void updateDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0);
  
  // Tampilkan judul
  display.println("NodeMCU Sensor Hub");
  display.println("----------------");
  
  // Tampilkan data sensor
  display.print("LDR: ");
  display.print(ldrValue);
  display.println("   ");
  
  display.print("Relay: ");
  display.println(digitalRead(RELAY_PIN) ? "ON " : "OFF");
  
  // Tampilkan waktu (opsional)
  display.print("Time: ");
  display.print(millis() / 1000);
  display.println("s");
  
  display.display();
  
  Serial.println("OLED Display diperbarui");
}
