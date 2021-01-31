//
// Created by Ethan on 11/30/2019.
//

#ifndef HW6_LOGGER_H
#define HW6_LOGGER_H

#include <string>
#include <fstream>
#include <utility>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "ThreadManager.h"
#include "Helper.h"
#include "LogMessage.h"

using std::string;
using std::cout;
using std::endl;
using std::fstream;
using std::ios;

//
// class LoggerClient:
//    Opens a text log file, timestamp at beginning,
//       writes string entries, timestamp at end
//
    class LoggerClient {

    private:

        // Private setup for singleton
        LoggerClient(){}; // Cannot call constructor
        LoggerClient(LoggerClient const&){}; // cannot use copy constructor
        LoggerClient& operator=(LoggerClient const&){}; // cannot use assignment constructor
        static LoggerClient* instance;
        // End private setup for singleton

        char *portnum;
        char *hostname;

        // Some constants
        static const int MAX_LOG_STRING = 1024;				// Biggest log string

    public:
        static LoggerClient* Instance(); // Public Instance for singleton

        static void setPortNum(string portnum);
        static void setHostName(string hostname);

        static void* LoggerProcess(void *args);
    }; // class Log

#endif //HW6_LOGGER_H
