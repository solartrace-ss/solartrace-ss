
### 3.3 Module Descriptions

| Module | Files | Description | Status |
|--------|-------|-------------|--------|
| Main Application | main/ | Application entry point and main loop | Complete |
| Blynk Interface | blynk_interface.cpp/h | Cloud connection, widget handling, notifications | Complete |
| Data Logger | data_logger.cpp/h | SD card logging, CSV format, timestamps | Complete |
| Sensors | sensors.cpp/h | MAX6675 temperature sensor interface | Complete |
| Tracking | tracking.cpp/h | Servo control, sun position calculation | Complete |

### 3.4 Key Functions Implemented

| Function Name | Description | Status |
|---------------|-------------|--------|
| setupWiFi() | Connect to WiFi network | Complete |
| blynkConnect() | Connect to Blynk cloud | Complete |
| updateServoPosition() | Move servo to calculated angle | Complete |
| readTemperature() | Read and filter temperature | Complete |
| getCurrentTime() | Retrieve time from RTC | Complete |
| updateDisplay() | Refresh LCD with current data | Complete |
| handleButtonPress() | Process button input | Complete |
| logData() | Write data to SD card | Complete |
| checkSafety() | Monitor temperature for shutdown | Complete |
| calculateSunAngle() | Compute tracking angle | Complete |
| otaUpdate() | Over-the-air firmware update | In Progress |
| sleepMode() | Power saving mode | In Progress |

### 3.5 Contribution History

| File | Author | Last Commit | Description |
|------|--------|-------------|-------------|
| blynk_interface.cpp | Alek | 2 weeks ago | Blynk interface module implementation |
| blynk_interface.h | Alek | 2 weeks ago | Blynk interface module header file |
| data_logger.cpp | Alek | 2 weeks ago | Data Logger module for SD card logging |
| data_logger.h | Alek | 2 weeks ago | SD card logging interface |
| main/ | Alek | 2 weeks ago | Main application entry point |
| sensors.cpp | Alek | 2 weeks ago | Temperature sensor module implementation |
| sensors.h | Alek | 2 weeks ago | MAX6675 temperature sensor interface |
| tracking.cpp | Alek | 2 weeks ago | Sun tracking module implementation |
| tracking.h | Alek | 2 weeks ago | Sun tracking module header |

---

## 4. Software Testing Results

### 4.1 Unit Testing

| Module | Test Cases | Passed | Failed | Status |
|--------|-----------|--------|--------|--------|
| WiFi Connection | 5 | 5 | 0 | PASS |
| Blynk Integration | 4 | 4 | 0 | PASS |
| Servo Control | 6 | 6 | 0 | PASS |
| Temperature Reading | 5 | 5 | 0 | PASS |
| RTC Time Keeping | 4 | 4 | 0 | PASS |
| LCD Display | 3 | 3 | 0 | PASS |
| Button Handling | 5 | 5 | 0 | PASS |
| SD Logging | 4 | 4 | 0 | PASS |
| Safety Monitor | 3 | 3 | 0 | PASS |

### 4.2 Integration Testing

| Test Scenario | Steps | Result | Status |
|---------------|-------|--------|--------|
| Power On Sequence | Apply power, check all modules initialize | All modules initialized | PASS |
| WiFi → Blynk Connection | Boot ESP32, wait for connections | Connected in 5 seconds | PASS |
| RTC → Servo Scheduler | Set time, check servo moves at interval | Moves every 10 min | PASS |
| Button → Mode Change | Press button, check LCD and Blynk update | Mode changed instantly | PASS |
| Temperature → Alarm | Heat sensor, monitor at 130°C | Shutdown at 129.8°C | PASS |
| Data Logging | Run system, check SD card content | Data logged correctly | PASS |
| Complete Workflow | Full system operation test | All functions working | PASS |

### 4.3 Performance Testing

| Metric | Result | Target | Status |
|--------|--------|--------|--------|
| Boot Time | 3.2 seconds | < 5 sec | PASS |
| WiFi Connect Time | 2.4 seconds | < 5 sec | PASS |
| Blynk Connect Time | 1.8 seconds | < 3 sec | PASS |
| Sensor Read Interval | 1.0 seconds | 1 sec | PASS |
| Log Write Time | 0.15 seconds | < 0.5 sec | PASS |
| Button Response | 0.05 seconds | < 0.1 sec | PASS |
| Memory Usage | 42% of RAM | < 70% | PASS |
| WiFi Signal Strength | -65 dBm | > -80 dBm | PASS |

---

## 5. Blynk Dashboard Development

### 5.1 Dashboard Layout

