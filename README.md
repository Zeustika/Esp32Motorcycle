## 🏍️ ESP32 Smart Motorcycle System with Auto-Off & Anti-Theft

This project is a smart motorcycle security and control system based on the **ESP32 microcontroller**. It features **Bluetooth control**, **multi-mode relay activation**, and an **anti-theft system** that triggers an alarm if the vehicle is moved while in parking mode.

---

### 🔧 Features

- 🔌 **3 Relay Control Modes**  
  - **Relay 1 (ON/OFF toggle)**  
  - **Relay 2 (Push-to-ON, active while pressed)**  
  - **Relay 3 (Toggle + Auto-off after a delay + Alarm mode)**

- 📱 **Bluetooth Control** via MIT App Inventor
- 🅿️ **Parking Mode Detection**  
  If the Bluetooth connection is lost, the system enters parking mode and watches for movement.
- 🚨 **Anti-Theft Alarm**  
  If movement is detected during parking mode (via MPU-6050), the alarm relay is triggered for 1 minute.
- 🔋 **Auto-Off Function**  
  Relay 3 automatically turns off after a set duration if no action is taken.

---

### 🧰 Hardware Requirements

| Component         | Description                            |
|------------------|----------------------------------------|
| ESP32            | ESP32-WROOM-32D module                 |
| 3-Channel Relay  | To control multiple electrical loads   |
| MPU-6050         | Accelerometer & gyroscope module       |
| Passive Buzzer   | For audible alarm                      |
| Status LED       | For visual feedback                    |
| Android Phone    | For Bluetooth control via app          |

---

### ⚡ Wiring Diagram

```
ESP32-WROOM-32D
+--------------------------+
| GPIO 13 -> RELAY_1       |
| GPIO 12 -> RELAY_2       |
| GPIO 14 -> RELAY_3       |
| GPIO 27 -> STATUS LED    |
| GPIO 21 (SDA) -> MPU6050 |
| GPIO 22 (SCL) -> MPU6050 |
| GND      -> All modules  |
| 3.3V/5V  -> MPU6050, etc |
+--------------------------+
```
![WhatsApp Image 2024-11-24 at 13 51 36_5bef2cc3](https://github.com/user-attachments/assets/d040a750-c320-429e-a4d9-f8c8f1424160)


*(Make sure relays are powered separately if needed depending on current)*

---

### 🚀 How to Use

#### 1. Upload the Code

Flash `motor_iyus_auto_off.ino` to your ESP32 using Arduino IDE or PlatformIO.

#### 2. Connect the Hardware

- Wire the relays, LED, buzzer, and MPU-6050 according to the diagram above.
- Ensure ESP32 has a stable 5V power supply.

#### 3. Build the Android App

- Use **MIT App Inventor** to create an app with **3 buttons**:
  - Button 1: Toggle Relay 1
  - Button 2: Momentary Push Relay 2
  - Button 3: Toggle Relay 3 + enable auto-off + alarm
  
*(I can help design the UI if needed!)*

#### 4. Pair Phone via Bluetooth

- Connect your Android phone via Bluetooth to the ESP32 module.
- Control the system using the app.

#### 5. Auto-Off and Alarm

- When Relay 3 is turned ON, a timer begins.
- If Bluetooth disconnects (simulating parking), system enters **parking mode**.
- If movement is detected by MPU-6050, the alarm will activate for 1 minute.

---

### 📌 Notes

- The system is designed to continue functioning after Bluetooth disconnect.
- You can modify the delay time for auto-off or alarm duration in the code.
- Always ensure power safety when connecting to real motorcycle circuits.

### 📌 Credits
- fauzan
- harpan
- samith
- raden iqbal
- falgan
