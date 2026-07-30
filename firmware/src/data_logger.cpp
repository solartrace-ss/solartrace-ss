/*
 * ============================================================================
 * SOLARTRACE - Data Logger Module Implementation
 * ============================================================================
 * 
 * File      : data_logger.cpp
 * Purpose   : SD card data logging implementation
 * Team      : South Sudan - UbuntuNet Alliance Women Hackathon 2026
 * ============================================================================
 */

#include "data_logger.h"
#include <RTClib.h>

// ============================================================================
// CONSTRUCTOR / DESTRUCTOR
// ============================================================================

DataLogger::DataLogger() {
    csPin = SD_CS;
    sessionID = "";
    fileName = "";
    initialized = false;
    loggingActive = false;
    logCount = 0;
    bufferIndex = 0;
    logFile = File();
    
    // Initialize buffer
    for (int i = 0; i < MAX_LOG_BUFFER; i++) {
        logBuffer[i] = "";
    }
}

DataLogger::~DataLogger() {
    closeSession();
}

// ============================================================================
// INITIALIZATION
// ============================================================================

void DataLogger::begin() {
    begin(sessionID);
}

void DataLogger::begin(String id) {
    sessionID = id;
    begin(csPin);
}

void DataLogger::begin(int pin) {
    csPin = pin;
    if (sessionID.length() == 0) {
        sessionID = generateSessionID();
    }
    begin(csPin, sessionID);
}

void DataLogger::begin(int pin, String id) {
    csPin = pin;
    sessionID = id;
    
    Serial.println("Initializing Data Logger...");
    
    // Initialize SD card
    if (!initSD()) {
        Serial.println("WARNING: SD Card initialization failed!");
        return;
    }
    
    // Create session
    createSession();
    
    // Set file name
    fileName = "/session_" + sessionID + ".csv";
    
    Serial.println("Data Logger initialized");
    printStatus();
}

// ============================================================================
// CORE FUNCTIONS
// ============================================================================

void DataLogger::logData(float temperature, int mode) {
    if (!loggingActive || !initialized) return;
    
    // Get current time
    RTC_DS3231 rtc;
    if (!rtc.begin()) {
        Serial.println("WARNING: RTC not available for logging");
        return;
    }
    
    DateTime now = rtc.now();
    
    // Format timestamp and log entry
    String timestamp = formatTimestamp(now);
    String logEntry = formatCSVLine(timestamp, temperature, mode);
    
    // Add to buffer
    logBuffer[bufferIndex % MAX_LOG_BUFFER] = logEntry;
    bufferIndex++;
    logCount++;
    
    // Flush if buffer is full
    if (bufferIndex % MAX_LOG_BUFFER == 0) {
        flushBuffer();
    }
}

void DataLogger::logEvent(String event) {
    if (!loggingActive || !initialized) return;
    
    RTC_DS3231 rtc;
    if (!rtc.begin()) return;
    
    DateTime now = rtc.now();
    String timestamp = formatTimestamp(now);
    String logEntry = timestamp + ",EVENT," + event + "," + sessionID;
    
    logBuffer[bufferIndex % MAX_LOG_BUFFER] = logEntry;
    bufferIndex++;
    logCount++;
    
    if (bufferIndex % MAX_LOG_BUFFER == 0) {
        flushBuffer();
    }
}

void DataLogger::logSafetyEvent(float temperature) {
    String event = "SAFETY: Temperature " + String(temperature) + "°C exceeded 130°C";
    logEvent(event);
}

void DataLogger::logStartup(String id, String version) {
    sessionID = id;
    String event = "STARTUP: Version " + version + " | Session " + id;
    logEvent(event);
    logEvent("--- Session Started ---");
}

void DataLogger::logShutdown() {
    logEvent("--- Session Ended ---");
    flushBuffer();
    closeSession();
}

// ============================================================================
// SESSION MANAGEMENT
// ============================================================================

void DataLogger::createSession() {
    if (!initialized) {
        Serial.println("ERROR: SD Card not initialized!");
        return;
    }
    
    checkAndCreateDirectory();
    
    String filename = getDefaultFileName();
    if (openFile(filename, false)) {
        // Write CSV header
        logFile.println("Timestamp,Temperature,Mode,SessionID,Event");
        logFile.flush();
        closeFile();
        fileName = filename;
        loggingActive = true;
        Serial.println("Session created: " + filename);
    } else {
        Serial.println("ERROR: Could not create session file!");
    }
}

void DataLogger::closeSession() {
    if (loggingActive) {
        flushBuffer();
        closeFile();
        loggingActive = false;
        Serial.println("Session closed");
    }
}

String DataLogger::generateSessionID() {
    RTC_DS3231 rtc;
    if (rtc.begin()) {
        DateTime now = rtc.now();
        String id = String(now.year()) +
                    String(now.month()) +
                    String(now.day()) +
                    String(now.hour()) +
                    String(now.minute()) +
                    String(random(1000, 9999));
        return id;
    }
    
    // Fallback: use millis and random
    return String(millis()) + String(random(1000, 9999));
}

void DataLogger::setSessionID(String id) {
    sessionID = id;
}

