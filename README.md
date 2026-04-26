# Smart IoT Real-Time Information Display System

## Developed by Roshan Chavan

An IoT-based real-time information display system using ESP32, MAX7219 LED Matrix, DS3231 RTC Module, and DHT22 Sensor. This project displays custom text, real-time clock, date, temperature, and humidity on a 32x8 LED matrix display and allows full control through a WiFi-based web interface.

---

## Project Overview

This project is designed to create a smart embedded display system for real-time information monitoring.

The system uses:

- ESP32 for processing and WiFi connectivity
- MAX7219 4-in-1 LED Matrix for display output
- DS3231 RTC Module for accurate time and date
- DHT22 Sensor for temperature and humidity monitoring

Users can connect to the ESP32 hotspot and open a web page to:

- Change custom scrolling text
- Set date and time
- Select 12-hour or 24-hour clock format
- Adjust display brightness (intensity)

All settings are saved permanently using ESP32 Preferences memory, so data remains محفوظ even after power OFF and ON.

---

## Features

### Real-Time Clock Display
- Displays current time using DS3231 RTC
- Supports both 12-hour and 24-hour format
- RTC backup battery keeps time saved even after power loss

### Date Display
- Automatically scrolls current date

### Temperature Monitoring
- Reads live temperature from DHT22

### Humidity Monitoring
- Reads live humidity from DHT22

### Custom Scrolling Text
- User can update display message from web browser

### WiFi Web Server Control
- ESP32 works in Access Point (AP) mode
- No external router required
- Mobile can connect directly to ESP32

### Display Intensity Control
- Brightness can be adjusted from webpage

### Permanent Memory Storage
- Settings are saved using Preferences.h
- Custom text, brightness, and time format remain saved after restart

---

## Hardware Components Used

| Component | Quantity |
|---|---:|
| ESP32 Dev Board (30 Pin) | 1 |
| MAX7219 8x32 LED Matrix | 1 |
| DS3231 RTC Module | 1 |
| DHT22 Sensor | 1 |
| Jumper Wires | As required |
| Power Supply / USB Cable | 1 |

---

## Pin Connections

### MAX7219 to ESP32

| MAX7219 | ESP32 |
|---|---|
| VCC | 5V |
| GND | GND |
| DIN | GPIO 23 |
| CS | GPIO 5 |
| CLK | GPIO 18 |

---

### DS3231 RTC to ESP32

| DS3231 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

### DHT22 to ESP32

| DHT22 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO 4 |

---

## Working Principle

### Step 1 — Power ON

ESP32 starts in AP (Access Point) mode and creates its own WiFi hotspot:

Embedded_With_Roshan

---

### Step 2 — User Connects Mobile

User connects mobile phone to ESP32 WiFi and opens browser using:

192.168.4.1

---

### Step 3 — Web Dashboard Opens

User can:

- Set custom display text
- Set date and time
- Select time format
- Adjust brightness

---

### Step 4 — Data Displayed on LED Matrix

The LED matrix shows:

1. Custom scrolling text
2. Current time
3. Current date
4. Temperature
5. Humidity

in continuous loop.

---

### Step 5 — Permanent Saving

All settings are stored in ESP32 Preferences memory and remain saved after restart.

---

## Software Used

- Arduino IDE
- Embedded C++
- ESP32 Board Package
- Required Libraries:
  - WiFi.h
  - WebServer.h
  - MD_Parola.h
  - MD_MAX72xx.h
  - RTClib.h
  - DHT.h
  - Preferences.h

---

## Installation Steps

### Step 1

Install Arduino IDE

---

### Step 2

Install ESP32 Board Package

---

### Step 3

Install Required Libraries from Library Manager

---

### Step 4

Upload code to ESP32

---

### Step 5

Open Serial Monitor and note IP Address

Usually:

192.168.4.1

---

### Step 6

Connect mobile to ESP32 WiFi

SSID:

Embedded_With_Roshan

Password:

12345678

---

### Step 7

Open browser and access:

http://192.168.4.1

---

## Applications

- Smart Notice Board
- Office Information Display
- College Project Demonstration
- Industrial Monitoring Display
- Environmental Monitoring
- IoT Dashboard
- Embedded Systems Portfolio Project

---

## Future Improvements

- Add weather API support
- Add OLED display support
- Add mobile app control
- Add MQTT cloud monitoring
- Add Google Assistant integration
- Add voice control
- Add multiple display modes
- Add alarm and notification system

---

## Conclusion

This project demonstrates the practical implementation of Embedded Systems, IoT, Sensors, Real-Time Clock management, Web Server development, and persistent memory storage using ESP32.

It is highly useful for resume building, GitHub portfolio, LinkedIn showcase, and technical interviews in Embedded Systems and IoT domains.

---

## Author

### Roshan Chavan

Embedded Systems Engineer  
Electronics and Telecommunication Engineer

---

## GitHub Repository

Add your GitHub repository link here after upload.

Example:

https://github.com/RoshanWithEmbedded/smart-iot-real-time-display-system
