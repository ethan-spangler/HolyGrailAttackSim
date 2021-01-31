//
// Created by Ethan on 9/16/2019.
//

#include <iostream>
#include "Helper.h"

using std::string;
using std::cout;
using std::endl;

string Helper::castle_file_name;
string Helper::knight_file_name;
string Helper::log_file_name;

bool Helper::parse_cli_arguments(int argc, char **argv) {
    bool castle_file_specified = false; // This is a required argument

    // We are expecting 1-3 pairs of cli arguments, add one for program name
    if (!(argc == 3 || argc == 5 || argc == 7)) {
        print_usage();
        return false;
    }

    for (int i = 1; i < argc; i += 2) // We are looking at pairs
    {
        if (string(argv[i]) == "-c") {

            // make sure user inputted a pair
            if (string(argv[i+1]).length() == 2 && argv[i+1][0] == '-') {
                print_usage();
                return false;
            }

            // Copy castle file name
            castle_file_name = string(argv[i+1]);
            castle_file_specified = true;

        } else if (string(argv[i]) == "-k") {

            // make sure user inputted a pair
            if (string(argv[i+1]).length() == 2 && argv[i+1][0] == '-') {
                print_usage();
                return false;
            }

            // Copy knight file name
            knight_file_name = string(argv[i+1]);

        } else if (string(argv[i]) == "-l") {

            // make sure user inputted a pair
            if (string(argv[i+1]).length() == 2 && argv[i+1][0] == '-') {
                print_usage();
                return false;
            }

            // Copy log file name
            log_file_name = string(argv[i+1]);
        }
        else {
            print_usage();
            return false;
        }
    }
    if (!castle_file_specified) {
        print_usage();
        return false;
    }

    return true;
}

void Helper::print_usage() {
    cout << "Usage:" << endl;
    cout << "\tlogging.exe -c <castle_file_name>" << endl;
    cout << "\tlogging.exe -c <castle_file_name> [-k <knight_file_name>]" << endl;
    cout << "\tlogging.exe -c <castle_file_name> [-l <log_file_name>]" << endl;
    cout << "\tlogging.exe -c <castle_file_name> [-k <knight_file_name>] [-l <log_file_name>]" << endl;
}