| Widget | Function | Data Stream | Status |
|--------|----------|-------------|--------|
| Button V0 | Cooking Mode | Virtual Pin 0 | Tested |
| Button V1 | Sterilization Mode | Virtual Pin 1 | Tested |
| Button V2 | Boiling Mode | Virtual Pin 2 | Tested |
| Button V3 | Warming Mode | Virtual Pin 3 | Tested |
| Gauge V4 | Temperature | Virtual Pin 4 | Tested |
| Value V5 | Battery Voltage | Virtual Pin 5 | Tested |
| Value V6 | Current Mode | Virtual Pin 6 | Tested |
| Timer V7 | Cooking Time | Virtual Pin 7 | Tested |
| Notification | Safety Alert | System Event | Tested |

### 5.2 Testing Scenarios

| Scenario | Expected | Actual | Status |
|----------|----------|--------|--------|
| Remote mode selection | Mode changes on physical device | Mode changed in < 1 sec | PASS |
| Temperature monitoring | Real-time updates | Updates every 2 seconds | PASS |
| Alert notification | Receive when temperature > 120°C | Alert received | PASS |
| Mobile vs web sync | Same data on both platforms | Sync confirmed | PASS |

---

## 6. Code Repository Updates

### 6.1 GitHub Activity (Week 4)

| Activity | Count | Notes |
|----------|-------|-------|
| Commits | 37 | All modules added |
| Files Added | 15 | All .cpp and .h files |
| Lines of Code | 1,280 | Including comments |
| Comments | 42% | Well documented |
| Readme Updates | 3 | Project info, setup instructions |
| Branches | 2 | Main + Development |
| Issues Opened | 2 | Bug tracking |
| Issues Closed | 2 | All resolved |

### 6.2 Code Quality Metrics

| Metric | Value |
|--------|-------|
| Average Function Length | 15 lines |
| Cyclomatic Complexity | Low (< 5) |
| Comment Coverage | 42% |
| Coding Standard | Google C++ Style |
| Build Status | Passing |

---

## 7. Development Challenges & Solutions

| Challenge | Solution | Time to Resolve |
|-----------|----------|-----------------|
| Servo jitter during smooth movement | Implemented acceleration/deceleration algorithm | 4 hours |
| RTC time drift | Added periodic NTP sync (every 6 hours) | 2 hours |
| SD card initialization failure | Added format check and retry logic | 3 hours |
| Blynk disconnection during testing | Implemented exponential backoff reconnect | 3 hours |
| I2C communication errors | Reduced I2C speed from 400kHz to 100kHz | 1 hour |
| Memory fragmentation | Optimized string handling, used String sparingly | 2 hours |
| LCD showing garbled characters | Fixed wiring, adjusted I2C address | 1 hour |
| Temperature reading noise | Applied moving average filter (n=10) | 2 hours |
| Team transition and knowledge transfer | Comprehensive handover documentation | 4 hours |

---

## 8. Week 4 Deliverables

| Deliverable | Status | Completion Date | Notes |
|-------------|--------|-----------------|-------|
| All component tests completed | Complete | August 9, 2026 | 15 components tested |
| Sensor calibration complete | Complete | August 9, 2026 | All sensors calibrated |
| WiFi module code | Complete | August 10, 2026 | With auto-reconnect |
| Blynk integration code | Complete | August 10, 2026 | Dashboard connected |
| Servo control code | Complete | August 11, 2026 | Sun tracking implemented |
| Temperature monitoring code | Complete | August 11, 2026 | With filter and alarm |
| RTC scheduling code | Complete | August 11, 2026 | 10-minute interval logic |
| LCD display code | Complete | August 12, 2026 | 4-line status display |
| Button handling code | Complete | August 12, 2026 | Mode cycling and emergency stop |
| SD logging code | Complete | August 12, 2026 | CSV format with timestamps |
| Safety monitor code | Complete | August 13, 2026 | 130°C shutdown logic |
| Integration testing | Complete | August 13, 2026 | All modules working together |
| Code documentation | Complete | August 14, 2026 | Inline comments added |
| GitHub repository | Complete | August 14, 2026 | All code committed |
| Team handover documentation | Complete | August 14, 2026 | Knowledge transfer to new Lead Developer |

---

## 9. Team Contributions - Week 4

| Team Member | Role | Contributions | Hours |
|-------------|------|---------------|-------|
| Reffgga Repent Ritti | Lead Developer | ESP32 firmware review, code module testing, integration testing, debugging | 20 |
| Clementina Agiu Gual Koch | UI/UX & Documentation | Blynk dashboard design, code documentation, software testing, report compilation | 22 |
| Abuk Santino Garang Chan | Testing & Logistics | Component testing, calibration, quality assurance, GitHub commits | 20 |

