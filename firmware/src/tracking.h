/*
 * ============================================================================
 * SOLARTRACE - Sun Tracking Module Header
 * ============================================================================
 * 
 * File      : tracking.h
 * Purpose   : RTC-based sun tracking algorithm
 * Team      : South Sudan - UbuntuNet Alliance Women Hackathon 2026
 * ============================================================================
 */

#ifndef TRACKING_H
#define TRACKING_H

#include <Arduino.h>
#include <RTClib.h>
#include <Servo.h>

// ============================================================================
// SOLAR PARAMETERS (Juba, South Sudan - 4.85°N)
// ============================================================================

#define LATITUDE              4.85
#define SUNRISE_HOUR          6
#define SUNRISE_MINUTE        30
#define SUNSET_HOUR           18
#define SUNSET_MINUTE         0
#define TOTAL_DAYLIGHT        690      // 11.5 hours in minutes
#define SERVO_STEP_INTERVAL   10       // Minutes between adjustments
#define SERVO_STEP_ANGLE      2.5      // Degrees per step

// ============================================================================
// PIN DEFINITIONS
// ============================================================================

#define SERVO_PIN             13       // GPIO13 - PWM Signal

// ============================================================================
// SUN TRACKER CLASS
// ============================================================================

class SunTracker {
public:
    // Constructor / Destructor
    SunTracker();
    ~SunTracker();
    
    // Initialization
    void begin();
    void begin(int servoPin);
    
    // Core Functions
    float calculateSunAngle();
    void moveToAngle(float angle);
    void moveToAngle(int angle);
    
    // Position Control
    void idlePosition();
    void trackingPosition();
    void emergencyPosition();
    
    // Getters
    float getCurrentAngle();
    float getTargetAngle();
    bool isTracking();
    
    // Time Functions
    DateTime getSunriseTime();
    DateTime getSunsetTime();
    float getDaylightMinutes();
    
    // Debug
    void printStatus();
    
private:
    // Internal Components
    Servo servo;
    RTC_DS3231 rtc;
    
    // Internal State
    float currentAngle;
    float targetAngle;
    bool trackingActive;
    int servoPin;
    bool isInitialized;
    
    // Internal Methods
    void setupRTC();
    int calculateMinutesSinceMidnight(int hour, int minute);
    float clamp(float value, float min, float max);
    int clamp(int value, int min, int max);
    bool isDaylight();
    void logAngleChange(float oldAngle, float newAngle);
};

#endif // TRACKING_H
