# SolarTrace - Week 4 Progress Report
## UbuntuNet Alliance Women Hackathon 2026

**Project:** SolarTrace - Smart IoT-Connected Solar Cooker  
**Team:** Reffgga Repent Ritti, Clementina Agiu Gual Koch, Abuk Santino Garang Chan  
**Report Period:** Week 4 (August 8-14, 2026)  
**Date:** August 14, 2026

---

## 1. Executive Summary

This report documents the progress made during Week 4 (August 8-14, 2026) of the SolarTrace project development. The team focused on component testing, software development, and initial system integration. Significant progress was made in firmware implementation, sensor calibration, and communication protocols. 

**Note:** This week also marked a team composition change with Reffgga Repent Ritti joining as Lead Developer, replacing Alek Madut Malual who stepped down due to personal circumstances. The transition has been smooth as Reffgga was already familiar with the project from behind-the-scenes contributions.

---

## 2. Component Testing

### 2.1 Individual Component Tests

| Component | Test Conducted | Result | Remarks |
|-----------|---------------|--------|---------|
| ESP32 | WiFi scan, GPIO test, power consumption | PASS | All pins functional, WiFi stable |
| Servo Motor | Range of motion, torque test | PASS | 0-180 degree movement smooth |
| Temperature Sensor | Reading verification, accuracy test | PASS | +/- 0.5 degree Celsius accuracy |
| RTC Module | Time keeping, I2C communication | PASS | Time maintained after power cycle |
| LCD Module | Display test, contrast adjustment | PASS | All characters visible |
| Push Button | Debounce test, interrupt trigger | PASS | No false triggers |
| Solar Panels | Voltage output, current test | PASS | 50W output verified |
| Charge Controller | Charging test, voltage regulation | PASS | Stable output at 13.8V |
| Battery | Voltage test, charge retention | PASS | 12.8V, holding charge |
| Micro SD Module | Read/Write test, file system check | PASS | FAT32 formatted, read/write OK |

### 2.2 Sensor Calibration

| Sensor | Calibration Method | Result | Tolerance |
|--------|-------------------|--------|-----------|
| Temperature Sensor | Ice bath (0°C) + Boiling water (100°C) | Calibrated | +/- 0.5°C |
| RTC | NTP time sync | Synced | < 1 sec deviation |
| Battery Voltage | Multimeter comparison | Verified | +/- 0.1V |
| Servo Position | PWM mapping calibration | Verified | +/- 1 degree accuracy |

---

## 3. Software Development

### 3.1 Development Environment Setup

| Tool | Version | Status |
|------|---------|--------|
| Arduino IDE | 2.3.2 | Configured |
| ESP32 Board Package | 2.0.17 | Installed |
| Blynk Library | 1.1.0 | Installed |
| RTClib | 2.1.4 | Installed |
| LiquidCrystal I2C | 1.1.4 | Installed |
| SD Library | 2.0.0 | Installed |
| GitHub Desktop | Latest | Configured |

### 3.2 Code Modules Developed

#### 3.2.1 WiFi Connection Module
- WiFi connection with SSID and password
- Auto-reconnect on disconnection
- Connection status monitoring
- LED indicator for connection state

#### 3.2.2 Blynk Integration Module
- Blynk cloud connection
- Widget value handling
- Push notifications
- Data upload at 2-second intervals
- Dashboard control response

#### 3.2.3 Servo Control Module
- Servo initialization with sweep
- Position mapping (0 - 180 degrees)
- Smooth movement algorithm
- Limit switch protection
- 10-minute interval scheduler

#### 3.2.4 Temperature Sensor Module
- Analog reading with 10-bit resolution
- Moving average filter (n=10 samples)
- Celsius conversion formula
- Alarm threshold detection (130°C)
- Safety shutdown trigger

#### 3.2.5 RTC Module
- Time initialization from NTP
- 24-hour format
- Sunrise/sunset calculation
- Scheduler for 10-minute tracking
- Daylight saving adjustment

#### 3.2.6 LCD Display Module
- 16x2 character display
- Status line 1: Temperature and Time
- Status line 2: Mode and Battery
- Scroll text for long messages
- Backlight control

#### 3.2.7 Push Button Module
- Interrupt-based detection
- Debounce filtering (50ms)
- Mode cycle: Cook → Sterilize → Boil → Warm
- Long press (3 sec) - emergency stop
- Double click - manual position override

#### 3.2.8 SD Card Logging Module
- SPI initialization
- File creation with date in filename
- CSV format with headers
- Append mode for continuous logging
- Error handling and retry

#### 3.2.9 Main Program Loop
- Sequential task scheduling
- Interrupt handling
- Watchdog timer for crash recovery
- Memory management
- LED status indicators

### 3.3 Code Structure