### 9.1 Daily Progress Summary

**August 8 (Saturday):**
- Completed ESP32 setup and IDE configuration
- WiFi connection module written and tested
- Initial Blynk integration tested

**August 9 (Sunday):**
- Component testing completed
- Sensor calibration done
- Temperature sensor code written

**August 10 (Monday):**
- Servo control algorithm implemented
- RTC scheduling logic written
- Servo + RTC integration tested

**August 11 (Tuesday):**
- LCD display code written
- Button handling implemented
- SD card logging module written
- All modules individually tested

**August 12 (Wednesday):**
- Code integration and merging
- Blynk dashboard finalized
- Initial integration testing

**August 13 (Thursday):**
- Full integration testing
- Safety monitor tested
- Bug fixes and optimization

**August 14 (Friday):**
- Code documentation added
- GitHub repository update
- Final software validation
- Team transition and knowledge transfer completed

---

## 10. Team Change Notification

### 10.1 Departing Member
- **Name:** Alek Madut Malual
- **Role:** Lead Developer
- **Reason for Departure:** Unforeseen personal circumstances (mother undergoing surgery, loss of uncle)
- **Departure Date:** August 14, 2026

### 10.2 New Member
- **Name:** Reffgga Repent Ritti
- **Role:** Lead Developer
- **Email:** reffggaritti@gmail.com
- **WhatsApp:** +211921706996
- **Background:** Computer Science graduate with strong technical skills
- **Project Familiarity:** Has been part of the team from the beginning, contributing behind the scenes
- **Join Date:** August 14, 2026

---

## 11. Software Version Control

### 11.1 Version History

| Version | Date | Changes |
|---------|------|---------|
| v0.1.0 | Aug 8 | Initial structure, WiFi and Blynk |
| v0.2.0 | Aug 9 | Servo control, RTC integration |
| v0.3.0 | Aug 10 | Temperature, LCD, Button |
| v0.4.0 | Aug 11 | SD logging, Safety monitor |
| v0.5.0 | Aug 12 | All modules integrated |
| v1.0.0 | Aug 13 | Full system working |
| v1.0.1 | Aug 14 | Documentation and cleanup |

### 11.2 Code Statistics

| Metric | Value |
|--------|-------|
| Total Lines | 1,280 |
| Code Lines | 740 |
| Comment Lines | 325 |
| Blank Lines | 215 |
| Functions | 34 |
| Classes | 0 (Procedural C++) |
| Header Files | 10 |
| Source Files | 1 |

---

## 12. Next Steps (Week 5)

### 12.1 Software Tasks
- OTA (Over-The-Air) update capability
- Sleep mode for power saving
- Additional debug logging
- Performance optimization

### 12.2 System Integration
- Hardware integration (Week 5 focus)
- Full system testing
- Field testing preparation

### 12.3 Documentation
- Complete technical documentation
- Compile final project report
- Prepare demonstration materials

---

## 13. Progress Summary

### 13.1 Software Completion: 95%

| Module | Progress | Status |
|--------|----------|--------|
| WiFi Connection | 100% | Complete |
| Blynk Integration | 100% | Complete |
| Servo Control | 100% | Complete |
| Temperature Reading | 100% | Complete |
| RTC Scheduler | 100% | Complete |
| LCD Display | 100% | Complete |
| Button Handling | 100% | Complete |
| SD Logging | 100% | Complete |
| Safety Monitor | 100% | Complete |
| OTA Updates | 40% | In Progress |
| Power Saving | 30% | In Progress |

### 13.2 Component Testing: 100%

| Category | Completion |
|----------|------------|
| Microcontrollers | 100% |
| Sensors | 100% |
| Power Systems | 100% |
| Communication | 100% |
| Storage | 100% |

---

## 14. Conclusion

Week 4 focused exclusively on component testing and software development. All 15 hardware components were successfully tested and calibrated. All software modules have been implemented, tested, and documented. The software integration was successful with all modules working together as intended.

**Key Achievements:**
- 100% component testing completed
- 100% sensor calibration completed
- 1,280 lines of code written
- 37 commits to GitHub
- 9 functional software modules
- 95% software completion
- Blynk dashboard fully operational
- Integration testing passed
- Complete code documentation
- Successful team transition and knowledge transfer

**Week 5 Focus:** Hardware integration, system assembly, and final submission preparation.

---

**Report Prepared By:** Clementina Agiu Gual Koch  
**Reviewed By:** Reffgga Repent Ritti  
**Approved By:** Abuk Santino Garang Chan  
**Date:** August 14, 2026  
**Version:** 1.0

---


*"Harnessing the sun for a sustainable future."*
