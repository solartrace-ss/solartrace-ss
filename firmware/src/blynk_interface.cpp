/*
 * ============================================================================
 * SOLARTRACE - Blynk Interface Module Implementation
 * ============================================================================
 * 
 * File      : blynk_interface.cpp
 * Purpose   : Blynk IoT platform communication implementation
 * Team      : South Sudan - UbuntuNet Alliance Women Hackathon 2026
 * ============================================================================
 */

#include "blynk_interface.h"

// ============================================================================
// CONSTRUCTOR / DESTRUCTOR
// ============================================================================

BlynkInterface::BlynkInterface() {
    authToken = "";
    connected = false;
    emergencyStopActive = false;
    selectedMode = -1;
}

BlynkInterface::~BlynkInterface() {
    // Nothing to clean up
}

// ============================================================================
// INITIALIZATION
// ============================================================================

void BlynkInterface::begin(const char* token) {
    authToken = token;
    Serial.println("Initializing Blynk Interface...");
    
    // Setup Blynk
    Blynk.config(token);
    connectBlynk();
    
    // Send initial values
    updateTemperature(0.0);
    updateStatus("INIT");
    updateSessionID("N/A");
    updateCO2Savings(0.0);
    setEmergencyStop(false);
    
    Serial.println("Blynk Interface initialized");
}

void BlynkInterface::begin(const char* token, const char* ssid, const char* password) {
    authToken = token;
    Serial.println("Initializing Blynk with WiFi...");
    
    // Setup WiFi
    setupWiFi(ssid, password);
    
    // Setup Blynk
    Blynk.config(token);
    connectBlynk();
    
    // Send initial values
    updateTemperature(0.0);
    updateStatus("INIT");
    updateSessionID("N/A");
    updateCO2Savings(0.0);
    setEmergencyStop(false);
    
    Serial.println("Blynk Interface initialized");
}

// ============================================================================
// CORE FUNCTIONS
// ============================================================================

void BlynkInterface::run() {
    if (connected) {
        Blynk.run();
    }
}

bool BlynkInterface::isConnected() {
    return connected && Blynk.connected();
}

bool BlynkInterface::isWiFiConnected() {
    return WiFi.status() == WL_CONNECTED;
}

// ============================================================================
// DATA UPDATE
// ============================================================================

void BlynkInterface::updateTemperature(float temperature) {
    Blynk.virtualWrite(VP_TEMPERATURE, temperature);
}

void BlynkInterface::updateTargetTemperature(float temperature) {
    Blynk.virtualWrite(VP_TARGET_TEMP, String(temperature) + "°C");
}

void BlynkInterface::updateStatus(String status) {
    Blynk.virtualWrite(VP_SYSTEM_STATUS, status);
}

void BlynkInterface::updateSessionID(String id) {
    Blynk.virtualWrite(VP_SESSION_ID, id);
}

void BlynkInterface::updateCO2Savings(float co2) {
    Blynk.virtualWrite(VP_CO2_SAVINGS, String(co2, 3) + " tons");
}

// ============================================================================
// NOTIFICATIONS
// ============================================================================

void BlynkInterface::sendNotification(String message) {
    // Send via Blynk
    Blynk.virtualWrite(VP_NOTIFICATION, message);
    
    // Also print to serial
    Serial.print("[NOTIFICATION] ");
    Serial.println(message);
}

void BlynkInterface::sendEmergencyAlert(float temperature) {
    String alert = "!!!!! EMERGENCY: Temperature " + String(temperature) + "°C !!!!!";
    Blynk.virtualWrite(VP_NOTIFICATION, alert);
    Serial.println("!!!!! " + alert + " !!!!!");
}

void BlynkInterface::sendModeChangeAlert(String mode) {
    String message = "Mode changed to: " + mode;
    Blynk.virtualWrite(VP_NOTIFICATION, message);
    Serial.println(message);
}

// ============================================================================
// CONTROL
// ============================================================================

void BlynkInterface::setEmergencyStop(bool active) {
    emergencyStopActive = active;
    Blynk.virtualWrite(VP_EMERGENCY_STOP, active ? 1 : 0);
}

bool BlynkInterface::getEmergencyStop() {
    return emergencyStopActive;
}

int BlynkInterface::getSelectedMode() {
    return selectedMode;
}

// ============================================================================
// STATUS
// ============================================================================

void BlynkInterface::printStatus() {
    Serial.println("=== Blynk Interface Status ===");
    Serial.print("Connected: ");
    Serial.println(connected ? "YES" : "NO");
    Serial.print("WiFi: ");
    Serial.println(isWiFiConnected() ? "Connected" : "Disconnected");
    Serial.print("Emergency Stop: ");
    Serial.println(emergencyStopActive ? "ACTIVE" : "INACTIVE");
    Serial.print("Selected Mode: ");
    Serial.println(selectedMode);
    Serial.println("==============================");
}

// ============================================================================
// INTERNAL METHODS
// ============================================================================

void BlynkInterface::setupWiFi(const char* ssid, const char* password) {
    Serial.println("Connecting to WiFi...");
    
    WiFi.begin(ssid, password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nWARNING: WiFi connection failed!");
    }
}

void BlynkInterface::connectBlynk() {
    Serial.println("Connecting to Blynk...");
    
    if (authToken.length() == 0) {
        Serial.println("ERROR: No auth token provided!");
        connected = false;
        return;
    }
    
    Blynk.config(authToken.c_str());
    
    // Wait for connection
    int attempts = 0;
    while (!Blynk.connected() && attempts < 10) {
        Blynk.connect();
        delay(1000);
        attempts++;
        Serial.print(".");
    }
    
    if (Blynk.connected()) {
        connected = true;
        Serial.println("\nBlynk connected!");
    } else {
        connected = false;
        Serial.println("\nWARNING: Blynk connection failed!");
    }
}

void BlynkInterface::processNotifications() {
    // Process any pending notifications
    // This is handled by Blynk internally
}