String DataLogger::getSessionID() {
    return sessionID;
}

// ============================================================================
// DATA RETRIEVAL
// ============================================================================

String DataLogger::readLogs() {
    if (!initialized) return "";
    
    if (!openFile(fileName, false)) {
        return "";
    }
    
    String content = "";
    while (logFile.available()) {
        content += logFile.readStringUntil('\n');
    }
    closeFile();
    
    return content;
}

String DataLogger::readLastNLogs(int n) {
    // This would require reading from end of file
    // Simplified implementation
    return "";
}

String DataLogger::readLogsByDate(String date) {
    // Filter logs by date
    // Simplified implementation
    return "";
}

// ============================================================================
// BUFFER MANAGEMENT
// ============================================================================

void DataLogger::flushBuffer() {
    if (!loggingActive || !initialized) return;
    
    writeBufferToFile();
    clearBuffer();
}

void DataLogger::clearBuffer() {
    for (int i = 0; i < MAX_LOG_BUFFER; i++) {
        logBuffer[i] = "";
    }
    bufferIndex = 0;
}

int DataLogger::getBufferSize() {
    return bufferIndex;
}

// ============================================================================
// STATUS
// ============================================================================

bool DataLogger::isReady() {
    return initialized;
}

bool DataLogger::isLogging() {
    return loggingActive;
}

uint32_t DataLogger::getLogCount() {
    return logCount;
}

uint32_t DataLogger::getFileSize() {
    if (!initialized) return 0;
    
    if (openFile(fileName, false)) {
        uint32_t size = logFile.size();
        closeFile();
        return size;
    }
    return 0;
}

// ============================================================================
// DEBUG
// ============================================================================

void DataLogger::printStatus() {
    Serial.println("=== Data Logger Status ===");
    Serial.print("Initialized: ");
    Serial.println(initialized ? "YES" : "NO");
    Serial.print("Logging: ");
    Serial.println(loggingActive ? "YES" : "NO");
    Serial.print("Session ID: ");
    Serial.println(sessionID);
    Serial.print("File: ");
    Serial.println(fileName);
    Serial.print("Log Count: ");
    Serial.println(logCount);
    Serial.print("Buffer Size: ");
    Serial.println(bufferIndex);
    Serial.print("File Size: ");
    Serial.print(getFileSize());
    Serial.println(" bytes");
    Serial.println("==========================");
}

void DataLogger::printLogSummary() {
    Serial.println("=== Log Summary ===");
    Serial.print("Session: ");
    Serial.println(sessionID);
    Serial.print("Total Logs: ");
    Serial.println(logCount);
    Serial.print("Log File: ");
    Serial.println(fileName);
    Serial.print("File Size: ");
    Serial.print(getFileSize());
    Serial.println(" bytes");
    Serial.println("===================");
}

// ============================================================================
// INTERNAL METHODS
// ============================================================================

bool DataLogger::initSD() {
    Serial.println("Initializing SD Card...");
    
    // Initialize SPI for SD card
    SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    
    if (!SD.begin(csPin)) {
        Serial.println("SD Card initialization failed!");
        initialized = false;
        return false;
    }
    
    // Check card type
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE) {
        Serial.println("No SD card attached!");
        initialized = false;
        return false;
    }
    
    initialized = true;
    Serial.println("SD Card initialized successfully");
    return true;
}

bool DataLogger::openFile(String filename, bool append) {
    if (!initialized) return false;
    
    if (append) {
        logFile = SD.open(filename, FILE_APPEND);
    } else {
        logFile = SD.open(filename, FILE_WRITE);
    }
    
    return logFile;
}

void DataLogger::closeFile() {
    if (logFile) {
        logFile.flush();
        logFile.close();
    }
}

void DataLogger::writeBufferToFile() {
    if (!loggingActive || !initialized) return;
    
    if (!openFile(fileName, true)) {
        Serial.println("ERROR: Could not open file for writing!");
        return;
    }
    
    for (int i = 0; i < MAX_LOG_BUFFER; i++) {
        if (logBuffer[i] != "") {
            logFile.println(logBuffer[i]);
            logBuffer[i] = "";
        }
    }
    
    logFile.flush();
    closeFile();
}

String DataLogger::formatTimestamp(DateTime dt) {
    String timestamp = String(dt.year()) + "-" +
                       String(dt.month()) + "-" +
                       String(dt.day()) + " " +
                       String(dt.hour()) + ":" +
                       String(dt.minute()) + ":" +
                       String(dt.second());
    return timestamp;
}

String DataLogger::formatCSVLine(String timestamp, float temp, int mode) {
    String line = timestamp + "," +
                  String(temp) + "," +
                  String(mode) + "," +
                  sessionID + ",";
    return line;
}

String DataLogger::getDefaultFileName() {
    return "/session_" + sessionID + ".csv";
}

bool DataLogger::createDirectory(String path) {
    if (!initialized) return false;
    
    if (SD.exists(path)) {
        return true;
    }
    
    return SD.mkdir(path);
}

void DataLogger::checkAndCreateDirectory() {
    // Create logs directory if it doesn't exist
    if (!SD.exists("/logs")) {
        SD.mkdir("/logs");
    }
}
