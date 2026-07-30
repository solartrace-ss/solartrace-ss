/*
 * ============================================================================
 * SOLARTRACE - Smart Solar Cooker with RTC-Based Automatic Sun Tracking
 * ============================================================================
 * 
 * Project   : SolarTrace
 * Version   : 1.0
 * Date      : July 2026
 * Team      : South Sudan - UbuntuNet Alliance Women Hackathon 2026
 * 
 * Description:
 * This firmware implements a smart solar cooker with automatic sun tracking
 * using an ESP32 microcontroller, DS3231 RTC module, MAX6675 thermocouple,
 * and MG995 servo motor. The system supports 4 cooking modes and communicates
 * with the Blynk IoT platform for remote monitoring and control.
 * 
 * ============================================================================
 * MODES:
 *   0 - COOKING      : 80-100°C  (General cooking)
 *   1 - STERILIZATION : 120°C    (Hold for 20 minutes)
 *   2 - BOIL_WATER   : 100°C     (Alert when reached)
 *   3 - WARMING      : 70°C      (Keep warm)
 *   4 - SAFETY       : N/A       (Emergency override)
 * ============================================================================
 */

#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <MAX6675.h>
#include <Servo.h>
#include <SD.h>
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <EEPROM.h>

// ============================================================================
// CONFIGURATION - WIFI AND BLYNK
// ============================================================================

// WiFi Credentials
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Blynk Authentication Token
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";

// ============================================================================
// BLYNK VIRTUAL PINS
// ============================================================================

#define VP_MODE_SELECT     V0   // Mode selection dropdown
#define VP_TEMPERATURE     V1   // Temperature display gauge
#define VP_NOTIFICATION    V2   // Push notifications
#define VP_LOGGING_STATUS  V3   // Logging status
#define VP_EMERGENCY_STOP  V4   // Emergency stop button
#define VP_CO2_SAVINGS     V5   // CO2 savings display

// ============================================================================
// PIN DEFINITIONS
// ============================================================================

// RTC - I2C (SDA = GPIO21, SCL = GPIO22)
// No additional pins needed for I2C

// MAX6675 Thermocouple
#define THERMO_CS   15      // Chip Select
#define THERMO_SCK  14      // SPI Clock
#define THERMO_SO   12      // SPI Data Out

// MG995 Servo Motor
#define SERVO_PIN   13      // PWM Signal

// MicroSD Card Module (SPI)
#define SD_CS       5       // Chip Select
#define SD_SCK      18      // SPI Clock
#define SD_MOSI     23      // SPI Master Out
#define SD_MISO     19      // SPI Master In

// ============================================================================
// GLOBAL OBJECTS
// ============================================================================

RTC_DS3231 rtc;
MAX6675 thermocouple(THERMO_SCK, THERMO_CS, THERMO_SO);
Servo servoMotor;
File logFile;

// ============================================================================
// CONSTANTS AND MACROS
// ============================================================================

// Solar Parameters (Juba, South Sudan - 4.85°N)
#define LATITUDE               4.85
#define SUNRISE_TIME           390     // 6:30 AM in minutes from midnight
#define SUNSET_TIME            1080    // 6:00 PM in minutes from midnight
#define TOTAL_DAYLIGHT         690     // 11.5 hours in minutes
#define SUN_MOVEMENT_PER_HOUR  15.0    // Degrees per hour
#define SERVO_STEP_INTERVAL    10      // Minutes between servo adjustments
#define SERVO_STEP_ANGLE       2.5     // Degrees per step

// Temperature Constants
#define MAX_SAFE_TEMP          130.0   // Maximum safe temperature (°C)
#define TEMP_READ_INTERVAL     500     // Milliseconds between temp readings
#define STERILIZATION_TEMP     120.0   // Sterilization target temperature
#define STERILIZATION_HOLD     20      // Minutes to hold sterilization temp
#define BOIL_TEMP              100.0   // Boiling point
#define WARMING_TEMP           70.0    // Warming target temperature

// Mode Constants
#define MODE_IDLE               -1
#define MODE_COOKING            0
#define MODE_STERILIZATION      1
#define MODE_BOIL_WATER         2
#define MODE_WARMING            3
#define MODE_SAFETY             4

