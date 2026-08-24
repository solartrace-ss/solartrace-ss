# SolarTrace - Week 5 Progress Report

## UbuntuNet Alliance Women Hackathon 2026

**Project:** SolarTrace - Smart IoT-Connected Solar Cooker  
**Team:** Reffgga Repent Ritti, Clementina Agiu Gual Koch, Abuk Santino Garang Chan  
**Report Period:** Week 5 (August 17-21, 2026)  
**Date:** August 21, 2026

---

## Table of Contents

1. [Executive Summary](#1-executive-summary)
2. [Hardware Development & Integration](#2-hardware-development--integration)
3. [Software Development & Upgrades](#3-software-development--upgrades)
4. [Hackathon Submission & Review](#4-hackathon-submission--review)
5. [Software Testing Results](#5-software-testing-results)
6. [Hardware Assembly Summary](#6-hardware-assembly-summary)
7. [Development Challenges & Solutions](#7-development-challenges--solutions)
8. [Week 5 Deliverables](#8-week-5-deliverables)
9. [Team Contributions](#9-team-contributions---week-5)
10. [System Component Updates](#10-system-component-updates)
11. [Code Repository Updates](#11-code-repository-updates)
12. [Summary of Key Achievements](#12-summary-of-key-achievements)
13. [Software Completion Status](#13-software-completion-status)
14. [Photos & Visual Documentation](#14-photos--visual-documentation)
15. [Next Steps](#15-next-steps-week-6)
16. [Conclusion](#16-conclusion)

---

## 1. Executive Summary

This report documents the progress made during Week 5 (August 17-21, 2026) of the SolarTrace project development. The team focused on hardware integration, system assembly, software upgrades, and final submission preparation. Major milestones achieved include complete hardware assembly with stand, mirror installation, solar panel integration, and successful system testing. The team also participated in a critical hackathon meeting with mentors and submitted all required deliverables including the prototype documentation, PowerPoint presentation, and demo video.

---

## 2. Hardware Development & Integration

### 2.1 Stand Construction & Assembly

| Component | Work Done | Result | Remarks |
|-----------|-----------|--------|---------|
| Stand Structure | Welding and assembly of support frame | Complete | Stable and level structure |
| Tracking Level | Alignment calibration for sun tracking | Complete | Accurate horizontal/vertical positioning |
| Burner Ring (Pot Receptacle) | Fabrication and mounting | Complete | Securely holds cooking vessel |

**Details:**
- The stand was welded to provide a sturdy base for the parabolic dish
- Tracking level was calibrated to ensure precise sun tracking
- The burner ring (pot receptacle) was fabricated and securely mounted to hold cooking vessels

### 2.2 Parabolic Dish Mirror Installation

| Task | Details | Result |
|------|---------|--------|
| Mirror Installation | Mirror pieces stuck onto parabolic dish | Complete |
| Reflectivity Test | Tea making test conducted | PASS |
| Focal Point Alignment | Verified focal point for cooking | Accurate |

**Testing Results:**
- **Tea Making Test:** Successfully boiled water and made tea using solar energy
- **Temperature Achieved:** Reached cooking temperature within expected time
- **Focal Point:** Accurately concentrated sunlight on the burner ring

### 2.3 Solar Panel Integration

| Component | Specification | Status |
|-----------|--------------|--------|
| Solar Panels | 50W panels | Added |
| Panel Mounting | Securely mounted on stand | Complete |
| Connection | Connected to charge controller | Complete |
| Power Output | Verified charging capability | PASS |

**Benefits of Solar Panel Addition:**
- Provides sustainable power for electronics
- Reduces reliance on batteries
- Extends system operational time
- Supports off-grid operation

---

## 3. Software Development & Upgrades

### 3.1 Component Testing on ESP32

| Component | Previous | Updated/Tested | Result |
|-----------|----------|---------------|--------|
| RTC Module | DS3231 | Tested on ESP32 | PASS |
| Motor | MG995 Servo | Tested on ESP32 | PASS |
| Temperature Sensor | MAX6675 | Changed to DS18B20 | PASS |
| Buzzer | - | Newly added and tested | PASS |
| LCD Module | I2C LCD | Tested on ESP32 | PASS |

### 3.2 Sensor Migration: MAX6675 → DS18B20

| Aspect | MAX6675 (Previous) | DS18B20 (New) | Reason for Change |
|--------|-------------------|---------------|-------------------|
| Interface | SPI | 1-Wire | Simplified wiring |
| Accuracy | +/- 0.5°C | +/- 0.5°C | Comparable accuracy |
| Power | 3.3V/5V | 3.3V/5V | Compatible |
| Cost | Higher | Lower | Cost-effective |
| Availability | Limited | Widely available | Easier to source |

**Migration Status:** Complete - DS18B20 successfully tested and working with ESP32

### 3.3 Manual UI Implementation

| Feature | Description | Status |
|---------|-------------|--------|
| Manual Mode Selection | Manual UI added for user control | Complete |
| Mode-to-Pin Mapping | All modes assigned to specific pins | Complete |
| LCD Interface | Real-time display of manual controls | Complete |
| Button Control | Physical button control for manual mode | Complete |

### 3.4 Mode Configuration to Pins

| Mode | Pin Assignment | Function |
|------|---------------|----------|
| Cooking Mode | V0 | Activates cooking temperature setting |
| Sterilization Mode | V1 | Activates sterilization cycle |
| Boiling Mode | V2 | Activates boiling temperature |
| Warming Mode | V3 | Activates warming function |
| Servo Control | GPIO 13 | Sun tracking servo motor |
| Buzzer | GPIO 14 | Audio alerts and notifications |
| DS18B20 | GPIO 4 | Temperature sensor data |
| LCD I2C | SDA (21), SCL (22) | Display interface |

---

## 4. Hackathon Submission & Review

### 4.1 Mentor Meeting

| Activity | Details | Status |
|----------|---------|--------|
| Project Structure Presentation | Presented complete project architecture | Complete |
| Prototype Demonstration | Showcased working prototype | Complete |
| 5-Minute Demo Video | Submitted demo video | Complete |
| Live Video Meeting | Met with mentors virtually | Complete |

**Meeting Outcomes:**
- Positive feedback on project progress
- Technical suggestions for improvement received
- Final submission requirements confirmed
- Next steps communicated

### 4.2 Submitted Deliverables

| Deliverable | Description | Status |
|-------------|-------------|--------|
| PowerPoint Presentation | SolarTrace project presentation | Submitted |
| Prototype Documentation | Comprehensive project documentation | Submitted |
| 5-Minute Demo Video | Prototype demonstration video | Submitted |

**Presentation Content:**
- Project overview and problem statement
- Technical architecture and components
- Software development and testing
- Hardware integration and assembly
- Demonstration of working prototype
- Conclusion and next steps

---

## 5. Software Testing Results

### 5.1 Component Integration Testing on ESP32

| Component | Test Conducted | Result | Status |
|-----------|---------------|--------|--------|
| DS18B20 | Temperature reading verification | Accurate readings | PASS |
| Servo Motor MG995 | Range of motion, PWM control | Smooth movement | PASS |
| RTC DS3231 | Time keeping, I2C communication | Accurate time | PASS |
| Buzzer | Sound output, alert notification | Clear sound | PASS |
| LCD I2C | Display functionality | All characters visible | PASS |
| Push Button | Manual mode switching | Responsive | PASS |
| Solar Panels | Voltage/current output | Stable charging | PASS |

### 5.2 Manual UI Testing

| Test Scenario | Expected Result | Actual Result | Status |
|---------------|-----------------|---------------|--------|
| Mode Selection via Button | Cycle through modes | Cycling working | PASS |
| Mode Display on LCD | Show current mode | Display correct | PASS |
| Buzzer Alert | Sound on mode change | Buzzer active | PASS |
| Servo Response | Move to tracking angle | Accurate movement | PASS |
| Temperature Display | Show real-time temp | Reading correctly | PASS |

### 5.3 System Integration Testing

| Test Scenario | Steps | Result | Status |
|---------------|-------|--------|--------|
| Full System Power On | Apply power, check all modules | All initialized | PASS |
| Solar Panel Charging | Monitor battery charge | Charging active | PASS |
| Temperature Monitoring | DS18B20 reading | Real-time updates | PASS |
| Manual Mode Control | Press button, verify mode change | Instant response | PASS |
| Servo Sun Tracking | Verify tracking movement | Smooth tracking | PASS |
| Buzzer Alert System | Trigger alert conditions | Buzzer sounds | PASS |
| LCD Status Display | Verify all information shown | Complete display | PASS |

---

## 6. Hardware Assembly Summary

### 6.1 Complete System Components

| Component | Quantity | Status |
|-----------|----------|--------|
| Parabolic Dish with Mirrors | 1 | Installed |
| Stand Structure | 1 | Welded and leveled |
| Burner Ring (Pot Receptacle) | 1 | Mounted |
| Solar Panels (50W) | 2 | Added |
| Charge Controller | 1 | Connected |
| Battery (12V) | 1 | Installed |
| ESP32 Microcontroller | 1 | Mounted |
| Servo Motor MG995 | 1 | Installed |
| DS18B20 Temperature Sensor | 1 | Installed |
| RTC DS3231 | 1 | Connected |
| LCD I2C Display | 1 | Mounted |
| Buzzer | 1 | Installed |
| Push Button | 1 | Mounted |

### 6.2 Assembly Process

| Day | Activity | Completed |
|-----|----------|-----------|
| Monday | Stand welding, tracking level setup, burner ring mounting | ✓ |
| Tuesday | Mirror installation, tea testing, component testing | ✓ |
| Thursday | Software upgrade with manual UI | ✓ |
| Friday | Solar panel addition | ✓ |

---

## 7. Development Challenges & Solutions

| Challenge | Solution | Time to Resolve |
|-----------|----------|-----------------|
| Parabolic dish mirror alignment | Used precision measurement tools | 2 hours |
| DS18B20 1-Wire communication issues | Added pull-up resistor | 1 hour |
| Servo MG995 power requirements | Dedicated power supply connection | 1 hour |
| Buzzer interference with I2C | Moved GPIO pin assignment | 30 minutes |
| Manual UI mode switching debounce | Implemented software debounce | 1 hour |
| Solar panel wiring and connection | Used proper gauge wires | 1 hour |
| LCD display contrast adjustment | Adjusted potentiometer | 30 minutes |

---

## 8. Week 5 Deliverables

| Deliverable | Status | Completion Date | Notes |
|-------------|--------|-----------------|-------|
| Stand welding and assembly | Complete | August 17, 2026 | Leveled and stable |
| Burner ring mounting | Complete | August 17, 2026 | Securely attached |
| Mirror installation | Complete | August 18, 2026 | All mirrors stuck |
| Tea making test | Complete | August 18, 2026 | Successful |
| RTC DS3231 testing | Complete | August 18, 2026 | Working on ESP32 |
| Servo MG995 testing | Complete | August 18, 2026 | Smooth movement |
| DS18B20 migration | Complete | August 18, 2026 | Working accurately |
| Buzzer testing | Complete | August 18, 2026 | Clear sound output |
| LCD testing | Complete | August 18, 2026 | Display working |
| Mentor meeting | Complete | August 19, 2026 | Presentation delivered |
| PowerPoint submission | Complete | August 19, 2026 | Submitted |
| Prototype documentation | Complete | August 19, 2026 | Submitted |
| Demo video submission | Complete | August 19, 2026 | 5-minute video |
| Manual UI implementation | Complete | August 20, 2026 | All modes mapped |
| Solar panel addition | Complete | August 21, 2026 | Panels installed |

---

## 9. Team Contributions - Week 5

| Team Member | Role | Contributions | Hours |
|-------------|------|---------------|-------|
| Reffgga Repent Ritti | Lead Developer | Software upgrades, manual UI implementation, component testing, ESP32 integration | 25 |
| Clementina Agiu Gual Koch | UI/UX & Documentation | Documentation, PowerPoint preparation, demo video creation, report compilation | 24 |
| Abuk Santino Garang Chan | Testing & Logistics | Hardware assembly, mirror installation, stand welding, solar panel integration | 28 |

### 9.1 Daily Progress Summary

**August 17 (Monday):**
- Stand welding completed
- Tracking level calibrated
- Burner ring (pot receptacle) fabricated and mounted
- All hardware components summed and checked

**August 18 (Tuesday):**
- Mirror pieces stuck onto parabolic dish
- Tea making test conducted - successful
- Component testing on ESP32:
  - RTC DS3231 - PASS
  - Servo MG995 - PASS
  - DS18B20 (replacing MAX6675) - PASS
  - Buzzer - PASS
  - LCD Module - PASS

**August 19 (Wednesday):**
- Hackathon mentor meeting conducted
- Project structure presentation delivered
- Prototype demonstrated in live video
- Submitted PowerPoint presentation
- Submitted prototype documentation
- Submitted 5-minute demo video

**August 20 (Thursday):**
- Software upgrade: Manual UI implemented
- All modes mapped to specific pins
- Pin configuration documented
- System testing with manual controls

**August 21 (Friday):**
- Hardware upgrade: Solar panels added
- Panels connected to charge controller
- Power system verified
- Final system testing completed

---

## 10. System Component Updates

### 10.1 Hardware Component Updates

| Component | Week 4 Status | Week 5 Status | Change |
|-----------|--------------|---------------|--------|
| Stand | Not assembled | Welded and leveled | ✓ Added |
| Burner Ring | Not assembled | Fabricated and mounted | ✓ Added |
| Mirrors | Not installed | Stuck on parabolic dish | ✓ Added |
| Solar Panels | Separate | Integrated into system | ✓ Added |
| Temperature Sensor | MAX6675 | DS18B20 | ✓ Changed |

### 10.2 Software Component Updates

| Component | Week 4 Status | Week 5 Status | Change |
|-----------|--------------|---------------|--------|
| Manual UI | Not implemented | Fully implemented | ✓ Added |
| Mode-Pin Mapping | Not configured | All modes mapped | ✓ Added |
| Buzzer Control | Not implemented | Integrated | ✓ Added |

---

## 11. Code Repository Updates

### 11.1 GitHub Activity (Week 5)

| Activity | Count | Notes |
|----------|-------|-------|
| Commits | 28 | New features and updates |
| Files Added | 5 | Manual UI, DS18B20, Buzzer |
| Lines of Code Added | 320 | Additional functionality |
| Lines of Code Modified | 150 | Updates and improvements |
| Lines of Code Removed | 45 | Removed MAX6675 code |
| Branches | 3 | Main, Development, Feature/Manual-UI |

### 11.2 Code Statistics Update

| Metric | Week 4 | Week 5 | Change |
|--------|--------|--------|--------|
| Total Lines | 1,280 | 1,550 | +270 |
| Code Lines | 740 | 890 | +150 |
| Comment Lines | 325 | 390 | +65 |
| Functions | 34 | 40 | +6 |
| Header Files | 10 | 12 | +2 |
| Source Files | 1 | 1 | 0 |

---

## 12. Summary of Key Achievements

| Achievement | Details | Impact |
|-------------|---------|--------|
| Complete Hardware Assembly | Stand, burner ring, mirrors installed | Fully functional physical prototype |
| Successful Solar Cooking Test | Tea made using solar energy | Proven functionality |
| DS18B20 Migration | Replaced MAX6675 | Simplified wiring, lower cost |
| ESP32 Component Integration | All components tested | Reliable system operation |
| Manual UI Implementation | User-friendly controls | Enhanced usability |
| Solar Panel Integration | Added 50W panels | Sustainable power source |
| Mentor Meeting | Successfully presented | Positive validation |
| All Submissions Complete | PPT, Doc, Video | Meets hackathon requirements |
| Live Video Demonstration | Working prototype shown | Proof of concept confirmed |

---

## 13. Software Completion Status

### 13.1 Overall Software Progress: 98%

| Module | Week 4 Status | Week 5 Status | Progress |
|--------|--------------|---------------|----------|
| WiFi Connection | 100% | 100% | Complete |
| Blynk Integration | 100% | 100% | Complete |
| Servo Control | 100% | 100% | Complete |
| Temperature Reading | 100% | 100% | Complete |
| RTC Scheduler | 100% | 100% | Complete |
| LCD Display | 100% | 100% | Complete |
| Button Handling | 100% | 100% | Complete |
| SD Logging | 100% | 100% | Complete |
| Safety Monitor | 100% | 100% | Complete |
| **Manual UI** | **0%** | **100%** | **✓ Added** |
| **Buzzer Control** | **0%** | **100%** | **✓ Added** |
| OTA Updates | 40% | 50% | In Progress |
| Power Saving | 30% | 40% | In Progress |

### 13.2 Hardware Completion Status: 100%

| Category | Week 4 | Week 5 |
|----------|--------|--------|
| Stand Assembly | 0% | 100% |
| Burner Ring | 0% | 100% |
| Mirror Installation | 0% | 100% |
| Solar Panel Integration | 0% | 100% |
| Component Testing | 100% | 100% |
| Sensor Calibration | 100% | 100% |

---

## 14. Photos & Visual Documentation

### 14.1 Hardware Assembly Photos

| Photo ID | Description | Captured |
|----------|-------------|----------|
| IMG_001 | Stand welding in progress | August 17 |
| IMG_002 | Burner ring installation | August 17 |
| IMG_003 | Mirror installation on parabolic dish | August 18 |
| IMG_004 | Tea making test | August 18 |
| IMG_005 | ESP32 component testing | August 18 |
| IMG_006 | System with solar panels | August 21 |
| IMG_007 | Complete assembled prototype | August 21 |

### 14.2 Demonstration Video

| Aspect | Details |
|--------|---------|
| Duration | 5 minutes |
| Content | Full system demonstration |
| Format | MP4 |
| Submission Date | August 19, 2026 |
| Status | Submitted |

---

## 15. Next Steps (Week 6)

### 15.1 Final Tasks
- Final system integration and validation
- Bug fixes and performance optimization
- Complete final project documentation
- Prepare final presentation materials
- Hardware fine-tuning

### 15.2 Submission Preparation
- Finalize all documentation
- Compile comprehensive project report
- Prepare final demonstration
- Complete any outstanding tasks

---

## 16. Conclusion

Week 5 marked a significant milestone in the SolarTrace project with the completion of hardware assembly, successful system testing, and submission of all hackathon deliverables. The team successfully:

- **Completed** full hardware assembly including stand, burner ring, and mirrors
- **Achieved** successful solar cooking test (tea making)
- **Integrated** all components with ESP32 microcontroller
- **Upgraded** software with manual UI and proper pin mapping
- **Added** solar panels for sustainable power
- **Presented** the project to mentors
- **Submitted** PowerPoint, documentation, and demo video

**Key Achievements:**
- 100% hardware assembly completed
- 100% component testing on ESP32
- 100% software module implementation
- 98% overall software completion
- Successful mentor meeting
- All hackathon deliverables submitted

**Final Week Focus:** System finalization, documentation completion, and submission preparation.

---

**Report Prepared By:** Clementina Agiu Gual Koch  
**Reviewed By:** Reffgga Repent Ritti  
**Approved By:** Abuk Santino Garang Chan  
**Date:** August 21, 2026  
**Version:** 1.0

---

*"Harnessing the sun for a sustainable future."*
