/*
 * ============================================================================
 * SOLARTRACE - Data Logger Module Header
 * ============================================================================
 * 
 * File      : data_logger.h
 * Purpose   : SD card data logging interface
 * Team      : South Sudan - UbuntuNet Alliance Women Hackathon 2026
 * ============================================================================
 */

#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

// ============================================================================
// PIN DEFINITIONS
// ============================================================================

#define SD_CS        5        // GPIO5 - Chip Select
#define SD_SCK       18       // GPIO18 - SPI Clock
#define SD_MOSI      23       // GPIO23 - SPI Master Out
#define SD_MISO      19       // GPIO19 - SPI Master In

// ============================================================================
// LOGGING CONSTANTS
// ============================================================================

#define LOG_INTERVAL       30000   // 30 seconds between log entries
#define MAX_LOG_BUFFER     10      // Maximum buffer size
#define MAX_SESSION_ID     20      // Maximum session ID length

// ============================================================================
// DATA LOGGER CLASS
// ============================================================================

class DataLogger {
public:
    // Constructor / Destructor
    DataLogger();
    ~DataLogger();
    
    // Initialization
    void begin();
    void begin(String sessionID);
    void begin(int csPin);
    void begin(int csPin, String sessionID);
    
    // Core Functions
    void logData(float temperature, int mode);
    void logEvent(String event);
    void logSafetyEvent(float temperature);
    void logStartup(String sessionID, String version);
    void logShutdown();
    
    // Session Management
    void createSession();
    void closeSession();
    String generateSessionID();
    void setSessionID(String id);
    String getSessionID();
    
    // Data Retrieval
    String readLogs();
    String readLastNLogs(int n);
    String readLogsByDate(String date);
    
    // Buffer Management
    void flushBuffer();
    void clearBuffer();
    int getBufferSize();
    
    // Status
    bool isReady();
    bool isLogging();
    uint32_t getLogCount();
    uint32_t getFileSize();
    
    // Debug
    void printStatus();
    void printLogSummary();
    
private:
    // Internal State
    int csPin;
    String sessionID;
    String fileName;
    bool initialized;
    bool loggingActive;
    uint32_t logCount;
    
    // Buffer
    String logBuffer[MAX_LOG_BUFFER];
    int bufferIndex;
    
    // File
    File logFile;
    
    // Internal Methods
    bool initSD();
    bool openFile(String filename, bool append);
    void closeFile();
    void writeBufferToFile();
    String formatTimestamp(DateTime dt);
    String formatCSVLine(String timestamp, float temp, int mode);
    String getDefaultFileName();
    bool createDirectory(String path);
    void checkAndCreateDirectory();
};

#endif // DATA_LOGGER_H
