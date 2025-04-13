#include "BluetoothSerial.h"

BluetoothSerial ESP_BT;

int relay_pin_1 = 4;
int relay_pin_2 = 5;
int relay_pin_3 = 2;

int rf_pin_1 = 27;
int rf_pin_2 = 26;
int rf_pin_3 = 25;

bool relayState1 = HIGH;
bool relayState2 = HIGH;
bool relayState3 = HIGH;

bool rfButton1State = HIGH;
bool rfButton2State = HIGH;
bool rfButton3State = HIGH;

bool flashing = false;
unsigned long flashInterval = 150;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(19200);
  ESP_BT.begin("Motor_iyus");

  pinMode(relay_pin_1, OUTPUT);
  pinMode(relay_pin_2, OUTPUT);
  pinMode(relay_pin_3, OUTPUT);

  pinMode(rf_pin_1, INPUT);
  pinMode(rf_pin_2, INPUT);
  pinMode(rf_pin_3, INPUT);

  digitalWrite(relay_pin_1, HIGH);
  digitalWrite(relay_pin_2, HIGH);
  digitalWrite(relay_pin_3, HIGH);
}

void loop() {
  if (!ESP_BT.hasClient()) {
    if (relayState1 != HIGH || relayState2 != HIGH || relayState3 != HIGH) {
      Serial.println("Tidak ada koneksi");
      relayState1 = HIGH;
      relayState2 = HIGH;
      relayState3 = HIGH;
      digitalWrite(relay_pin_1, relayState1);
      digitalWrite(relay_pin_2, relayState2);
      digitalWrite(relay_pin_3, relayState3);
    }
  } else {
    if (ESP_BT.available()) {
      int incoming = ESP_BT.read();
      int button = floor(incoming / 10);
      int value = incoming % 10;

      switch (button) {
        case 1:
          Serial.print("Bluetooth Button 1:"); Serial.println(value);
          relayState1 = !value;
          digitalWrite(relay_pin_1, relayState1);
          break;
        case 2:
          Serial.print("Bluetooth Button 2:"); Serial.println(value);
          if (value == 1) {
            relayState2 = LOW;
            digitalWrite(relay_pin_2, LOW);
            delay(1000);
            relayState2 = HIGH;
            digitalWrite(relay_pin_2, HIGH);
          }
          break;
        case 3:
          Serial.print("Bluetooth Button 3:"); Serial.println(value);
          if (value == 1) {
            flashing = true;
          } else {
            flashing = false;
            digitalWrite(relay_pin_3, HIGH);
          }
          break;
      }
    }
  }

  if (digitalRead(rf_pin_1) == HIGH && rfButton1State == HIGH) {
    Serial.println("RF Button 1 clicked");
    relayState1 = !relayState1;
    digitalWrite(relay_pin_1, relayState1);
    rfButton1State = LOW;
    delay(300);
  } else if (digitalRead(rf_pin_1) == LOW && rfButton1State == LOW) {
    rfButton1State = HIGH;
  }

  if (digitalRead(rf_pin_2) == HIGH && rfButton2State == HIGH) {
    Serial.println("RF Button 2 clicked");
    relayState2 = LOW;
    digitalWrite(relay_pin_2, LOW);
    delay(1000);
    relayState2 = HIGH;
    digitalWrite(relay_pin_2, HIGH);
    rfButton2State = LOW;
    delay(300);
  } else if (digitalRead(rf_pin_2) == LOW && rfButton2State == LOW) {
    rfButton2State = HIGH;
  }

  if (digitalRead(rf_pin_3) == HIGH && rfButton3State == HIGH) {
    Serial.println("RF Button 3 clicked");
    flashing = !flashing;
    rfButton3State = LOW;
    delay(300);
  } else if (digitalRead(rf_pin_3) == LOW && rfButton3State == LOW) {
    rfButton3State = HIGH;
  }

  if (flashing) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= flashInterval) {
      previousMillis = currentMillis;
      relayState3 = !relayState3;
      digitalWrite(relay_pin_3, relayState3);
    }
  }
}