// State Constants
#define STATE_IDLE              0
#define STATE_RUNNING           1
#define STATE_SAFETY            2
#define STATE_ERROR             3

// SD Card Constants
#define LOG_INTERVAL            30000   // 30 seconds between log entries
#define MAX_LOG_BUFFER          10

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

// System State
int currentMode = MODE_IDLE;
int systemState = STATE_IDLE;
float targetTemperature = 0.0;
float currentTemperature = 0.0;
bool isSafetyActive = false;
bool isHeating = false;
bool isLogging = false;
bool isSterilizing = false;

// Timing Variables
unsigned long lastTempRead = 0;
unsigned long lastLogEntry = 0;
unsigned long sterilizationStartTime = 0;
unsigned long lastServoMove = 0;

// Session Variables
String sessionID = "";
int sessionCount = 0;
float maxTempReached = 0.0;
float co2Saved = 0.0;
int cookingTimeMinutes = 0;

// Log Buffer
String logBuffer[MAX_LOG_BUFFER];
int logBufferIndex = 0;

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

void setupSystem();
void setupRTC();
void setupSDCard();
void setupBlynk();
void setupServo();

void loopSystem();
void handleModeExecution();
void handleSafetyCheck();
void handleTemperatureMonitoring();
void handleServoPositioning();

float calculateSunAngle();
float readTemperature();
void moveServoToAngle(float angle);
void logData(float temp, int mode);
void flushLogBuffer();

void engageSafetyMode();
void disengageSafetyMode();
void emergencyStop();

void startSterilization();
void checkSterilizationComplete();

void sendNotification(String message);
void updateBlynkDashboard();

String generateSessionID();

// ============================================================================
// BLYNK WIDGET HANDLERS
// ============================================================================

/**
 * Blynk Widget: Mode Selection (V0)
 * Called when user selects a mode from the Blynk dropdown
 */
BLYNK_WRITE(VP_MODE_SELECT) {
    int mode = param.asInt();
    if (mode >= MODE_COOKING && mode <= MODE_WARMING) {
        currentMode = mode;
        setMode(mode);
        Blynk.virtualWrite(VP_LOGGING_STATUS, "Mode: " + String(mode));
        sendNotification("Mode changed to: " + getModeName(mode));
    }
}

/**
 * Blynk Widget: Emergency Stop (V4)
 * Called when user presses the emergency stop button
 */
BLYNK_WRITE(VP_EMERGENCY_STOP) {
    if (param.asInt() == 1) {
        emergencyStop();
        Blynk.virtualWrite(VP_EMERGENCY_STOP, 0);  // Reset button
    }
}

// ============================================================================
// MAIN SETUP FUNCTION
// ============================================================================

void setup() {
    // Initialize Serial
    Serial.begin(115200);
    Serial.println("\n\n========================================");
    Serial.println("  SOLARTRACE - Smart Solar Cooker");
    Serial.println("  Team South Sudan - Hackathon 2026");
    Serial.println("========================================\n");
    
    // Setup all subsystems
    setupSystem();
    setupRTC();
    setupSDCard();
    setupServo();
    setupBlynk();
    
    // Generate session ID
    sessionID = generateSessionID();
    
    // Initial servo position (sunrise position)
    moveServoToAngle(0);
    
    // Set initial state
    systemState = STATE_IDLE;
    currentMode = MODE_IDLE;
    
    // Log startup
    logData(0, MODE_IDLE);
    
    Serial.println("SolarTrace initialized successfully!");
    Serial.println("Session ID: " + sessionID);
    Serial.println("Waiting for mode selection...\n");
    
    // Send startup notification
    sendNotification("SolarTrace system ready");
}

// ============================================================================
// MAIN LOOP FUNCTION
// ============================================================================

