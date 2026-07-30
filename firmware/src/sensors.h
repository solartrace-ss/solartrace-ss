/*
 * ============================================================================
 * SOLARTRACE - Temperature Sensor Module Header
 * ============================================================================
 * 
 * File      : sensors.h
 * Purpose   : MAX6675 thermocouple temperature sensor interface
 * Team      : South Sudan - UbuntuNet Alliance Women Hackathon 2026
 * ============================================================================
 */

#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <MAX6675.h>

// ============================================================================
// PIN DEFINITIONS
// ============================================================================

#define THERMO_CS    15       // GPIO15 - Chip Select
#define THERMO_SCK   14       // GPIO14 - SPI Clock
#define THERMO_SO    12       // GPIO12 - SPI Data Out

// ============================================================================
// TEMPERATURE CONSTANTS
// ============================================================================

#define TEMP_READ_INTERVAL    500    // Milliseconds between readings
#define MAX_SAFE_TEMP         130.0  // Maximum safe temperature
#define MIN_VALID_TEMP        -10.0  // Minimum valid temperature
#define MAX_VALID_TEMP        500.0  // Maximum valid temperature

// ============================================================================
// TEMPERATURE CONTROLLER CLASS
// ============================================================================

class TemperatureController {
public:
    // Constructor / Destructor
    TemperatureController();
    ~TemperatureController();
    
    // Initialization
    void begin();
    void begin(int csPin, int sckPin, int soPin);
    
    // Core Functions
    float readTemperature();
    float getCurrentTemperature();
    float getLastValidTemperature();
    
    // Status
    bool isSensorReady();
    bool isTemperatureValid();
    bool isOverheatDetected();
    
    // Calibration
    void calibrate();
    void setOffset(float offset);
    float getOffset();
    
    // Statistics
    float getMinTemperature();
    float getMaxTemperature();
    float getAverageTemperature();
    void resetStatistics();
    
    // Debug
    void printStatus();
    void printStatistics();
    
private:
    // Internal Components
    MAX6675* thermocouple;
    int csPin;
    int sckPin;
    int soPin;
    bool isInitialized;
    
    // Current Values
    float currentTemperature;
    float lastValidTemperature;
    float offset;
    
    // Statistics
    float minTemp;
    float maxTemp;
    float sumTemp;
    int sampleCount;
    
    // Status
    bool sensorReady;
    bool overheatDetected;
    
    // Internal Methods
    bool isValidTemperature(float temp);
    void updateStatistics(float temp);
    void checkOverheat(float temp);
    float clampTemperature(float temp);
};

#endif // SENSORS_H
