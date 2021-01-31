//
// Created by Ethan on 9/14/2019.
//

#include "Log.h"
using std::string;
using std::cout;
using std::endl;

const string os_logging::Log::DEFAULT_LOG_FILE_NAME = "log";

string os_logging::Log::getTimeStamp() {
    // Setup for ctime()
    time_t raw_time;
    time(&raw_time);

    return string(ctime(&raw_time));
}

// Start Constructors
os_logging::Log::Log() {
    setLogfileName(getDefaultLogfileName());
}

os_logging::Log::Log(char *name) {
    setLogfileName(string(name));
}

os_logging::Log::Log(string name) {
    setLogfileName(std::move(name));
}
// End Constructors

// Start Getters/Setters
void os_logging::Log::setLogfileName(string name) {
    logFileName = std::move(name);
}

string os_logging::Log::getLogfileName() const {
    return logFileName;
}

string os_logging::Log::getDefaultLogfileName() {
    return DEFAULT_LOG_FILE_NAME;
}
// End Getters/Setters

int os_logging::Log::open() {
    // Open logfile with to append to current file if it exists
    logFile.open(this->logFileName, ios::out | ios::app);

    if (logFile.fail()) {
        cout << "Error opening file: " << logFileName << "! Exiting..." << endl;
        return FAILURE;
    }

    writeLogRecord("Begin");
    return SUCCESS;
}

int os_logging::Log::close() {
    writeLogRecord("End");
    logFile.close();

    if (logFile.fail()) {
        cout << "Error closing file: " << logFileName << "! Exiting..." << endl;
        return FAILURE;
    }

    return SUCCESS;
}

int os_logging::Log::writeLogRecord(string message) {
    if (message.length() > MAX_LOG_STRING)
    {
        cout << "Error: String longer than MAX_LOG_STRING!" << endl;
        return FAILURE;
    }

    logFile << getTimeStamp() << message << endl;

    if (logFile.fail()) {
        cout << "Error writing to file: " << logFileName << "! Exiting..." << endl;
        return FAILURE;
    }

    return SUCCESS;
};








