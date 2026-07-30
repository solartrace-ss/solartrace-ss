/*
 * ============================================================================
 * SOLARTRACE - Sun Tracking Module Implementation
 * ============================================================================
 * 
 * File      : tracking.cpp
 * Purpose   : RTC-based sun tracking algorithm implementation
 * Team      : South Sudan - UbuntuNet Alliance Women Hackathon 2026
 * ============================================================================
 */

#include "tracking.h"
#include <Wire.h>

// ============================================================================
// CONSTRUCTOR / DESTRUCTOR
// ============================================================================

SunTracker::SunTracker() {
    currentAngle = 0.0;
    targetAngle = 0.0;
    trackingActive = false;
    servoPin = SERVO_PIN;
    isInitialized = false;
}

SunTracker::~SunTracker() {
    // Detach servo to free resources
    if (isInitialized) {
        servo.detach();
    }
}

// ============================================================================
// INITIALIZATION
// ============================================================================

void SunTracker::begin() {
    begin(servoPin);
}

void SunTracker::begin(int pin) {
    servoPin = pin;
    
    Serial.println("Initializing Sun Tracker...");
    
    // Setup RTC
    setupRTC();
    
    // Attach servo
    servo.attach(servoPin);
    servo.write(0);
    
    isInitialized = true;
    currentAngle = 0.0;
    trackingActive = false;
    
    Serial.println("Sun Tracker initialized");
    printStatus();
}

void SunTracker::setupRTC() {
    Serial.println("Initializing RTC...");
    
    if (!rtc.begin()) {
        Serial.println("ERROR: RTC not found!");
        Serial.println("Check I2C connections (SDA=GPIO21, SCL=GPIO22)");
        return;
    }
    
    // Check if RTC lost power
    if (rtc.lostPower()) {
        Serial.println("RTC lost power - setting to compile time");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    
    // Display current time
    DateTime now = rtc.now();
    Serial.print("RTC initialized: ");
    Serial.print(now.year());
    Serial.print("/");
    Serial.print(now.month());
    Serial.print("/");
    Serial.print(now.day());
    Serial.print(" ");
    Serial.print(now.hour());
    Serial.print(":");
    Serial.print(now.minute());
    Serial.print(":");
    Serial.println(now.second());
}

// ============================================================================
// CORE FUNCTIONS
// ============================================================================

float SunTracker::calculateSunAngle() {
    if (!isInitialized) {
        return 0.0;
    }
    
    DateTime now = rtc.now();
    
    // Get current time in minutes from midnight
    int currentMinutes = now.hour() * 60 + now.minute();
    
    // Calculate sunrise and sunset minutes
    int sunriseMinutes = SUNRISE_HOUR * 60 + SUNRISE_MINUTE;
    int sunsetMinutes = SUNSET_HOUR * 60 + SUNSET_MINUTE;
    
    // If before sunrise or after sunset, return 0 (idle position)
    if (currentMinutes < sunriseMinutes || currentMinutes > sunsetMinutes) {
        return 0.0;
    }
    
    // Calculate minutes since sunrise
    int minutesSinceSunrise = currentMinutes - sunriseMinutes;
    
    // Calculate angle: (minutes_since_sunrise / total_daylight) × 120°
    float angle = ((float)minutesSinceSunrise / TOTAL_DAYLIGHT) * 120.0;
    
    // Clamp angle to valid range
    angle = clamp(angle, 0.0, 120.0);
    
    targetAngle = angle;
    return angle;
}

void SunTracker::moveToAngle(float angle) {
    if (!isInitialized) return;
    
    // Clamp angle
    angle = clamp(angle, 0.0, 180.0);
    
    // Convert to integer for servo
    int angleInt = (int)angle;
    
    // Move servo
    servo.write(angleInt);
    delay(15);  // Allow servo to move
    
    // Update state
    float oldAngle = currentAngle;
    currentAngle = angle;
    targetAngle = angle;
    
    // Log angle change
    logAngleChange(oldAngle, currentAngle);
}

void SunTracker::moveToAngle(int angle) {
    moveToAngle((float)angle);
}

// ============================================================================
// POSITION CONTROL
// ============================================================================

void SunTracker::idlePosition() {
    moveToAngle(0);
    trackingActive = false;
    Serial.println("Servo moved to IDLE position (0°)");
}

void SunTracker::trackingPosition() {
    float angle = calculateSunAngle();
    moveToAngle(angle);
    trackingActive = true;
    Serial.print("Servo moved to TRACKING position (");
    Serial.print(angle);
    Serial.println("°)");
}

void SunTracker::emergencyPosition() {
    moveToAngle(0);
    trackingActive = false;
    Serial.println("!!!!! Servo moved to EMERGENCY position !!!!!");
}

// ============================================================================
// GETTERS
// ============================================================================

float SunTracker::getCurrentAngle() {
    return currentAngle;
}

float SunTracker::getTargetAngle() {
    return targetAngle;
}

bool SunTracker::isTracking() {
    return trackingActive;
}

// ============================================================================
// TIME FUNCTIONS
// ============================================================================

DateTime SunTracker::getSunriseTime() {
    DateTime now = rtc.now();
    return DateTime(now.year(), now.month(), now.day(),
                    SUNRISE_HOUR, SUNRISE_MINUTE, 0);
}

DateTime SunTracker::getSunsetTime() {
    DateTime now = rtc.now();
    return DateTime(now.year(), now.month(), now.day(),
                    SUNSET_HOUR, SUNSET_MINUTE, 0);
}

float SunTracker::getDaylightMinutes() {
    return TOTAL_DAYLIGHT;
}

// ============================================================================
// DEBUG
// ============================================================================

void SunTracker::printStatus() {
    DateTime now = rtc.now();
    float angle = calculateSunAngle();
    
    Serial.println("=== Sun Tracker Status ===");
    Serial.print("Time: ");
    Serial.print(now.hour());
    Serial.print(":");
    Serial.println(now.minute());
    Serial.print("Sun Angle: ");
    Serial.print(angle);
    Serial.println("°");
    Serial.print("Current Angle: ");
    Serial.print(currentAngle);
    Serial.println("°");
    Serial.print("Tracking Active: ");
    Serial.println(trackingActive ? "YES" : "NO");
    Serial.println("==========================");
}

// ============================================================================
// INTERNAL METHODS
// ============================================================================

int SunTracker::calculateMinutesSinceMidnight(int hour, int minute) {
    return hour * 60 + minute;
}

float SunTracker::clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

int SunTracker::clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

bool SunTracker::isDaylight() {
    DateTime now = rtc.now();
    int currentMinutes = now.hour() * 60 + now.minute();
    int sunriseMinutes = SUNRISE_HOUR * 60 + SUNRISE_MINUTE;
    int sunsetMinutes = SUNSET_HOUR * 60 + SUNSET_MINUTE;
    
    return (currentMinutes >= sunriseMinutes && currentMinutes <= sunsetMinutes);
}

void SunTracker::logAngleChange(float oldAngle, float newAngle) {
    // Only log significant changes
    if (abs(newAngle - oldAngle) > 1.0) {
        Serial.print("[Tracking] Angle changed: ");
        Serial.print(oldAngle);
        Serial.print("° → ");
        Serial.print(newAngle);
        Serial.println("°");
    }
}
