//
// Created by Ethan on 10/17/2019.
//

#include <unistd.h>
#include <cstring>
#include <iostream>
#include "PipeManager.h"
int* PipeManager::parent_pipe = nullptr;
int* PipeManager::logger_pipe = nullptr;
int* PipeManager::castle_attack_pipe = nullptr;
int* PipeManager::castle_bookkeep_pipe = nullptr;
int** PipeManager::knight_attack_pipes = nullptr;
int** PipeManager::knight_bookkeep_pipes = nullptr;

void PipeManager::initialize() {
    parent_pipe = new int[2];
    logger_pipe = new int[2];
    castle_attack_pipe = new int [2];
    castle_bookkeep_pipe = new int [2];
    knight_attack_pipes = new int* [5];
    knight_bookkeep_pipes = new int* [5];

    for (int i = 0; i < 5; i++)
    {
        knight_attack_pipes[i] = new int[2];
        knight_bookkeep_pipes[i] = new int[2];
    }
}

int PipeManager::read_parent() {
    int inbuf;
    read(parent_pipe[0], &inbuf, sizeof(inbuf));
    return inbuf;
}

std::string PipeManager::read_logger() {
    char* message = new char[1024];
    read(logger_pipe[0], message, 1024);
    return message;
}

int PipeManager::read_castle_attack() {
    int inbuf;
    read(castle_attack_pipe[0], &inbuf, sizeof(inbuf));
    return inbuf;
}

Message PipeManager::read_castle_bookkeep() {
    struct Message inbuf;
    read(castle_bookkeep_pipe[0], &inbuf, sizeof(Message));
    return inbuf;
}

int PipeManager::read_knight_attack(int knight) {
    int inbuf;
    read(knight_attack_pipes[knight][0], &inbuf, sizeof(inbuf));
    return inbuf;
}

Message PipeManager::read_knight_bookkeep(int knight) {
    struct Message inbuf;
    read(knight_bookkeep_pipes[knight][0], &inbuf, sizeof(Message));
    return inbuf;
}

void PipeManager::write_parent(int data) {
    write(parent_pipe[1], &data, sizeof(data));
}

void PipeManager::write_logger(std::string data) {
    char* data_array = new char[1024];
    strcpy(data_array, data.c_str());
    write(logger_pipe[1], data_array, 1024);
}

void PipeManager::write_castle_attack(int data) {
    write(castle_attack_pipe[1], &data, sizeof(data));
}

void PipeManager::write_castle_bookkeep(Message data) {
    write(castle_bookkeep_pipe[1], &data, sizeof(Message));
}

void PipeManager::write_knight_attack(int knight, int data) {
    write(knight_attack_pipes[knight][1], &data, sizeof(data));
}

void PipeManager::write_knight_bookkeep(int knight, Message data) {
    write(knight_bookkeep_pipes[knight][1], &data, sizeof(Message));
}