void loop() {
    // Run Blynk
    Blynk.run();
    
    // Get current time
    DateTime now = rtc.now();
    
    // ========================================
    // 1. TEMPERATURE MONITORING
    // ========================================
    if (millis() - lastTempRead >= TEMP_READ_INTERVAL) {
        lastTempRead = millis();
        currentTemperature = readTemperature();
        
        // Update Blynk dashboard
        Blynk.virtualWrite(VP_TEMPERATURE, currentTemperature);
        
        // Track max temperature
        if (currentTemperature > maxTempReached) {
            maxTempReached = currentTemperature;
        }
    }
    
    // ========================================
    // 2. SAFETY CHECK (HIGHEST PRIORITY)
    // ========================================
    handleSafetyCheck();
    
    // ========================================
    // 3. MODE EXECUTION
    // ========================================
    if (systemState == STATE_RUNNING && !isSafetyActive) {
        handleModeExecution();
    }
    
    // ========================================
    // 4. SUN TRACKING
    // ========================================
    if (systemState == STATE_RUNNING) {
        handleServoPositioning();
    }
    
    // ========================================
    // 5. DATA LOGGING
    // ========================================
    if (millis() - lastLogEntry >= LOG_INTERVAL) {
        lastLogEntry = millis();
        logData(currentTemperature, currentMode);
    }
    
    // ========================================
    // 6. UPDATE DASHBOARD
    // ========================================
    if (millis() % 10000 < 100) {  // Every 10 seconds
        updateBlynkDashboard();
    }
}

// ============================================================================
// SYSTEM SETUP FUNCTIONS
// ============================================================================

/**
 * Setup System - Initialize core components
 */
void setupSystem() {
    Serial.println("Initializing system...");
    
    // Initialize I2C
    Wire.begin();
    
    // Initialize SPI
    SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    
    // Initialize EEPROM (for storing settings)
    EEPROM.begin(512);
    
    // Set default target temperatures based on mode
    targetTemperature = 0;
    
    Serial.println("System initialized");
}

/**
 * Setup RTC - Initialize DS3231 Real-Time Clock
 */
void setupRTC() {
    Serial.println("Initializing RTC...");
    
    if (!rtc.begin()) {
        Serial.println("ERROR: Could not find RTC module!");
        Serial.println("Check I2C connections (SDA=GPIO21, SCL=GPIO22)");
        systemState = STATE_ERROR;
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
    Serial.println(now.minute());
}

/**
 * Setup SD Card - Initialize MicroSD Card Storage
 */
void setupSDCard() {
    Serial.println("Initializing SD Card...");
    
    if (!SD.begin(SD_CS)) {
        Serial.println("WARNING: SD Card initialization failed!");
        Serial.println("Check connections (CS=GPIO5, SCK=GPIO18, MOSI=GPIO23, MISO=GPIO19)");
        isLogging = false;
        return;
    }
    
    // Check SD card type
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE) {
        Serial.println("WARNING: No SD card attached!");
        isLogging = false;
        return;
    }
    
    // Create session file
    String fileName = "/session_" + sessionID + ".csv";
    logFile = SD.open(fileName, FILE_WRITE);
    
    if (logFile) {
        // Write CSV header
        logFile.println("Timestamp,Temperature,Mode,SessionID");
        logFile.close();
        isLogging = true;
        Serial.println("SD Card initialized. Session file: " + fileName);
    } else {
        Serial.println("WARNING: Could not create log file!");
        isLogging = false;
    }
}

/**
 * Setup Servo - Initialize MG995 Servo Motor
 */
void setupServo() {
    Serial.println("Initializing Servo...");
    
    servoMotor.attach(SERVO_PIN);
    servoMotor.write(0);
    
    Serial.println("Servo initialized at 0°");
}

/**
 * Setup Blynk - Initialize Blynk IoT Platform
 */
void setupBlynk() {
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
        
        Serial.println("Connecting to Blynk...");
        Blynk.config(auth);
        Blynk.connect();
        Serial.println("Blynk connected!");
    } else {
        Serial.println("\nWARNING: WiFi connection failed!");
        Serial.println("System will run in offline mode.");
    }
}

// ============================================================================
// MODE EXECUTION FUNCTIONS
// ============================================================================

/**
 * Handle Mode Execution - Execute the selected cooking mode
 */
