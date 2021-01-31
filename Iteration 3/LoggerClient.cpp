//
// Created by Ethan on 9/14/2019.
//

#include "LoggerClient.h"

LoggerClient* LoggerClient::instance = nullptr;

// Start Constructors
LoggerClient* LoggerClient::Instance() {
    if (!instance) // Allow one instance of the log
    {
        instance = new LoggerClient;
        instance->hostname = new char[81];
        instance->portnum = new char[81];
    }

    return instance;
}
// End Constructors

// Setters for hostname/portnum
void LoggerClient::setHostName(string hostname)
{
     strcpy(instance->hostname, hostname.c_str());
}

void LoggerClient::setPortNum(string portnum)
{
    strcpy(instance->portnum, portnum.c_str());
}

// Function to be run on a thread for the logger
void* LoggerClient::LoggerProcess(void *args)
{
    struct addrinfo *myinfo;
    LogMessage logmessage;

    int sockdesc = socket(AF_INET, SOCK_STREAM, 0);
    if (sockdesc < 0)
    {
        cout << "Error creating LoggerClient Socket" << endl;
        exit(0);
    }

    if (getaddrinfo(Instance()->hostname, Instance()->portnum, NULL, &myinfo))
    {
        cout << "Error getting LoggerClient address" << endl;
        exit(0);
    }

    int connection = connect(sockdesc, myinfo->ai_addr, myinfo->ai_addrlen);
    if ( connection < 0 )
    {
        cout << "Error in connect" << endl;
        exit(0);
    }

    logmessage.command = 0; // Just write messages, no need for commands yet
    strcpy(logmessage.data, "Begin");
    write(sockdesc, (char*) &logmessage, sizeof(logmessage));

    // Grab a message from logger queue and write it to the log socket, until receiving alert to die
    while (true)
    {
        string message = ThreadManager::ReadLoggerQueue();

        if (message[0] == '\a') // LoggerClient Exit code
            break;

        if (message.length() > 1024)
        {
            cout << "Error: Log String longer than MAX_LOG_STRING!" << endl;
            exit(1);
        }

        strcpy(logmessage.data, message.c_str());
        write(sockdesc, (char*) &logmessage, sizeof(logmessage));
    }

    strcpy(logmessage.data, "End");
    write(sockdesc, (char*) &logmessage, sizeof(logmessage));


    close(sockdesc);
    pthread_exit(0);
}