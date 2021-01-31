#include <iostream>
#include <signal.h>
#include <pthread.h>

#include "ThreadManager.h"
#include "Helper.h"

// Initializes the thread manager, setting up shared memory objects
ThreadManager* thread_manager = ThreadManager::Instance();
Knight* knights = new Knight[5];
Castle* castle = Castle::Instance();
LoggerClient* logger = LoggerClient::Instance();

int main(int argc, char **argv) {

    // Setup signal with handler for thread killing
    signal(SIGUSR2, Helper::ThreadRipper);

    // Parse all the command line arguments, exiting if there are issues
    Helper::ParseCommandLineArguments(argc, argv);

    // Create knights and castle from setup files
    knights = Knight::CreateKnightsFromFile();
    Castle::CreateCastleFromFile();

    // Create and start a thread for the logger process
    ThreadManager::CreateLoggerThread();

    // Create and start threads for the knight processes
    for (int i = 0; i < Knight::getKnight_count(); i++)
    {
        Knight* current = &knights[i];

        ThreadManager::CreateKnightAttackerThread(i, current);
        ThreadManager::CreateKnightBookKeeperThread(i, current);
    }

    // Create and start threads for the castle processes
    ThreadManager::CreateCastleAttackerThread();
    ThreadManager::CreateCastleBookkeepingThread();

    // Parent Logic
    while (true)
    {
        // Read an integer from the parent pipe
        int pipe_message = ThreadManager::ReadParentPipe();

        // If the castle is dead
        if (pipe_message == 0)
        {
            struct Message message;
            message.from = 0;
            message.type = 0;
            message.damage = -1;

            // Signal the castle death to all knight bookkeeping processes
            for (int i = 0; i < Knight::getKnight_count(); i++)
                ThreadManager::WriteKnightQueue(i, message);

            break; // Exit infinite loop with parent logic
        }

        // If all knights are dead
        if (pipe_message == -1)
            break; // Exit infinite loop with parent logic

        // If a knight died
        if (pipe_message > 0 && pipe_message < 6)
        {
            // Signal castle attacker that knight is dead
            sigval value;
            value.sival_int = pipe_message - 1;
            pthread_sigqueue(ThreadManager::getCastle_attack_thread(), SIGUSR1, value);
        }
    }

    // Wait for child threads to die off
    ThreadManager::WaitForKnightThreads(Knight::getKnight_count());
    ThreadManager::WaitForCastleThreads();
    ThreadManager::CloseLogger();
    ThreadManager::WaitForLoggerThread();

    return 0;
}