void handleModeExecution() {
    // If no mode selected, do nothing
    if (currentMode == MODE_IDLE) {
        return;
    }
    
    // If system is in safety mode, prevent mode execution
    if (isSafetyActive) {
        return;
    }
    
    switch (currentMode) {
        case MODE_COOKING:
            // Cooking mode: Maintain 80-100°C
            targetTemperature = 90.0;  // Mid-range
            if (currentTemperature >= 100.0) {
                isHeating = false;
                sendNotification("Cooking temperature reached: " + String(currentTemperature) + "°C");
            } else if (currentTemperature < 80.0) {
                isHeating = true;
            }
            break;
            
        case MODE_STERILIZATION:
            // Sterilization mode: Maintain 120°C for 20 minutes
            targetTemperature = STERILIZATION_TEMP;
            
            if (!isSterilizing) {
                // Start sterilization process
                if (currentTemperature >= STERILIZATION_TEMP) {
                    startSterilization();
                } else {
                    isHeating = true;
                    sendNotification("Heating to 120°C for sterilization...");
                }
            } else {
                // Check if sterilization is complete
                checkSterilizationComplete();
            }
            break;
            
        case MODE_BOIL_WATER:
            // Boil water mode: Heat to 100°C and alert
            targetTemperature = BOIL_TEMP;
            
            if (currentTemperature >= BOIL_TEMP) {
                isHeating = false;
                sendNotification("Water is boiling! (100°C)");
                // Auto-switch to warming mode after boiling
                // currentMode = MODE_WARMING;
            } else {
                isHeating = true;
            }
            break;
            
        case MODE_WARMING:
            // Warming mode: Maintain 70°C
            targetTemperature = WARMING_TEMP;
            
            if (currentTemperature >= WARMING_TEMP + 5) {
                isHeating = false;
            } else if (currentTemperature < WARMING_TEMP - 5) {
                isHeating = true;
            }
            break;
            
        default:
            break;
    }
}

/**
 * Set Mode - Change the current cooking mode
 */
void setMode(int mode) {
    currentMode = mode;
    
    // Reset sterilization state
    isSterilizing = false;
    sterilizationStartTime = 0;
    
    // Set system state to running
    systemState = STATE_RUNNING;
    
    // Update target temperature based on mode
    switch (mode) {
        case MODE_COOKING:
            targetTemperature = 90.0;
            sendNotification("Cooking mode activated (80-100°C)");
            break;
        case MODE_STERILIZATION:
            targetTemperature = STERILIZATION_TEMP;
            sendNotification("Sterilization mode activated (120°C / 20 min)");
            break;
        case MODE_BOIL_WATER:
            targetTemperature = BOIL_TEMP;
            sendNotification("Boil water mode activated (100°C)");
            break;
        case MODE_WARMING:
            targetTemperature = WARMING_TEMP;
            sendNotification("Warming mode activated (70°C)");
            break;
        default:
            break;
    }
    
    Serial.print("Mode set to: ");
    Serial.println(getModeName(mode));
}

/**
 * Get Mode Name - Convert mode number to string
 */
String getModeName(int mode) {
    switch (mode) {
        case MODE_IDLE:          return "IDLE";
        case MODE_COOKING:       return "COOKING";
        case MODE_STERILIZATION: return "STERILIZATION";
        case MODE_BOIL_WATER:    return "BOIL_WATER";
        case MODE_WARMING:       return "WARMING";
        case MODE_SAFETY:        return "SAFETY";
        default:                 return "UNKNOWN";
    }
}

// ============================================================================
// SUN TRACKING FUNCTIONS
// ============================================================================

/**
 * Handle Servo Positioning - Move servo based on time
 */
void handleServoPositioning() {
    // Only move servo every SERVO_STEP_INTERVAL minutes
    if (millis() - lastServoMove < SERVO_STEP_INTERVAL * 60000) {
        return;
    }
    lastServoMove = millis();
    
    // Calculate sun angle
    float angle = calculateSunAngle();
    
    // Move servo to calculated angle
    moveServoToAngle(angle);
    
    Serial.print("Sun angle: ");
    Serial.print(angle);
    Serial.println("°");
}

/**
 * Calculate Sun Angle - Calculate solar angle based on RTC time
 * 
 * Formula: angle = (minutes_since_sunrise / total_daylight) × 120°
 * 
 * @return float Sun angle in degrees (0-120)
 */
float calculateSunAngle() {
    DateTime now = rtc.now();
    
    // Get current time in minutes from midnight
    int currentMinutes = now.hour() * 60 + now.minute();
    
    // Calculate minutes since sunrise
    int minutesSinceSunrise = currentMinutes - SUNRISE_TIME;
    
    // If before sunrise or after sunset, return 0 (idle position)
    if (minutesSinceSunrise < 0 || currentMinutes > SUNSET_TIME) {
        return 0;
    }
    
    // Calculate angle: (minutes_since_sunrise / total_daylight) × 120°
    float angle = ((float)minutesSinceSunrise / TOTAL_DAYLIGHT) * 120.0;
    
    // Clamp angle to valid range
    if (angle < 0) angle = 0;
    if (angle > 120) angle = 120;
    
    return angle;
}

