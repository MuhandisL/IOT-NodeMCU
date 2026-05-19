# 🚀 NodeMCU ESP8266 - 25 Sensor dengan Blynk & Relay Control

![NodeMCU](https://img.shields.io/badge/NodeMCU-ESP8266-blue)
![Blynk](https://img.shields.io/badge/Blynk-IoT-green)
![Arduino](https://img.shields.io/badge/Arduino-IDE-cyan)
![License](https://img.shields.io/badge/License-MIT-yellow)

> **Proyek lengkap 25 sensor/aktuator** yang terhubung ke NodeMCU ESP8266, dengan integrasi Blynk IoT dan kontrol 1 channel relay (Pin D0).

---

## 📌 DAFTAR ISI (Klik Langsung ke File Kode)

### 📁 Sensor Analog (Pin A0)

| No | Sensor | File Kode (.ino) | Deskripsi Singkat |
|----|--------|------------------|-------------------|
| 1 | LDR (Cahaya) | [`01_LDR/ldr.ino`](01_LDR/ldr.ino) | Membaca intensitas cahaya, relay ON saat gelap |
| 2 | Potensiometer | [`02_Potensiometer/potensiometer.ino`](02_Potensiometer/potensiometer.ino) | Membaca resistansi manual, relay ON saat >512 |
| 3 | Soil Moisture | [`03_Soil_Moisture/soil_moisture.ino`](03_Soil_Moisture/soil_moisture.ino) | Kelembaban tanah, relay ON saat kering (pompa) |
| 4 | MQ-2 Gas | [`04_MQ2_Gas/mq2_gas.ino`](04_MQ2_Gas/mq2_gas.ino) | Deteksi gas berbahaya, relay ON + notifikasi |
| 19 | Rain Sensor | [`19_Rain_Sensor/rain_sensor.ino`](19_Rain_Sensor/rain_sensor.ino) | Deteksi hujan, relay ON untuk penutup jemuran |
| 21 | Sound Sensor | [`21_Sound_Sensor/sound_sensor.ino`](21_Sound_Sensor/sound_sensor.ino) | Deteksi suara, toggle relay dengan tepuk tangan |

---

### 📁 Sensor Digital (Input)

| No | Sensor | File Kode (.ino) | Deskripsi Singkat |
|----|--------|------------------|-------------------|
| 5 | Flame Sensor | [`05_Flame_Sensor/flame_sensor.ino`](05_Flame_Sensor/flame_sensor.ino) | Deteksi api, respon cepat, relay ON + alarm |
| 6 | PIR Motion | [`06_PIR_Motion/pir_motion.ino`](06_PIR_Motion/pir_motion.ino) | Deteksi gerakan, relay ON 5 detik |
| 7 | Push Button | [`07_Push_Button/push_button.ino`](07_Push_Button/push_button.ino) | Input tombol manual, toggle relay |
| 20 | IR Obstacle | [`20_IR_Obstacle/ir_obstacle.ino`](20_IR_Obstacle/ir_obstacle.ino) | Deteksi penghalang, relay ON 500ms |
| 22 | Touch Sensor | [`22_Touch_Sensor/touch_sensor.ino`](22_Touch_Sensor/touch_sensor.ino) | Sensor sentuh kapasitif, toggle relay |

---

### 📁 Aktuator (Output)

| No | Aktuator | File Kode (.ino) | Deskripsi Singkat |
|----|----------|------------------|-------------------|
| 8 | Buzzer | [`08_Buzzer/buzzer.ino`](08_Buzzer/buzzer.ino) | Menghasilkan suara alarm, relay menyala bersamaan |
| 9 | LED | [`09_LED/led.ino`](09_LED/led.ino) | Output cahaya, relay mengikuti status LED |
| 10 | Relay Module | [`10_Relay_Module/relay_module.ino`](10_Relay_Module/relay_module.ino) | Kontrol perangkat listrik (butuh level shifter) |
| 23 | Servo Motor | [`23_Servo/servo.ino`](23_Servo/servo.ino) | Penggerak sudut 0-180°, relay ON saat bergerak |
| 24 | RGB LED | [`24_RGB_LED/rgb_led.ino`](24_RGB_LED/rgb_led.ino) | LED warna (R,G,B), relay ON saat menyala |

---

### 📁 Sensor Lingkungan (Digital 1-Wire)

| No | Sensor | File Kode (.ino) | Deskripsi Singkat |
|----|--------|------------------|-------------------|
| 11 | DHT11 | [`11_DHT11/dht11.ino`](11_DHT11/dht11.ino) | Suhu & kelembaban, relay ON saat suhu >30°C |
| 12 | DHT22 | [`12_DHT22/dht22.ino`](12_DHT22/dht22.ino) | Suhu & kelembaban (akurat), relay ON saat suhu >30°C |
| 13 | Ultrasonic HC-SR04 | [`13_Ultrasonic/ultrasonic.ino`](13_Ultrasonic/ultrasonic.ino) | Pengukur jarak (cm), relay ON saat jarak <20cm |

---

### 📁 Sensor I2C

| No | Sensor | File Kode (.ino) | Deskripsi Singkat |
|----|--------|------------------|-------------------|
| 15 | OLED Display | [`15_OLED/oled.ino`](15_OLED/oled.ino) | Display grafis 128x64, tampilkan data sensor |
| 16 | LCD I2C | [`16_LCD/lcd.ino`](16_LCD/lcd.ino) | Display teks 16x2, tampilkan status relay |
| 17 | MPU6050 | [`17_MPU6050/mpu6050.ino`](17_MPU6050/mpu6050.ino) | Gyro + Accelerometer, relay ON saat goncangan |
| 18 | BMP280 | [`18_BMP280/bmp280.ino`](18_BMP280/bmp280.ino) | Tekanan udara & suhu, relay ON saat tekanan turun |

---

### 📁 Komunikasi Khusus

| No | Sensor | File Kode (.ino) | Deskripsi Singkat |
|----|--------|------------------|-------------------|
| 14 | RFID RC522 | [`14_RFID/rfid.ino`](14_RFID/rfid.ino) | Pembaca kartu RFID (SPI), relay ON 3 detik jika valid |
| 25 | Keypad 4x4 | [`25_Keypad/keypad.ino`](25_Keypad/keypad.ino) | Input matriks 16 tombol, toggle relay dengan * atau PIN |

---

## 📌 DAFTAR ISI (Klik Langsung ke File Kode)

- [1. LDR (Cahaya)](ldr.ino) - Sensor cahaya analog
- [2. Potensiometer](potensiometer.ino) - Pembaca resistansi manual
- [3. Soil Moisture](soil_moisture.ino) - Kelembaban tanah
- [4. MQ-2 Gas Sensor](mq2_gas.ino) - Deteksi gas berbahaya
- [5. Flame Sensor](flame_sensor.ino) - Deteksi api
- [6. PIR Motion Sensor](pir_motion.ino) - Deteksi gerakan
- [7. Push Button](push_button.ino) - Input tombol manual
- [8. Buzzer](buzzer.ino) - Alarm suara
- [9. LED](led.ino) - Output cahaya
- [10. Relay Module](relay_module.ino) - Kontrol perangkat listrik
- [11. DHT11](dht11.ino) - Suhu & kelembaban
- [12. DHT22](dht22.ino) - Suhu & kelembaban (akurat)
- [13. Ultrasonic HC-SR04](ultrasonic.ino) - Pengukur jarak
- [14. RFID RC522](rfid.ino) - Pembaca kartu RFID
- [15. OLED I2C](oled.ino) - Display grafis
- [16. LCD I2C](lcd.ino) - Display teks
- [17. MPU6050](mpu6050.ino) - Gyro & accelerometer
- [18. BMP280](bmp280.ino) - Tekanan udara
- [19. Rain Sensor](rain_sensor.ino) - Deteksi hujan
- [20. IR Obstacle Sensor](ir_obstacle.ino) - Deteksi penghalang
- [21. Sound Sensor](sound_sensor.ino) - Deteksi suara (clap switch)
- [22. Touch Sensor](touch_sensor.ino) - Sensor sentuh
- [23. Servo Motor](servo.ino) - Penggerak sudut
- [24. RGB LED](rgb_led.ino) - LED warna
- [25. Keypad 4x4](keypad.ino) - Input matriks tombol

