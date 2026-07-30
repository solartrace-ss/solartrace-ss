/*
 * ============================================================================
 * SOLARTRACE - Temperature Sensor Module Implementation
 * ============================================================================
 * 
 * File      : sensors.cpp
 * Purpose   : MAX6675 thermocouple temperature sensor implementation
 * Team      : South Sudan - UbuntuNet Alliance Women Hackathon 2026
 * ============================================================================
 */

#include "sensors.h"

// ============================================================================
// CONSTRUCTOR / DESTRUCTOR
// ============================================================================

TemperatureController::TemperatureController() {
    csPin = THERMO_CS;
    sckPin = THERMO_SCK;
    soPin = THERMO_SO;
    thermocouple = nullptr;
    isInitialized = false;
    currentTemperature = 0.0;
    lastValidTemperature = 0.0;
    offset = 0.0;
    minTemp = 1000.0;
    maxTemp = -1000.0;
    sumTemp = 0.0;
    sampleCount = 0;
    sensorReady = false;
    overheatDetected = false;
}

TemperatureController::~TemperatureController() {
    if (thermocouple != nullptr) {
        delete thermocouple;
        thermocouple = nullptr;
    }
}

// ============================================================================
// INITIALIZATION
// ============================================================================

void TemperatureController::begin() {
    begin(csPin, sckPin, soPin);
}

void TemperatureController::begin(int cs, int sck, int so) {
    csPin = cs;
    sckPin = sck;
    soPin = so;
    
    Serial.println("Initializing Temperature Sensor...");
    
    // Create thermocouple object
    thermocouple = new MAX6675(sckPin, csPin, soPin);
    
    if (thermocouple != nullptr) {
        isInitialized = true;
        
        // Test reading
        float testTemp = thermocouple->readCelsius();
        if (isValidTemperature(testTemp)) {
            sensorReady = true;
            currentTemperature = testTemp;
            lastValidTemperature = testTemp;
            Serial.print("Temperature sensor ready: ");
            Serial.print(testTemp);
            Serial.println("°C");
        } else {
            sensorReady = false;
            Serial.println("WARNING: Temperature sensor not responding!");
        }
    } else {
        Serial.println("ERROR: Failed to initialize thermocouple!");
        isInitialized = false;
    }
}

// ============================================================================
// CORE FUNCTIONS
// ============================================================================

float TemperatureController::readTemperature() {
    if (!isInitialized || thermocouple == nullptr) {
        return currentTemperature;
    }
    
    // Read temperature
    float temp = thermocouple->readCelsius();
    
    // Check for valid reading
    if (isValidTemperature(temp)) {
        currentTemperature = temp + offset;
        lastValidTemperature = currentTemperature;
        sensorReady = true;
        updateStatistics(currentTemperature);
        checkOverheat(currentTemperature);
    } else {
        sensorReady = false;
        currentTemperature = lastValidTemperature;
    }
    
    return currentTemperature;
}

float TemperatureController::getCurrentTemperature() {
    return currentTemperature;
}

float TemperatureController::getLastValidTemperature() {
    return lastValidTemperature;
}

// ============================================================================
// STATUS
// ============================================================================

bool TemperatureController::isSensorReady() {
    return sensorReady && isInitialized;
}

bool TemperatureController::isTemperatureValid() {
    return isValidTemperature(currentTemperature);
}

bool TemperatureController::isOverheatDetected() {
    return overheatDetected;
}

// ============================================================================
// CALIBRATION
// ============================================================================

void TemperatureController::calibrate() {
    if (!isInitialized) return;
    
    Serial.println("Calibrating temperature sensor...");
    
    // Take multiple readings for calibration
    float sum = 0.0;
    int count = 0;
    
    for (int i = 0; i < 10; i++) {
        float temp = thermocouple->readCelsius();
        if (isValidTemperature(temp)) {
            sum += temp;
            count++;
        }
        delay(100);
    }
    
    if (count > 0) {
        float avg = sum / count;
        Serial.print("Average reading: ");
        Serial.print(avg);
        Serial.println("°C");
        Serial.print("Current offset: ");
        Serial.println(offset);
    }
}

void TemperatureController::setOffset(float off) {
    offset = off;
    Serial.print("Temperature offset set to: ");
    Serial.println(offset);
}

float TemperatureController::getOffset() {
    return offset;
}

// ============================================================================
// STATISTICS
// ============================================================================

float TemperatureController::getMinTemperature() {
    return (minTemp == 1000.0) ? 0.0 : minTemp;
}

float TemperatureController::getMaxTemperature() {
    return (maxTemp == -1000.0) ? 0.0 : maxTemp;
}

float TemperatureController::getAverageTemperature() {
    return (sampleCount == 0) ? 0.0 : (sumTemp / sampleCount);
}

void TemperatureController::resetStatistics() {
    minTemp = 1000.0;
    maxTemp = -1000.0;
    sumTemp = 0.0;
    sampleCount = 0;
    Serial.println("Temperature statistics reset");
}

// ============================================================================
// DEBUG
// ============================================================================

void TemperatureController::printStatus() {
    Serial.println("=== Temperature Sensor Status ===");
    Serial.print("Initialized: ");
    Serial.println(isInitialized ? "YES" : "NO");
    Serial.print("Sensor Ready: ");
    Serial.println(sensorReady ? "YES" : "NO");
    Serial.print("Current Temp: ");
    Serial.print(currentTemperature);
    Serial.println("°C");
    Serial.print("Last Valid: ");
    Serial.print(lastValidTemperature);
    Serial.println("°C");
    Serial.print("Overheat: ");
    Serial.println(overheatDetected ? "YES" : "NO");
    Serial.println("==================================");
}

void TemperatureController::printStatistics() {
    Serial.println("=== Temperature Statistics ===");
    Serial.print("Samples: ");
    Serial.println(sampleCount);
    Serial.print("Min: ");
    Serial.print(getMinTemperature());
    Serial.println("°C");
    Serial.print("Max: ");
    Serial.print(getMaxTemperature());
    Serial.println("°C");
    Serial.print("Avg: ");
    Serial.print(getAverageTemperature());
    Serial.println("°C");
    Serial.println("================================");
}

// ============================================================================
// INTERNAL METHODS
// ============================================================================

bool TemperatureController::isValidTemperature(float temp) {
    return !isnan(temp) && 
           temp >= MIN_VALID_TEMP && 
           temp <= MAX_VALID_TEMP;
}

void TemperatureController::updateStatistics(float temp) {
    if (temp < minTemp) minTemp = temp;
    if (temp > maxTemp) maxTemp = temp;
    sumTemp += temp;
    sampleCount++;
}

void TemperatureController::checkOverheat(float temp) {
    overheatDetected = (temp > MAX_SAFE_TEMP);
    
    if (overheatDetected) {
        Serial.print("!!!!! OVERHEAT WARNING: ");
        Serial.print(temp);
        Serial.println("°C !!!!!");
    }
}

float TemperatureController::clampTemperature(float temp) {
    if (temp < MIN_VALID_TEMP) return MIN_VALID_TEMP;
    if (temp > MAX_VALID_TEMP) return MAX_VALID_TEMP;
    return temp;
}
