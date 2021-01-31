//
// Created by Ethan on 9/16/2019.
//
#include "Helper.h"

using std::string;
using std::cout;
using std::endl;

void Helper::ParseCommandLineArguments(int argc, char **argv) {
    bool castle_file_specified = false;
    bool knight_file_specified = false;
    bool server_name_specified = false;
    bool logger_port_specified = false;

    // We are expecting 2-3 pairs of cli arguments, add one for program name
    if (!(argc == 9)) {
        print_usage();
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i += 2) // We are looking at pairs
    {
        if (string(argv[i]) == "-c") {

            // make sure user inputted a pair
            if (argv[i+1][0] == '-') {
                print_usage();
                exit(EXIT_FAILURE);
            }

            // Copy castle file name
            Castle::setCastle_setup_file_name(string(argv[i+1]));
            castle_file_specified = true;

        } else if (string(argv[i]) == "-k") {

            // make sure user inputted a pair
            if (argv[i+1][0] == '-') {
                print_usage();
                exit(EXIT_FAILURE);
            }

            // Copy knight file name
            Knight::setKnight_setup_file_name(string(argv[i+1]));
            knight_file_specified = true;

        } else if (string(argv[i]) == "-s") {

            // make sure user inputted a pair
            if (argv[i+1][0] == '-') {
                print_usage();
                exit(EXIT_FAILURE);
            }

            if (string(argv[i+1]).length() > 80)
            {
                cout << "Hostname too long!" << endl;
                exit(EXIT_FAILURE);
            }
            // Copy log file name
            LoggerClient::setHostName(string(argv[i+1]));
            server_name_specified = true;

        } else if (string(argv[i]) == "-p") {

            // make sure user inputted a pair
            if (argv[i+1][0] == '-') {
                print_usage();
                exit(EXIT_FAILURE);
            }

            if (string(argv[i+1]).length() > 80)
            {
                cout << "Portnum too long!" << endl;
                exit(EXIT_FAILURE);
            }
            // Copy log file name
            LoggerClient::setPortNum(string(argv[i+1]));
            logger_port_specified = true;
        }
        else {
            print_usage();
            exit(EXIT_FAILURE);
        }
    }
    if (!(castle_file_specified && knight_file_specified && logger_port_specified && server_name_specified)) {
        print_usage();
        exit(EXIT_FAILURE);
    }
}

// Print the usage statement of the program
void Helper::print_usage() {
    cout << "Usage:" << endl;
    cout << "\tHW6.exe -c <castle_file_name> -k <knight_file_name> -s <logserver> -p <logserverport>" << endl;
}

// Signal handler for thread killing
void Helper::ThreadRipper(int signum)
{
    pthread_exit(NULL);
}