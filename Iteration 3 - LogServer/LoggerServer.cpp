//
// Created by Ethan on 12/4/2019.
//

#include "LoggerServer.h"

LoggerServer* LoggerServer::instance = nullptr;
string LoggerServer::log_file_name = "";



LoggerServer* LoggerServer::Instance()
{
    if (!instance)
    {
        instance = new LoggerServer;
        instance->initialize();
    }

    return instance;
}

void LoggerServer::initialize()
{
    if (log_file_name.empty())
        SetLogFileName("log");

    instance->logger_pipe = new int[2];
    pipe(instance->logger_pipe);
}

// Start Getters/Setters
void LoggerServer::SetLogFileName(string name)
{
    log_file_name = std::move(name);
}

string LoggerServer::GetLogFileName()
{
    return log_file_name;
}

// Open or Close logger
void LoggerServer::open()
{
    // Open logfile to append to current file if it exists
    logfile.open(log_file_name, ios::out | ios::app);

    if (logfile.fail()) {
        cout << "Error opening file: " << log_file_name << "! Exiting..." << endl;
        exit(1);
    }
}

void LoggerServer::close()
{
    // Close logfile stream
    logfile.close();

    if (logfile.fail()) {
        cout << "Error closing file: " << log_file_name << "! Exiting..." << endl;
        exit(1);
    }
}

string LoggerServer::getTimeStamp()
{
    // Setup for ctime()

    time_t raw_time;
    time(&raw_time);

    return string(ctime(&raw_time));
}

// Writes a message to the log file
void LoggerServer::writeToLogFile(string message)
{
    logfile << getTimeStamp() << message << endl;

    if (logfile.fail()) {
        cout << "Error writing to file: " << log_file_name << "! Exiting..." << endl;
        exit(1);
    }
}

// Pthread Method - Runs in the background to handle the logger functionality
void* LoggerServer::LoggerProcess(void *args)
{
    char *input = new char[1024];

    // Ensure instance has been created, and the file stream is opened
    Instance();
    Instance()->open();

    for(;;)
    {
        // Read string from the logger pipe
        read(Instance()->logger_pipe[0], input, 1024);

        // Check if exit alert message was received
        if (input[0] == '\a')
        {
            Instance()->close();
            break; // Exit the program
        }

        Instance()->writeToLogFile(input);
    }

    pthread_exit(0);
}

// Pthread Method - Runs for each connection
void* LoggerServer::ConnectionProcessor(void *args)
{
    LogMessage message;
    int value;
    char *buf = new char[1024];

    for(;;)
    {
        value = read((long) args, (char*)&message, sizeof(LogMessage));

        // If value == 0, client closed the socket connection
        if (value<1)
            break;

        // Exit command
        if (message.command == -1)
        {
            strcpy(buf, "\a"); // Tell logger thread to die
            write(Instance()->logger_pipe[1], buf, 1024);
            break;
        }

        // Check message length
        if (string(message.data).length() > 1024)
        {
            cout << "Error: String longer than MAX_LOG_STRING!" << endl;
            Instance()->close();
            exit(1);
        }

        strcpy(buf, message.data);
        write(Instance()->logger_pipe[1], buf, 1024);
    }

    pthread_exit(0);
}
