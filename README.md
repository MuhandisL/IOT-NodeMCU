# 🚀 NodeMCU ESP8266 - 25 Sensor dengan Blynk & Relay Control

![NodeMCU](https://img.shields.io/badge/NodeMCU-ESP8266-blue)
![Blynk](https://img.shields.io/badge/Blynk-IoT-green)
![Arduino](https://img.shields.io/badge/Arduino-IDE-cyan)
![License](https://img.shields.io/badge/License-MIT-yellow)

> **Proyek lengkap 25 sensor/aktuator** yang terhubung ke NodeMCU ESP8266, dengan integrasi Blynk IoT dan kontrol 1 channel relay (Pin D0).

---

### 📁 Sensor Analog (Pin A0)

| No | Sensor | File Kode (.ino) | Deskripsi Singkat |
|----|--------|------------------|-------------------|
| 1 | LDR (Cahaya) | [`ldr.ino`](ldr.ino) | Membaca intensitas cahaya, relay ON saat gelap |
| 2 | Potensiometer | [`potensiometer.ino`](potensiometer.ino) | Membaca resistansi manual, relay ON saat >512 |
| 3 | Soil Moisture | [`soil_moisture.ino`](soil_moisture.ino) | Kelembaban tanah, relay ON saat kering (pompa) |
| 4 | MQ-2 Gas | [`mq2_gas.ino`](mq2_gas.ino) | Deteksi gas berbahaya, relay ON + notifikasi |
| 19 | Rain Sensor | [`rain_sensor.ino`](rain_sensor.ino) | Deteksi hujan, relay ON untuk penutup jemuran |
| 21 | Sound Sensor | [`sound_sensor.ino`](sound_sensor.ino) | Deteksi suara, toggle relay dengan tepuk tangan |

---

### 📁 Sensor Digital (Input)

| No | Sensor | File Kode (.ino) | Deskripsi Singkat |
|----|--------|------------------|-------------------|
| 5 | Flame Sensor | [`flame_sensor.ino`](flame_sensor.ino) | Deteksi api, respon cepat, relay ON + alarm |
| 6 | PIR Motion | [`pir_motion.ino`](pir_motion.ino) | Deteksi gerakan, relay ON 5 detik |
| 7 | Push Button | [`push_button.ino`](push_button.ino) | Input tombol manual, toggle relay |
| 20 | IR Obstacle | [`ir_obstacle.ino`](ir_obstacle.ino) | Deteksi penghalang, relay ON 500ms |
| 22 | Touch Sensor | [`touch_sensor.ino`](touch_sensor.ino) | Sensor sentuh kapasitif, toggle relay |

---

### 📁 Aktuator (Output)

| No | Aktuator | File Kode (.ino) | Deskripsi Singkat |
|----|----------|------------------|-------------------|
| 8 | Buzzer | [`buzzer.ino`](buzzer.ino) | Menghasilkan suara alarm, relay menyala bersamaan |
| 9 | LED | [`led.ino`](led.ino) | Output cahaya, relay mengikuti status LED |
| 10 | Relay Module | [`relay_module.ino`](relay_module.ino) | Kontrol perangkat listrik (butuh level shifter) |
| 23 | Servo Motor | [`servo.ino`](servo.ino) | Penggerak sudut 0-180°, relay ON saat bergerak |
| 24 | RGB LED | [`rgb_led.ino`](rgb_led.ino) | LED warna (R,G,B), relay ON saat menyala |

---

### 📁 Sensor Lingkungan (Digital 1-Wire)

| No | Sensor | File Kode (.ino) | Deskripsi Singkat |
|----|--------|------------------|-------------------|
| 11 | DHT11 | [`dht11.ino`](dht11.ino) | Suhu & kelembaban, relay ON saat suhu >30°C |
| 12 | DHT22 | [`dht22.ino`](dht22.ino) | Suhu & kelembaban (akurat), relay ON saat suhu >30°C |
| 13 | Ultrasonic HC-SR04 | [`ultrasonic.ino`](ultrasonic.ino) | Pengukur jarak (cm), relay ON saat jarak <20cm |

---

### 📁 Sensor I2C

| No | Sensor | File Kode (.ino) | Deskripsi Singkat |
|----|--------|------------------|-------------------|
| 15 | OLED Display | [`oled.ino`](oled.ino) | Display grafis 128x64, tampilkan data sensor |
| 16 | LCD I2C | [`lcd.ino`](lcd.ino) | Display teks 16x2, tampilkan status relay |
| 17 | MPU6050 | [`mpu6050.ino`](mpu6050.ino) | Gyro + Accelerometer, relay ON saat goncangan |
| 18 | BMP280 | [`bmp280.ino`](bmp280.ino) | Tekanan udara & suhu, relay ON saat tekanan turun |

---

### 📁 Komunikasi Khusus

| No | Sensor | File Kode (.ino) | Deskripsi Singkat |
|----|--------|------------------|-------------------|
| 14 | RFID RC522 | [`rfid.ino`](rfid.ino) | Pembaca kartu RFID (SPI), relay ON 3 detik jika valid |
| 25 | Keypad 4x4 | [`keypad.ino`](keypad.ino) | Input matriks 16 tombol, toggle relay dengan * atau PIN |

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

