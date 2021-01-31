
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

#include "LoggerServer.h"
#include "LogMessage.h"

using std::cout;
using std::endl;
using std::string;

static char* log_file_name = nullptr;
static char* portnum = new char[81];

void PrintUsage();
void ParseCommandLineArguments(int argc, char** argv);



int main(int argc, char** argv)
{
    int sockdesc;
    struct addrinfo *myinfo;
    int connection;
    int value;

    ParseCommandLineArguments(argc, argv);
    LoggerServer::Instance();

    // Create thread for logger process. We only have a single thread
    // handling the actual filestream for the logger. It has a pipe
    // so that other threads can queue up log messages.
    pthread_t logger_thread;
    pthread_create(&logger_thread, NULL, LoggerServer::LoggerProcess, NULL);

    // Set up socket to TCP/IP stream
    sockdesc = socket(AF_INET, SOCK_STREAM, 0);
    if (sockdesc < 0)
    {
        cout << "Error creating socket" << endl;
        exit(0);
    }

    // Set up the address record
    if (getaddrinfo("127.0.0.1", portnum, NULL, &myinfo) != 0)
    {
        cout << "Error getting address" << endl;
        exit(0);
    }

    // Bind the socket to an address
    if (bind(sockdesc, myinfo->ai_addr, myinfo->ai_addrlen) < 0)
    {
        cout << "Error binding to socket" << endl;
        exit(0);
    }

    // Now listen to the socket
    if (listen(sockdesc, 1) < 0)
    {
        cout << "Error in listen" << endl;
        exit(0);
    }

    // Loop for listening to connections
    for (;;)
    {
        cout << "Waiting for Connection..." << endl;

        // Accept a connect, check the returned descriptor
        connection = accept(sockdesc, NULL, NULL);
        if (connection < 0)
        {
            cout << "Error in accept" << endl;
            exit(0);
        } else
        {
            // Create a thread for each connection
            pthread_create(new pthread_t, NULL, LoggerServer::ConnectionProcessor, (void *) connection);
        }
    }
}

void ParseCommandLineArguments(int argc, char** argv)
{
    bool logfile_given = false;
    bool portnum_given = false;

    if (argc != 5)
    {
        PrintUsage();
        exit(EXIT_FAILURE);
    }

    // Loop through the arguments to find the port and hostname
    for (int i = 1; i < 5; i += 2)
    {
        if (string(argv[i]) == "-l")
        {
            // Ensure logfile not provided twice and that it is a pair
            if (logfile_given || argv[i+1][0] == '-') {
                PrintUsage();
                exit(EXIT_FAILURE);
            }

            LoggerServer::SetLogFileName(argv[i+1]);
            logfile_given = true;
        }
        else if (string(argv[i]) == "-p")
        {
            // Ensure portnum not provided twice and that it is a pair
            if (portnum_given || argv[i+1][0] == '-') {
                PrintUsage();
                exit(EXIT_FAILURE);
            }

            if (string(argv[i+1]).length() > 80)
            {
                cout << "Port Number too long" << endl;
                exit(EXIT_FAILURE);
            }

            strcpy(portnum, argv[i+1]);
            portnum_given = true;
        }
        else
        {
            PrintUsage();
            exit(EXIT_FAILURE);
        }
    }

    if (!(logfile_given && portnum_given))
    {
        PrintUsage();
        exit(EXIT_FAILURE);
    }
}

void PrintUsage()
{
    cout << "Usage: logServer -l <logfilename> -p <portnumber>" << endl;
}