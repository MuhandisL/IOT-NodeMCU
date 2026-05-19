/*
 * JUDUL: Servo Motor
 * FUNGSI: Menggerakkan sudut servo (0-180 derajat)
 * PIN: D4 (PWM)
 * RELAY: D0 (aktif saat servo bergerak)
 * 
 * Library yang diperlukan:
 * - Servo (built-in Arduino)
 * 
 * Blynk Virtual Pin:
 * V1 = Kontrol sudut servo (slider 0-180)
 * V10 = Status relay
 */

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Servo Motor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

#define SERVO_PIN D4
#define RELAY_PIN D0

Servo myservo;
char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

int currentAngle = 90;

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  myservo.attach(SERVO_PIN);
  myservo.write(90);  // Posisi tengah
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}

// Kontrol dari Blynk Slider (0-180)
BLYNK_WRITE(V1) {
  int angle = param.asInt();
  currentAngle = angle;
  
  // Nyalakan relay saat servo bergerak
  digitalWrite(RELAY_PIN, HIGH);
  Blynk.virtualWrite(V10, 1);
  
  myservo.write(angle);
  Serial.print("Servo bergerak ke sudut: ");
  Serial.println(angle);
  
  delay(500);  // Biarkan servo bergerak
  digitalWrite(RELAY_PIN, LOW);
  Blynk.virtualWrite(V10, 0);
}

// Auto sweep (opsional)
void autoSweep() {
  for (int angle = 0; angle <= 180; angle++) {
    myservo.write(angle);
    delay(15);
  }
  for (int angle = 180; angle >= 0; angle--) {
    myservo.write(angle);
    delay(15);
  }
}
