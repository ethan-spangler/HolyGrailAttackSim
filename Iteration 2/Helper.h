//
// Created by Ethan on 9/16/2019.
//

#ifndef LOGGING_HELPER_H
#define LOGGING_HELPER_H
#include <iostream>
#include <signal.h>
#include <unistd.h>

class Helper {
public:
    static std::string castle_file_name;
    static std::string knight_file_name;
    static std::string log_file_name;

    static void parse_cli_arguments(int argc, char **argv);
    static void print_usage();

    static void kill_all_in_group(int sig);
};

#endif //LOGGING_HELPER_H
