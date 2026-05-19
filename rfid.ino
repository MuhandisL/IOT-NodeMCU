/*
 * JUDUL: RFID RC522 - Pembaca Kartu RFID
 * FUNGSI: Membaca kartu RFID untuk akses kontrol
 * PIN: SPI (D5=SCK, D6=MISO, D7=MOSI, D8=SS), RST=D3
 * RELAY: D0 (aktif 3 detik saat kartu valid)
 * 
 * Cara Kerja:
 * - Membaca UID kartu RFID
 * - Membandingkan dengan daftar UID yang diizinkan
 * - Relay ON jika UID cocok (akses diterima)
 * 
 * Library yang diperlukan:
 * - MFRC522 by Miguel Balboa
 * 
 * Blynk Virtual Pin:
 * V1 = UID kartu yang terbaca
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "RFID RC522"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D8
#define RST_PIN D3
#define RELAY_PIN D0

MFRC522 mfrc522(SS_PIN, RST_PIN);

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

// Daftar UID kartu yang diizinkan (ganti dengan UID kartu Anda)
// Cara dapatkan UID: upload program, tempelkan kartu, baca di Serial Monitor
String authorizedUID1 = "AB CD EF 12 34";  // Kartu 1
String authorizedUID2 = "12 34 56 78 9A";  // Kartu 2

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  Serial.println("RFID RC522 Siap! Tempelkan kartu...");
}

void loop() {
  Blynk.run();
  
  // Cek apakah ada kartu baru
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Baca kartu
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  // Ambil UID kartu
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX);
    uid += " ";
  }
  uid.toUpperCase();
  
  // Kirim UID ke Blynk
  Blynk.virtualWrite(V1, uid);
  
  Serial.print("UID Kartu: ");
  Serial.println(uid);
  
  // Verifikasi akses
  if (uid == authorizedUID1 || uid == authorizedUID2) {
    digitalWrite(RELAY_PIN, HIGH);
    Blynk.virtualWrite(V10, 1);
    Blynk.logEvent("access_granted", "✅ Akses DITERIMA - Selamat datang!");
    Serial.println("✅ Akses DITERIMA! Relay ON selama 3 detik");
    delay(3000);
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V10, 0);
  } else {
    Blynk.logEvent("access_denied", "❌ Akses DITOLAK - Kartu tidak dikenal!");
    Serial.println("❌ Akses DITOLAK! Kartu tidak terdaftar");
  }
  
  // Hentikan pembacaan kartu
  mfrc522.PICC_HaltA();
  delay(1000);
}
