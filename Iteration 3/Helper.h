//
// Created by Ethan on 9/16/2019.
//

#ifndef LOGGING_HELPER_H
#define LOGGING_HELPER_H
#include <iostream>
#include <signal.h>
#include <unistd.h>

#include "Castle.h"
#include "Knight.h"
#include "LoggerClient.h"

class Helper {
private:
    static void print_usage();

public:
    static void ParseCommandLineArguments(int argc, char **argv);
    static void ThreadRipper(int signum);
};

#endif //LOGGING_HELPER_H
