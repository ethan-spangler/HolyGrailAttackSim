//
// Created by Ethan on 10/17/2019.
//

#ifndef LOGGING_PIPEMANAGER_H
#define LOGGING_PIPEMANAGER_H

#include <string>
#include "AttackMessage.h"

class PipeManager {
public:
    static void initialize();

    static int* parent_pipe;
    static int* logger_pipe;
    static int* castle_attack_pipe;
    static int* castle_bookkeep_pipe;
    static int** knight_attack_pipes;
    static int** knight_bookkeep_pipes;

    static int read_parent();
    static std::string read_logger();
    static int read_castle_attack();
    static Message read_castle_bookkeep();
    static int read_knight_attack(int knight);
    static Message read_knight_bookkeep(int knight);

    static void write_parent(int data);
    static void write_logger(std::string data);
    static void write_castle_attack(int data);
    static void write_castle_bookkeep(Message data);
    static void write_knight_attack(int knight, int data);
    static void write_knight_bookkeep(int knight, Message data);
};


#endif //LOGGING_PIPEMANAGER_H
