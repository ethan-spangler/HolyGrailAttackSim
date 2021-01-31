//
// class Log
//
// This class encapsulates the log file functionality
//
// DO NOT MODIFY THIS HEADER IN YOUR PROJECT:
// Grading will be done with this interface
//
// @author Martin L. Barrett
// @author Matthew S. Harrison: harrisonms1@etsu.edu
//

// Multiple-include protection
#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
#include <utility>
#include <iostream>
#include "Helper.h"
#include "PipeManager.h"

using std::string;
using std::cout;
using std::endl;
using std::fstream;
using std::ios;

// Google C++ standard: do not indent namespaces
namespace os_logging {

//
// class Log:
//    Opens a text log file, timestamp at beginning,
//       writes string entries, timestamp at end
//
    class Log {

    private:

        // Private setup for singleton
        Log(){}; // Cannot call constructor
        Log(Log const&){}; // cannot use copy constructor
        Log& operator=(Log const&){}; // cannot use assignment constructor
        static Log* m_pInstance;
        // End private setup for singleton

        // Some constants
        static const int MAX_LOG_STRING = 1024;				// Biggest log string
        static const string DEFAULT_LOG_FILE_NAME;			// Default log name

        // Success and failure of operations
        static const int SUCCESS = 1;
        static const int FAILURE = 0;

        string logFileName;     // Log file name
        fstream logFile;        // Log file variable

        string getTimeStamp(); // Get the timestamp value
    public:
        static Log* Instance(); // Public Instance for singleton

        // Setters
        void setLogfileName(string name);

        // Getters
        string getLogfileName() const;

        // Get the default log file name
        static string getDefaultLogfileName();

        // Log functions
        // Return SUCCESS or FAILURE
        //
        // open the log with timestamp
        void open();

        // close the log with timestamp
        void close();

        // Write a string to the log
        void writeLogRecord(string message);

        static void LoggerProcessor();
    }; // class Log

}  // end namespace os_logging

#endif

