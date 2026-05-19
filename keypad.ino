/*
 * JUDUL: Keypad 4x4
 * FUNGSI: Input tombol matriks 4x4 (16 tombol)
 * PIN: D1-D8 (4 baris + 4 kolom)
 * RELAY: D0 (toggle dengan tombol '*' atau '#')
 * 
 * Library yang diperlukan:
 * - Keypad by Mark Stanley, Alexander Brevig
 * 
 * Blynk Virtual Pin:
 * V1 = Tombol yang ditekan
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Keypad 4x4"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Keypad.h>

#define RELAY_PIN D0

// Definisi keypad 4x4
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Pin untuk baris (rows)
byte rowPins[ROWS] = {D1, D2, D3, D4};
// Pin untuk kolom (cols)
byte colPins[COLS] = {D5, D6, D7, D8};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

bool relayState = false;
String pinCode = "";
const String correctPin = "1234";  // PIN yang benar

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  
  char key = keypad.getKey();
  
  if (key) {
    Blynk.virtualWrite(V1, key);
    Serial.print("Tombol ditekan: ");
    Serial.println(key);
    
    // Tombol * : toggle relay langsung
    if (key == '*') {
      relayState = !relayState;
      digitalWrite(RELAY_PIN, relayState);
      Blynk.virtualWrite(V10, relayState);
      Serial.print("Relay toggled: ");
      Serial.println(relayState ? "ON" : "OFF");
    }
    
    // Tombol # : reset PIN
    else if (key == '#') {
      pinCode = "";
      Serial.println("PIN direset");
    }
    
    // Tombol angka : untuk PIN
    else if (key >= '0' && key <= '9') {
      pinCode += key;
      Serial.print("PIN sementara: ");
      Serial.println(pinCode);
      
      // Cek PIN jika sudah 4 digit
      if (pinCode.length() == 4) {
        if (pinCode == correctPin) {
          relayState = !relayState;
          digitalWrite(RELAY_PIN, relayState);
          Blynk.virtualWrite(V10, relayState);
          Blynk.logEvent("pin_correct", "✅ PIN benar! Relay toggled");
          Serial.println("✅ PIN BENAR! Relay toggled");
        } else {
          Blynk.logEvent("pin_wrong", "❌ PIN salah!");
          Serial.println("❌ PIN SALAH!");
        }
        pinCode = "";
      }
    }
    
    // Tombol A, B, C, D untuk fungsi khusus
    else if (key == 'A') {
      digitalWrite(RELAY_PIN, HIGH);
      Blynk.virtualWrite(V10, 1);
      Serial.println("Tombol A: Relay ON");
    }
    else if (key == 'B') {
      digitalWrite(RELAY_PIN, LOW);
      Blynk.virtualWrite(V10, 0);
      Serial.println("Tombol B: Relay OFF");
    }
    else if (key == 'C') {
      Serial.println("Tombol C: Status relay");
      Serial.print("Relay saat ini: ");
      Serial.println(digitalRead(RELAY_PIN) ? "ON" : "OFF");
    }
    else if (key == 'D') {
      Serial.println("Tombol D: Tampilkan PIN yang dimasukkan");
      Serial.print("PIN: ");
      Serial.println(pinCode);
    }
  }
}
