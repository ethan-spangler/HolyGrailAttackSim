//
// Created by Ethan on 12/4/2019.
//

#ifndef LOGSERVER_LOGGER_H
#define LOGSERVER_LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <cstring>

#include "LogMessage.h"

using std::string;
using std::cout;
using std::endl;
using std::fstream;
using std::ios;

class LoggerServer
{
private:

    // Singleton Setup
    LoggerServer(){};
    LoggerServer(LoggerServer const&){};
    LoggerServer& operator=(LoggerServer const&){};
    static LoggerServer* instance;

    static string log_file_name;

    fstream logfile;
    int* logger_pipe;

    string getTimeStamp();
    void writeToLogFile(string message);
    void initialize();
public:
    static LoggerServer* Instance(); // Public instance for singleton

    static void SetLogFileName(string name);
    static string GetLogFileName();

    // Open/Close logger
    void open();
    void close();

    static void* LoggerProcess(void* args);
    static void* ConnectionProcessor(void* args);
};


#endif //LOGSERVER_LOGGER_H
