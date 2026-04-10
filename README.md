# 🔐 RFID Access Control System

An ESP32-based access control system using RFID card scanning, with a servo-controlled lock, LCD display, LED indicators, and Bluetooth notifications.

---

## 📹 Demo Video

[![Demo Video](https://img.youtube.com/vi/wYxXUIIQQZ8/hqdefault.jpg)](https://youtu.be/wYxXUIIQQZ8)
> Click the thumbnail above to watch the project in action.

---

## ✨ Features

- RFID card reading via MFRC522
- Nokia 5110 LCD display (PCD8544)
- Servo motor to control door lock
- Green/Red LED indicators
- Bluetooth notifications via ESP32

---

## 🔧 Hardware

- ESP32
- MFRC522 RFID reader
- Nokia 5110 LCD (PCD8544)
- Servo motor
- Green and Red LEDs

---

## 📌 Pin Connections

| Component  | ESP32 Pin |
|------------|-----------|
| RFID SS    | 21        |
| RFID RST   | 22        |
| LCD DC     | 4         |
| LCD CS     | 15        |
| LCD RST    | 2         |
| Servo      | 13        |
| Green LED  | 16        |
| Red LED    | 17        |

---

## 📚 Libraries Required

- [MFRC522](https://github.com/miguelbalboa/rfid)
- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit PCD8544](https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library)
- [ESP32Servo](https://github.com/madhephaestus/ESP32Servo)
- BluetoothSerial *(included with ESP32 Arduino core)*

---

## ⚙️ How It Works

1. Scan an RFID card
2. If the UID matches an authorized card, the servo opens and the green LED turns on
3. Scan again to close — servo returns to 0° and red LED turns on
4. Unauthorized cards are rejected and the display shows **WRONG**
5. All access events are sent via Bluetooth

---

## 🚀 Setup

1. Install the required libraries in Arduino IDE
2. Replace the UID values in the code with your own card UIDs
3. Flash to your ESP32
4. Pair with `ESP32_BT` via Bluetooth to receive notifications
