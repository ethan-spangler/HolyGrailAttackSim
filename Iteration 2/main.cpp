#include <iostream>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include "PipeManager.h"
#include "Log.h"
#include "Helper.h"
#include "Castle.h"
#include "Knight.h"

using os_logging::Log;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
    PipeManager::initialize(); // Generate Pipemanager
    int pid_logger, pid_castle_attacker, pid_castle_bookkeeper, pid_knight_attacker, pid_knight_bookkeeper;

    //Set up parent pipe
    int success = pipe(PipeManager::parent_pipe);

    // Validate and parse command line arguments
    Helper::parse_cli_arguments(argc, argv);

    // Set up Logger pipe
    pipe(PipeManager::logger_pipe);

    // Fork for Logger process
    pid_logger = fork();
    if (pid_logger == 0)
        Log::LoggerProcessor();

    srand (time(NULL));
    // Setup Castle and Knights
    Castle castle = Castle::CreateCastleFromFile();
    Knight* knights = Knight::CreateKnightsFromFile();

    // If we got this far, everything should have worked so far
    // Lets set up all our other important pipes
    pipe(PipeManager::castle_attack_pipe);
    pipe(PipeManager::castle_bookkeep_pipe);
    for (int i = 0; i < Knight::GetKnightCount(); i++)
    {
        pipe(PipeManager::knight_attack_pipes[i]);
        pipe(PipeManager::knight_bookkeep_pipes[i]);
    }


    srand (time(NULL)); // Rand used in castle attacker
    // Fork for Castle Attacker
    pid_castle_attacker = fork();
    if (pid_castle_attacker == 0)
        Castle::CastleAttackerProcessor(castle);

    // Fork for Castle Bookkeeper
    pid_castle_bookkeeper = fork();
    if (pid_castle_bookkeeper == 0)
        Castle::CastleBookkeeperProcessor(castle, pid_castle_attacker);

    // Fork for Knight Attackers and Bookkeepers
    for (int i = 1; i <= Knight::GetKnightCount(); i++)
    {
        pid_knight_attacker = fork();
        if (pid_knight_attacker == 0)
            Knight::KnightAttackerProcessor(knights[i-1], i);

        pid_knight_bookkeeper = fork();
        if (pid_knight_bookkeeper == 0)
            Knight::KnightBookkeeperProcessor(knights[i-1], i, pid_knight_attacker);
    }

    // Parent Logic
    while (true)
    {
        int pipe_message = PipeManager::read_parent();

        // If castle is dead
        if (pipe_message == 0)
        {
            struct Message message;
            message.from = 0;
            message.type = 0;
            message.damage = -1;

            // Signal the castle death to all knight bookkeeping processes
            for (int i = 0; i < Knight::GetKnightCount(); i++)
                PipeManager::write_knight_bookkeep(i, message);

            break;
        }

        // If all knights are dead
        if (pipe_message == -1)
        {
            break;
        }

        // Knight Died
        if (pipe_message > 0 && pipe_message < 6)
        {
            // Signal castle attacker that knight is dead
            sigval value;
            value.sival_int = pipe_message - 1;
            sigqueue(pid_castle_attacker, SIGUSR1, value);
        }
    }
    // End Parent Logic

    // Wait for all knight/castle processes to end
    for (int i = 0; i <= Knight::GetKnightCount(); i++)
    {
        wait(NULL);
        wait(NULL);
    }

    // Tell logger to exit gracefully
    PipeManager::write_logger("\a");

    // Wait for logger process to exit
    wait(NULL);

    // We outta here
    return 1;
}