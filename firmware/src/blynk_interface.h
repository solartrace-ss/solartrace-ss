/*
 * ============================================================================
 * SOLARTRACE - Blynk Interface Module Header
 * ============================================================================
 * 
 * File      : blynk_interface.h
 * Purpose   : Blynk IoT platform communication interface
 * Team      : South Sudan - UbuntuNet Alliance Women Hackathon 2026
 * ============================================================================
 */

#ifndef BLYNK_INTERFACE_H
#define BLYNK_INTERFACE_H

#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>

// ============================================================================
// BLYNK VIRTUAL PIN DEFINITIONS
// ============================================================================

#define VP_MODE_SELECT     V0   // Mode selection (dropdown)
#define VP_TEMPERATURE     V1   // Temperature display (gauge)
#define VP_NOTIFICATION    V2   // Push notifications
#define VP_LOGGING_STATUS  V3   // Logging status (label)
#define VP_EMERGENCY_STOP  V4   // Emergency stop (button)
#define VP_CO2_SAVINGS     V5   // CO2 savings (label)
#define VP_TARGET_TEMP     V6   // Target temperature (label)
#define VP_SYSTEM_STATUS   V7   // System status (label)
#define VP_SESSION_ID      V8   // Session ID (label)

// ============================================================================
// BLYNK INTERFACE CLASS
// ============================================================================

class BlynkInterface {
public:
    // Constructor / Destructor
    BlynkInterface();
    ~BlynkInterface();
    
    // Initialization
    void begin(const char* authToken);
    void begin(const char* authToken, const char* ssid, const char* password);
    
    // Core Functions
    void run();
    bool isConnected();
    bool isWiFiConnected();
    
    // Data Update
    void updateTemperature(float temperature);
    void updateTargetTemperature(float temperature);
    void updateStatus(String status);
    void updateSessionID(String id);
    void updateCO2Savings(float co2);
    
    // Notifications
    void sendNotification(String message);
    void sendEmergencyAlert(float temperature);
    void sendModeChangeAlert(String mode);
    
    // Control
    void setEmergencyStop(bool active);
    bool getEmergencyStop();
    int getSelectedMode();
    
    // Status
    void printStatus();
    
private:
    // Internal State
    String authToken;
    bool connected;
    bool emergencyStopActive;
    int selectedMode;
    
    // Internal Methods
    void setupWiFi(const char* ssid, const char* password);
    void connectBlynk();
    void processNotifications();
};

#endif // BLYNK_INTERFACE_H
