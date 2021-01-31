//
// Created by Ethan on 11/30/2019.
//

#ifndef HW6_THREADMANAGER_H
#define HW6_THREADMANAGER_H

#include <pthread.h>
#include <string>
#include <unistd.h>
#include <cstring>
#include <iostream>

#include "SafeQueue.h"
#include "AttackMessage.h"
#include "Castle.h"
#include "LoggerClient.h"

class ThreadManager {
private:
    // Setup for Singleton
    ThreadManager(){};
    ThreadManager(ThreadManager const&){};
    ThreadManager& operator=(ThreadManager const&){};
    static ThreadManager* m_pInstance;

    void initialize();
    // End Setup for Singleton

    // Parent Stuff
    int* parent_pipe;
    
    // LoggerClient Stuff
    pthread_t logger_thread;
    int* logger_pipe;

    // Castle Stuff
    pthread_t castle_attack_thread;
    pthread_t castle_bookkeeping_thread;
    SafeQueue<Message> castle_bookkeeping_message_queue;

    // Knight Stuff
    pthread_t *knight_attack_threads;
    pthread_t *knight_bookkeeping_threads;
    SafeQueue<Message> *knight_bookkeeping_message_queues;

public:
    static ThreadManager* Instance(); // Instance for Singleton

    // Thread Management
    static void WaitForLoggerThread();
    static void WaitForCastleThreads();
    static void WaitForKnightThreads(int knight_count);
    static pthread_t getLogger_thread();
    static pthread_t getCastle_attack_thread();
    static pthread_t getCastle_bookkeeping_thread();
    static pthread_t *getKnight_attack_threads();
    static pthread_t *getKnight_bookkeeping_threads();

    // Parent Management
    static void WriteParentPipe(int value);
    static int ReadParentPipe();

    // LoggerClient Management
    static void WriteLoggerQueue(std::string message);
    static std::string ReadLoggerQueue();
    static void CreateLoggerThread();
    static void CloseLogger();

    // Castle Management
    static void WriteCastleQueue(Message message);
    static Message ReadCastleQueue();
    static void CreateCastleAttackerThread();
    static void CreateCastleBookkeepingThread();
    static void KillCastleAttackerThread();
    static void KillCastleBookkeepingThread();

    // Knight Management
    static void WriteKnightQueue(int knight_number, Message message);
    static Message ReadKnightQueue(int knight_number);
    static void CreateKnightAttackerThread(int knight_number, void* knight);
    static void CreateKnightBookKeeperThread(int knight_number, void* knight);
    static void KillKnightAttackerThread(int knight_number);
    static void KillKnightBookkeepingThread(int knight_number);


};
#endif //HW6_THREADMANAGER_H
