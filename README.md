🏍️ ESP32 Smart Motorcycle System
This project is an ESP32-based motorcycle security and control system designed to enhance the safety and convenience of two-wheel vehicles using Bluetooth connectivity and motion detection.

🔧 Key Features
🔌 3-Channel Relay Control

Relay 1: Toggle ON/OFF

Relay 2: Push-to-ON (active only while the button is pressed)

Relay 3: Toggle alarm state

📱 Bluetooth App Control
Built using MIT App Inventor, allowing full control of the motorcycle system via an Android smartphone.

🅿️ Automatic Parking Mode
If the Bluetooth connection is lost, the system automatically enters parking mode. If motion is detected while in parking mode, an alarm will be triggered for 1 minute.

🧠 Movement Detection with MPU-6050
The system uses a gyroscope and accelerometer to detect suspicious movement or changes in position.

🔔 Anti-Theft Alarm System
Relay 3 activates a passive buzzer to function as a loud audible alarm when needed.

🧰 Components Used
ESP32-WROOM-32D

3x Relay Module

Passive Buzzer

MPU-6050 Motion Sensor

Android Smartphone with Bluetooth

💡 Project Goal
To provide an affordable and effective way to improve motorcycle security using IoT and automation, making personal transportation smarter and safer.