/**
 * Move Servo to Angle - Position the servo at the given angle
 * 
 * @param angle Target angle in degrees (0-180)
 */
void moveServoToAngle(float angle) {
    // Clamp angle
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;
    
    servoMotor.write((int)angle);
    delay(15);  // Allow servo to move
}

// ============================================================================
// TEMPERATURE FUNCTIONS
// ============================================================================

/**
 * Read Temperature - Read temperature from MAX6675 thermocouple
 * 
 * @return float Temperature in Celsius (-1 if error)
 */
float readTemperature() {
    float temp = thermocouple.readCelsius();
    
    // Check for sensor error
    if (isnan(temp) || temp < -10 || temp > 500) {
        Serial.println("WARNING: Temperature sensor error!");
        return currentTemperature;  // Return last valid reading
    }
    
    return temp;
}

// ============================================================================
// STERILIZATION FUNCTIONS
// ============================================================================

/**
 * Start Sterilization - Begin the sterilization hold cycle
 */
void startSterilization() {
    isSterilizing = true;
    sterilizationStartTime = millis();
    sendNotification("Sterilization started - holding 120°C for 20 minutes");
    Serial.println("Sterilization started - 20 minute hold");
}

/**
 * Check Sterilization Complete - Verify if 20 minutes have elapsed
 */
void checkSterilizationComplete() {
    unsigned long elapsedMinutes = (millis() - sterilizationStartTime) / 60000;
    
    if (elapsedMinutes >= STERILIZATION_HOLD) {
        isSterilizing = false;
        isHeating = false;
        sendNotification("Sterilization complete! Instruments are sterile.");
        Serial.println("Sterilization complete!");
        
        // Switch to warming mode
        currentMode = MODE_WARMING;
        targetTemperature = WARMING_TEMP;
    } else {
        // Still sterilizing - maintain temperature
        isHeating = true;
        
        // Send progress update every 5 minutes
        if (elapsedMinutes % 5 == 0 && elapsedMinutes > 0) {
            String progress = "Sterilization: " + String(elapsedMinutes) + "/20 minutes";
            sendNotification(progress);
            Serial.println(progress);
        }
    }
}

// ============================================================================
// SAFETY FUNCTIONS
// ============================================================================

/**
 * Handle Safety Check - Monitor for safety conditions (HIGHEST PRIORITY)
 * 
 * This function is called every loop iteration and has the highest priority.
 * If the temperature exceeds MAX_SAFE_TEMP (130°C), safety mode is activated.
 */
void handleSafetyCheck() {
    // Check overheat condition
    if (currentTemperature > MAX_SAFE_TEMP && !isSafetyActive) {
        Serial.println("!!!!! OVERHEAT DETECTED !!!!!");
        Serial.print("Temperature: ");
        Serial.print(currentTemperature);
        Serial.println("°C");
        
        engageSafetyMode();
        return;
    }
    
    // If safety is active and temperature drops below safe level, allow reset
    if (isSafetyActive && currentTemperature < MAX_SAFE_TEMP - 10) {
        Serial.println("Temperature safe - disengaging safety mode");
        disengageSafetyMode();
    }
}

/**
 * Engage Safety Mode - Activate safety protocols
 */
void engageSafetyMode() {
    isSafetyActive = true;
    systemState = STATE_SAFETY;
    
    // Move reflector to idle position
    moveServoToAngle(0);
    
    // Stop heating
    isHeating = false;
    
    // Send emergency notification
    String alert = "EMERGENCY: Temperature exceeded " + String(MAX_SAFE_TEMP) + "°C!";
    sendNotification(alert);
    Blynk.virtualWrite(VP_EMERGENCY_STOP, 1);
    
    // Log safety event
    logData(currentTemperature, MODE_SAFETY);
    
    Serial.println("SAFETY MODE ENGAGED");
    Serial.println("Reflector moved to idle position");
}

/**
 * Disengage Safety Mode - Deactivate safety protocols
 */
