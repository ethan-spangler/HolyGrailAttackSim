//
// Created by Ethan on 9/16/2019.
//
#include "Helper.h"
#include "PipeManager.h"

using std::string;
using std::cout;
using std::endl;

string Helper::castle_file_name;
string Helper::knight_file_name;
string Helper::log_file_name;

void Helper::parse_cli_arguments(int argc, char **argv) {
    bool castle_file_specified = false; // This is a required argument
    bool knight_file_specified = false; // This is a required argument in HW4

    // We are expecting 1-3 pairs of cli arguments, add one for program name
    if (!(argc == 5 || argc == 7)) {
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
            castle_file_name = string(argv[i+1]);
            castle_file_specified = true;

        } else if (string(argv[i]) == "-k") {

            // make sure user inputted a pair
            if (argv[i+1][0] == '-') {
                print_usage();
                exit(EXIT_FAILURE);
            }

            // Copy knight file name
            knight_file_name = string(argv[i+1]);
            knight_file_specified = true;

        } else if (string(argv[i]) == "-l") {

            // make sure user inputted a pair
            if (argv[i+1][0] == '-') {
                print_usage();
                exit(EXIT_FAILURE);
            }

            // Copy log file name
            log_file_name = string(argv[i+1]);
        }
        else {
            print_usage();
            exit(EXIT_FAILURE);
        }
    }
    if (!castle_file_specified) {
        print_usage();
        exit(EXIT_FAILURE);
    }

    if (!knight_file_specified) {
        print_usage();
        exit(EXIT_FAILURE);
    }
}

void Helper::print_usage() {
    cout << "Usage:" << endl;
    cout << "\tlogging.exe -c <castle_file_name> [-k <knight_file_name>]" << endl;
    cout << "\tlogging.exe -c <castle_file_name> [-k <knight_file_name>] [-l <log_file_name>]" << endl;
}

void Helper::kill_all_in_group(int sig) {
    kill(0, sig); // Running kill with pid of 0 sends to all processes in the same group
}