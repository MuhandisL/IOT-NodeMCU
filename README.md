# 🚀 NodeMCU ESP8266 - 25 Sensor dengan Blynk & Relay Control

![NodeMCU](https://img.shields.io/badge/NodeMCU-ESP8266-blue)
![Blynk](https://img.shields.io/badge/Blynk-IoT-green)
![Arduino](https://img.shields.io/badge/Arduino-IDE-cyan)
![License](https://img.shields.io/badge/License-MIT-yellow)

> **Proyek lengkap 25 sensor/aktuator** yang terhubung ke NodeMCU ESP8266, dengan integrasi Blynk IoT dan kontrol 1 channel relay.

---

## 📌 Daftar Isi
- [Tentang Proyek](#-tentang-proyek)
- [Daftar Sensor](#-daftar-sensor)
- [Pin Configuration](#-pin-configuration-nodeMCU)
- [Persiapan Awal](#-persiapan-awal)
- [Kode & Penjelasan 25 Sensor](#-kode--penjelasan-25-sensor)
  - [1. LDR (Cahaya)](ldr.ino)
  - [2. Potensiometer](#2-potensiometer)
  - [3. Soil Moisture (Kelembaban Tanah)](#3-soil-moisture-sensor)
  - [4. MQ-2 Gas Sensor](#4-mq-2-gas-sensor)
  - [5. Flame Sensor (Api)](#5-flame-sensor)
  - [6. PIR Motion Sensor](#6-pir-motion-sensor)
  - [7. Push Button](#7-push-button)
  - [8. Buzzer](#8-buzzer)
  - [9. LED](#9-led)
  - [10. Relay Module](#10-relay-module)
  - [11. DHT11 (Suhu & Kelembaban)](#11-dht11-sensor)
  - [12. DHT22 (Akurat)](#12-dht22-sensor)
  - [13. Ultrasonic HC-SR04](#13-ultrasonic-hc-sr04)
  - [14. RFID RC522](#14-rfid-rc522)
  - [15. OLED I2C Display](#15-oled-i2c-display)
  - [16. LCD I2C Display](#16-lcd-i2c-display)
  - [17. MPU6050 (Gyro + Accelerometer)](#17-mpu6050-sensor)
  - [18. BMP280 (Tekanan Udara)](#18-bmp280-sensor)
  - [19. Rain Sensor (Hujan)](#19-rain-sensor)
  - [20. IR Obstacle Sensor](#20-ir-obstacle-sensor)
  - [21. Sound Sensor (Suara)](#21-sound-sensor)
  - [22. Touch Sensor](#22-touch-sensor)
  - [23. Servo Motor](#23-servo-motor)
  - [24. RGB LED](#24-rgb-led)
  - [25. Keypad 4x4](#25-keypad-4x4)
- [Setup Blynk](#-setup-blynk)
- [Troubleshooting](#-troubleshooting)
- [Lisensi](#-lisensi)

---

## 📖 Tentang Proyek

Proyek ini berisi **kode lengkap dan penjelasan** untuk 25 sensor/aktuator yang dapat dihubungkan ke **NodeMCU ESP8266**. Setiap sensor memiliki:

- ✅ Kode Arduino yang siap pakai
- ✅ Penjelasan cara kerja kode
- ✅ Integrasi dengan **Blynk IoT Platform**
- ✅ Kontrol **1 channel relay** berdasarkan pembacaan sensor
- ✅ Virtual Pin mapping untuk Blynk

### ⚠️ Catatan Penting
- NodeMCU hanya memiliki **1 pin analog (A0)**
- Untuk menggunakan banyak sensor analog, perlu **external ADC** (misal ADS1115)
- Relay 5V membutuhkan **level shifter** dari 3.3V NodeMCU

---

## 📋 Daftar Sensor

| No | Sensor | Jenis Data | Pin NodeMCU | Blynk VPin Data | VPin Relay |
|----|--------|------------|-------------|-----------------|------------|
| 1 | LDR | Analog | A0 | V1 | V10 |
| 2 | Potensiometer | Analog | A0 | V1 | V10 |
| 3 | Soil Moisture | Analog | A0 | V1, V2 | V10 |
| 4 | MQ-2 Gas | Analog/Digital | A0/D1 | V1, V2 | V10 |
| 5 | Flame Sensor | Digital | D2 | V1 | V10 |
| 6 | PIR Motion | Digital | D3 | V1 | V10 |
| 7 | Push Button | Digital | D4 | V1 | V10 |
| 8 | Buzzer | Output | D5 | - | V10 |
| 9 | LED | Output | D6 | - | V10 |
| 10 | Relay Module | Output | D1/D2 | V2 | V1 |
| 11 | DHT11 | Digital | D4 | V5, V6 | V10 |
| 12 | DHT22 | Digital | D4 | V5, V6 | V10 |
| 13 | Ultrasonic | Digital | D5, D6 | V1, V2 | V10 |
| 14 | RFID RC522 | SPI | D5-D8 | V1 | V10 |
| 15 | OLED I2C | I2C | D1, D2 | - | - |
| 16 | LCD I2C | I2C | D1, D2 | - | - |
| 17 | MPU6050 | I2C | D1, D2 | V1 | V10 |
| 18 | BMP280 | I2C | D1, D2 | V1, V2 | V10 |
| 19 | Rain Sensor | Analog/Digital | A0/D3 | V1, V2 | V10 |
| 20 | IR Obstacle | Digital | D7 | V1 | V10 |
| 21 | Sound Sensor | Analog/Digital | A0/D2 | V1, V2 | V10 |
| 22 | Touch Sensor | Digital | D5 | V1 | V10 |
| 23 | Servo Motor | PWM | D4 | V1 | V10 |
| 24 | RGB LED | PWM | D1,D2,D3 | V1 | V10 |
| 25 | Keypad 4x4 | Digital | D1-D8 | V1 | V10 |

---






## 🔌 Pin Configuration NodeMCU