void disengageSafetyMode() {
    isSafetyActive = false;
    systemState = STATE_RUNNING;
    
    // Resume normal operation
    if (currentMode != MODE_IDLE) {
        setMode(currentMode);
    }
    
    sendNotification("Safety mode disengaged - resuming operation");
    Serial.println("Safety mode disengaged");
}

/**
 * Emergency Stop - Emergency stop handler
 */
void emergencyStop() {
    Serial.println("!!!!! EMERGENCY STOP ACTIVATED !!!!!");
    
    // Move reflector to idle position
    moveServoToAngle(0);
    
    // Stop heating
    isHeating = false;
    isSterilizing = false;
    
    // Engage safety mode
    isSafetyActive = true;
    systemState = STATE_SAFETY;
    currentMode = MODE_SAFETY;
    
    // Send notification
    sendNotification("EMERGENCY STOP - System halted");
    Blynk.virtualWrite(VP_EMERGENCY_STOP, 1);
    
    // Log emergency event
    logData(currentTemperature, MODE_SAFETY);
}

// ============================================================================
// DATA LOGGING FUNCTIONS
// ============================================================================

/**
 * Log Data - Log data to SD card and buffer
 * 
 * @param temp Current temperature
 * @param mode Current mode
 */
void logData(float temp, int mode) {
    if (!isLogging) return;
    
    // Get current time
    DateTime now = rtc.now();
    
    // Format timestamp
    String timestamp = String(now.year()) + "-" +
                       String(now.month()) + "-" +
                       String(now.day()) + " " +
                       String(now.hour()) + ":" +
                       String(now.minute()) + ":" +
                       String(now.second());
    
    // Format log entry
    String logEntry = timestamp + "," +
                      String(temp) + "," +
                      String(mode) + "," +
                      sessionID;
    
    // Add to buffer
    logBuffer[logBufferIndex % MAX_LOG_BUFFER] = logEntry;
    logBufferIndex++;
    
    // Flush if buffer is full
    if (logBufferIndex % MAX_LOG_BUFFER == 0) {
        flushLogBuffer();
    }
}

/**
 * Flush Log Buffer - Write buffered logs to SD card
 */
void flushLogBuffer() {
    if (!isLogging) return;
    
    logFile = SD.open("/session_" + sessionID + ".csv", FILE_APPEND);
    
    if (logFile) {
        for (int i = 0; i < MAX_LOG_BUFFER && i < logBufferIndex; i++) {
            if (logBuffer[i] != "") {
                logFile.println(logBuffer[i]);
                logBuffer[i] = "";
            }
        }
        logFile.close();
    }
}

/**
 * Generate Session ID - Create unique session identifier
 */
String generateSessionID() {
    DateTime now = rtc.now();
    String id = String(now.year()) +
                String(now.month()) +
                String(now.day()) +
                String(now.hour()) +
                String(now.minute()) +
                String(random(1000, 9999));
    return id;
}

// ============================================================================
// NOTIFICATION FUNCTIONS
// ============================================================================

/**
 * Send Notification - Send push notification via Blynk
 * 
 * @param message Notification message
 */
void sendNotification(String message) {
    // Send via Blynk
    Blynk.virtualWrite(VP_NOTIFICATION, message);
    
    // Also print to serial
    Serial.print("[NOTIFICATION] ");
    Serial.println(message);
}

// ============================================================================
// BLYNK DASHBOARD UPDATE
// ============================================================================

/**
 * Update Blynk Dashboard - Update all dashboard widgets
 */
void updateBlynkDashboard() {
    Blynk.virtualWrite(VP_TEMPERATURE, currentTemperature);
    Blynk.virtualWrite(VP_LOGGING_STATUS, getModeName(currentMode));
    
    // Calculate CO2 savings
    // Assume 1 ton CO2 per household per year with charcoal
    // 1 ton = 1000 kg / 365 days = 2.74 kg per day
    co2Saved = sessionCount * 2.74 / 1000.0;  // Convert to tons
    Blynk.virtualWrite(VP_CO2_SAVINGS, co2Saved);
}

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

/**
 * Get Mode Name - Convert mode integer to string
 * (Already defined above - included for completeness)
 */

// ============================================================================
// END OF FILE
// ============================================================================
