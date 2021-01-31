//
// Created by Ethan on 11/30/2019.
//
#include "ThreadManager.h"

ThreadManager* ThreadManager::m_pInstance = nullptr;

ThreadManager* ThreadManager::Instance()
{
    if (!m_pInstance) // If we haven't used ThreadManager yet, create an instance
    {
        m_pInstance = new ThreadManager();
        m_pInstance->initialize();
    }

    return m_pInstance;
}

// This ensures pipes for parent and logger exist, and that pthread_t objects and SafeQueues are ready for castle/knights
void ThreadManager::initialize()
{
    // Parent Init
    parent_pipe = new int[2];
    pipe(parent_pipe);

    // LoggerClient Init
    logger_pipe = new int[2];
    pipe(logger_pipe);

    // Castle needs no Init

    // Knights Init
    knight_attack_threads = new pthread_t [5];
    knight_bookkeeping_threads = new pthread_t [5];
    knight_bookkeeping_message_queues = new SafeQueue<Message> [5];

    // Populate arrays for the knights
    for (int i = 0; i < 5; i++)
    {
        knight_attack_threads[i] = pthread_t();
        knight_bookkeeping_threads[i] = pthread_t();
        knight_bookkeeping_message_queues[i] = SafeQueue<Message>();
    }
}

// Start Thread Management

// Wait for logger thread to die
void ThreadManager::WaitForLoggerThread()
{
    pthread_join(Instance()->logger_thread, NULL);
}

// Wait for castle attacker and bookkeeping threads to die
void ThreadManager::WaitForCastleThreads()
{
    pthread_join(Instance()->castle_attack_thread, NULL);
    pthread_join(Instance()->castle_bookkeeping_thread, NULL);
}

// Wait for all knights' attacker and bookkeeping threads to die
void ThreadManager::WaitForKnightThreads(int knight_count)
{
    for (int i = 0; i < knight_count; i++)
    {
        pthread_join(Instance()->knight_attack_threads[i], NULL);
        pthread_join(Instance()->knight_bookkeeping_threads[i], NULL);
    }
}

pthread_t ThreadManager::getLogger_thread()
{
    return Instance()->logger_thread;
}

pthread_t ThreadManager::getCastle_attack_thread()
{
    return Instance()->castle_attack_thread;
}

pthread_t ThreadManager::getCastle_bookkeeping_thread()
{
    return Instance()->castle_bookkeeping_thread;
}

pthread_t *ThreadManager::getKnight_attack_threads()
{
    return Instance()->knight_attack_threads;
}

pthread_t *ThreadManager::getKnight_bookkeeping_threads()
{
    return Instance()->knight_bookkeeping_threads;
}
// End Thread Management

// Start Parent Pipe Functions
void ThreadManager::WriteParentPipe(int value)
{
    write(Instance()->parent_pipe[1], &value, sizeof(value));
}

int ThreadManager::ReadParentPipe()
{
    int inbuf;
    read(Instance()->parent_pipe[0], &inbuf, sizeof(inbuf));
    return inbuf;
}
// End Parent Pipe Functions

// Start LoggerClient Management
void ThreadManager::WriteLoggerQueue(std::string message)
{
    // Let's prevent buffer overflows by limiting the string size to our max string size minus one (null terminator)
    if (message.length() > 1023)
        return;

    // Lets copy the string passed in to a fixed-size array to be piped
    char* data_array = new char[1024];
    strcpy(data_array, message.c_str());
    write(m_pInstance->logger_pipe[1], data_array, 1024);
}

std::string ThreadManager::ReadLoggerQueue()
{
    char* message = new char[1024];
    read(m_pInstance->logger_pipe[0], message, 1024);
    return message;
}

void ThreadManager::CreateLoggerThread()
{
    pthread_create(&Instance()->logger_thread, NULL, LoggerClient::LoggerProcess, NULL);
}

// Tell the logger thread to close up shop and die off
void ThreadManager::CloseLogger()
{
    WriteLoggerQueue("\a"); // Escape character for LoggerClient
}
// End LoggerClient Management

// Start Castle Message Management
void ThreadManager::WriteCastleQueue(Message message)
{
    Instance()->castle_bookkeeping_message_queue.Enqueue(message);
}

Message ThreadManager::ReadCastleQueue()
{
    return Instance()->castle_bookkeeping_message_queue.Dequeue();
}

void ThreadManager::CreateCastleAttackerThread()
{
    pthread_create(&Instance()->castle_attack_thread, NULL, Castle::CastleAttackerProcess, NULL);
}

void ThreadManager::CreateCastleBookkeepingThread()
{
    pthread_create(&Instance()->castle_bookkeeping_thread, NULL, Castle::CastleBookkeeperProcess, NULL);
}

void ThreadManager::KillCastleAttackerThread()
{
    pthread_kill(Instance()->castle_attack_thread, SIGUSR2);
}

void ThreadManager::KillCastleBookkeepingThread()
{
    pthread_kill(Instance()->castle_bookkeeping_thread, SIGUSR2);
}
// End Castle Message Management

// Start Knight Message Queue Management
void ThreadManager::WriteKnightQueue(int knight_number, Message message)
{
    Instance()->knight_bookkeeping_message_queues[knight_number].Enqueue(message);
}

Message ThreadManager::ReadKnightQueue(int knight_number)
{
    return Instance()->knight_bookkeeping_message_queues[knight_number].Dequeue();
}

void ThreadManager::CreateKnightAttackerThread(int knight_number, void *knight)
{
    pthread_create(&Instance()->knight_attack_threads[knight_number], NULL, Knight::KnightAttackerProcess, knight);
}

void ThreadManager::CreateKnightBookKeeperThread(int knight_number, void *knight)
{
    pthread_create(&Instance()->knight_bookkeeping_threads[knight_number], NULL, Knight::KnightBookkeeperProcess, knight);
}

void ThreadManager::KillKnightAttackerThread(int knight_number)
{
    pthread_kill(Instance()->knight_attack_threads[knight_number], SIGUSR2);
}

void ThreadManager::KillKnightBookkeepingThread(int knight_number)
{
    pthread_kill(Instance()->knight_bookkeeping_threads[knight_number], SIGUSR2);
}
// End Knight Message Queue Management