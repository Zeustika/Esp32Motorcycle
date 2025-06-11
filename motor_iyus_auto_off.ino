#include "BluetoothSerial.h"
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

BluetoothSerial ESP_BT;
Adafruit_MPU6050 mpu;

int relay_pin_1 = 4; // Relay untuk kendaraan
int relay_pin_2 = 5; // Relay push button
int relay_pin_3 = 2; // Relay alarm

bool relayState1 = HIGH;
bool relayState2 = HIGH;
bool relayState3 = HIGH;

bool flashing = false;
unsigned long flashInterval = 100;
unsigned long previousMillis = 0;
bool ModeParkir = false;
bool nyalakamAlarm = false;
unsigned long waktuAlarm = 0;

void setup() {
  Serial.begin(19200);
  ESP_BT.begin("Motor_iyus");

  // Inisialisasi MPU6050
  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip. Continuing without MPU6050...");
  } else {
    Serial.println("MPU6050 successfully initialized!");
  }

  // Set pin relay sebagai output
  pinMode(relay_pin_1, OUTPUT);
  pinMode(relay_pin_2, OUTPUT);
  pinMode(relay_pin_3, OUTPUT);

  // Set semua relay dalam kondisi mati (HIGH)
  digitalWrite(relay_pin_1, HIGH);
  digitalWrite(relay_pin_2, HIGH);
  digitalWrite(relay_pin_3, HIGH);
}

void loop() {
  // Cek data dari Bluetooth
  if (ESP_BT.available()) {
    int incoming = ESP_BT.read();
    int button = floor(incoming / 10);
    int value = incoming % 10;

    switch (button) {
      case 1: // Tombol 1: Kendaraan hidup/mati
        Serial.print("Bluetooth Button 1: "); Serial.println(value);
        relayState1 = !value;
        digitalWrite(relay_pin_1, relayState1);
        break;
      case 2: // Tombol 2: Relay push-to-on
        Serial.print("Bluetooth Button 2: "); Serial.println(value);
        if (value == 1) {
          relayState2 = LOW;
          digitalWrite(relay_pin_2, LOW);
          delay(1000); // Relay aktif selama 1 detik
          relayState2 = HIGH;
          digitalWrite(relay_pin_2, HIGH);
        }
        break;
      case 3: // Tombol 3: Alarm berkedip
        Serial.print("Bluetooth Button 3: "); Serial.println(value);
        if (value == 1) {
          flashing = true;
        } else {
          flashing = false;
          digitalWrite(relay_pin_3, HIGH); // Matikan alarm
        }
        break;
      case 4: // Tombol 4: Mode parkir
        Serial.print("Parking Mode: "); Serial.println(value);
        ModeParkir = (value == 1);
        if (!ModeParkir) {
          nyalakamAlarm = false;
          digitalWrite(relay_pin_3, HIGH); // Matikan alarm jika mode parkir dimatikan
        }
        break;
    }
  }

  // Logika mematikan kendaraan jika Bluetooth terputus dan mode parkir tidak aktif
  if (!ESP_BT.hasClient() && !ModeParkir) {
    Serial.println("Bluetooth disconnected. Turning off the vehicle.");
    relayState1 = HIGH;
    relayState2 = HIGH;
    relayState3 = HIGH;
    digitalWrite(relay_pin_1, relayState1);
    digitalWrite(relay_pin_2, relayState2);
    digitalWrite(relay_pin_3, relayState3);
  }

  // Logika mode parkir
  if (ModeParkir) {
    sensors_event_t accel, gyro, temp;
    mpu.getEvent(&accel, &gyro, &temp);

    // Cetak nilai akselerasi untuk debugging
    Serial.print("Acceleration X: "); Serial.print(accel.acceleration.x);
    Serial.print("\tY: "); Serial.print(accel.acceleration.y);
    Serial.print("\tZ: "); Serial.println(accel.acceleration.z);

    // Deteksi pergerakan
    if (accel.acceleration.x > 10 || accel.acceleration.y > 1 || accel.acceleration.z > 10) {
      if (!nyalakamAlarm) {
        Serial.println("Movement detected! Activating alarm.");
        nyalakamAlarm = true;
        waktuAlarm = millis();
        digitalWrite(relay_pin_3, LOW); // Nyalakan alarm
      }
    }

    // Matikan alarm setelah 1 menit
    if (nyalakamAlarm && (millis() - waktuAlarm >= 15000)) {
      nyalakamAlarm = false;
      digitalWrite(relay_pin_3, HIGH); // Matikan alarm
    }
  }

  // Logika flashing alarm
  if (flashing) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= flashInterval) {
      previousMillis = currentMillis;
      relayState3 = !relayState3;
      digitalWrite(relay_pin_3, relayState3);
    }
  }
}
