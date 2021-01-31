//
// Created by Ethan on 9/14/2019.
//

#include "Log.h"

using namespace os_logging;

Log* Log::m_pInstance = nullptr;
const string Log::DEFAULT_LOG_FILE_NAME = "log";

string Log::getTimeStamp() {
    // Setup for ctime()
    time_t raw_time;
    time(&raw_time);

    return string(ctime(&raw_time));
}

// Start Constructors
Log* Log::Instance() {
    if (!m_pInstance) { // Allow one instance of the log
        m_pInstance = new Log;

        m_pInstance->setLogfileName(Helper::log_file_name.empty() ? getDefaultLogfileName() : Helper::log_file_name);
    }

    return m_pInstance;
}
// End Constructors

// Start Getters/Setters
void Log::setLogfileName(string name) {
    logFileName = std::move(name);
}

string Log::getLogfileName() const {
    return logFileName;
}

string Log::getDefaultLogfileName() {
    return DEFAULT_LOG_FILE_NAME;
}
// End Getters/Setters

void Log::open() {
    // Open logfile with to append to current file if it exists
    logFile.open(this->logFileName, ios::out | ios::app);

    if (logFile.fail()) {
        cout << "Error opening file: " << logFileName << "! Exiting..." << endl;
        Helper::kill_all_in_group(15); // SIGTERM all in group
    }

    writeLogRecord("Begin");
}

void Log::close() {
    writeLogRecord("End");
    logFile.close();

    if (logFile.fail()) {
        cout << "Error closing file: " << logFileName << "! Exiting..." << endl;
        Helper::kill_all_in_group(15); // SIGTERM all in group
    }
}

void Log::writeLogRecord(string message) {
    if (message.length() > MAX_LOG_STRING)
    {
        cout << "Error: String longer than MAX_LOG_STRING!" << endl;
        Helper::kill_all_in_group(15); // SIGTERM all in group
    }

    // Special character to tell the logger to exit
    if (message[0] == '\a')
    {
        Instance()->close();
        exit(1);
    }

    logFile << getTimeStamp() << message << endl;

    if (logFile.fail()) {
        cout << "Error writing to file: " << logFileName << "! Exiting..." << endl;
        Helper::kill_all_in_group(15); // SIGTERM all in group
    }
}

void Log::LoggerProcessor() {
    // Instantiate Logger
    Log::Instance();
    Log::Instance()->open();
    while (true)
    {
        Log::Instance()->writeLogRecord(PipeManager::read_logger());
    }

    exit(1); // If by some amazing feat our program ends up outside the loop, exit
};








