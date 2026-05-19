/*
 * JUDUL: LCD I2C 16x2
 * FUNGSI: Menampilkan teks 2 baris
 * PIN: I2C (D1=SCL, D2=SDA)
 * RELAY: D0 (ditampilkan statusnya di LCD)
 * 
 * Library yang diperlukan:
 * - LiquidCrystal I2C by Frank de Brabander
 * 
 * Blynk Virtual Pin:
 * - (Display lokal saja)
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "LCD Display"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Alamat I2C umumnya 0x27 atau 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define RELAY_PIN D0

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

BlynkTimer timer;
float temperature = 25.5;
int ldrValue = 500;

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, updateLCD);
  timer.setInterval(500L, readSensors);
}

void loop() {
  Blynk.run();
  timer.run();
}

void readSensors() {
  ldrValue = analogRead(A0);
  // Contoh: baca DHT jika ada
  // temperature = dht.readTemperature();
}

void updateLCD() {
  lcd.setCursor(0, 0);
  lcd.print("LDR:");
  lcd.print(ldrValue);
  lcd.print("   ");
  
  lcd.setCursor(0, 1);
  lcd.print("Relay:");
  lcd.print(digitalRead(RELAY_PIN) ? "ON " : "OFF");
  lcd.print(" Tmp:");
  lcd.print(temperature, 1);
  lcd.print("C");
  
  Serial.println("LCD Display diperbarui");
}
