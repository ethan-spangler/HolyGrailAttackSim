//
// Created by Ethan on 12/1/2019.
//

#include "Castle.h"

// Init static variables
Castle* Castle::instance = nullptr;
string Castle::castle_setup_file_name;

// Singleton Instance Setup
Castle* Castle::Instance()
{
    if (!instance)
    {
        instance = new Castle();
        instance->valid_target_count = 0;
        instance->valid_targets = new bool[5];
        for (int i = 0; i < 5; i++)
            instance->valid_targets[i] = false;
    }

    return instance;
}

// Start Getters/Setters
int Castle::getHit_points() const
{
    return hit_points;
}

void Castle::setHit_points(int hit_points)
{
    Castle::hit_points = hit_points;
}

int Castle::getAttack_rate() const
{
    return attack_rate;
}

void Castle::setAttack_rate(int attack_rate)
{
    Castle::attack_rate = attack_rate;
}

int Castle::getAttack_chance_taunt() const
{
    return attack_chance_taunt;
}

void Castle::setAttack_chance_taunt(int attack_chance_taunt)
{
    Castle::attack_chance_taunt = attack_chance_taunt;
}

int Castle::getAttack_chance_cow() const
{
    return attack_chance_cow;
}

void Castle::setAttack_chance_cow(int attack_chance_cow)
{
    Castle::attack_chance_cow = attack_chance_cow;
}

int Castle::getAttack_chance_rabbit() const
{
    return attack_chance_rabbit;
}

void Castle::setAttack_chance_rabbit(int attack_chance_rabbit)
{
    Castle::attack_chance_rabbit = attack_chance_rabbit;
}

int Castle::getDamage_weak() const
{
    return damage_weak;
}

void Castle::setDamage_weak(int damage_weak)
{
    Castle::damage_weak = damage_weak;
}

int Castle::getDamage_strong() const
{
    return damage_strong;
}

void Castle::setDamage_strong(int damage_strong)
{
    Castle::damage_strong = damage_strong;
}

bool *Castle::getValid_targets() const
{
    return valid_targets;
}

void Castle::setValid_targets(bool *valid_targets)
{
    Castle::valid_targets = valid_targets;
}

int Castle::getValid_target_count() const
{
    return valid_target_count;
}

void Castle::setValid_target_count(int valid_target_count)
{
    Castle::valid_target_count = valid_target_count;
}

const string &Castle::getCastle_setup_file_name()
{
    return castle_setup_file_name;
}

void Castle::setCastle_setup_file_name(const string &castle_setup_file_name)
{
    Castle::castle_setup_file_name = castle_setup_file_name;
}
// End Getters/Setters

// Start Castle Creation
Castle* Castle::CreateCastleFromFile() {
    int j = 1;
    int castle_hp;
    int castle_rate;
    int castle_taunt;
    int castle_cow;
    int castle_rabbit;
    int castle_weak;
    int castle_strong;

    string line;
    ifstream castle_file(castle_setup_file_name);
    if (castle_file.is_open())
    {
        ThreadManager::WriteLoggerQueue("Castle setup file opened successfully");

        castle_hp = GetFileIntegerInputInRange(castle_file, "Hitpoints", "hp:", 100, 300);
        castle_rate = GetFileIntegerInputInRange(castle_file, "Attack Rate", "rate:", 1, 100);
        castle_taunt = GetFileIntegerInputInRange(castle_file, "Taunt Attack Chance", "taunt:", 75, 89);
        castle_cow = GetFileIntegerInputInRange(castle_file, "Cow Attack Chance", "cow:", 10, 20);
        castle_rabbit = GetFileIntegerInputInRange(castle_file, "Rabbit Attack Chance", "rabbit:", 1, 5);
        castle_weak = GetFileIntegerInputInRange(castle_file, "Weak Attack Damage", "weak:", 1, 9);
        castle_strong = GetFileIntegerInputInRange(castle_file, "Strong Attack Damage", "strong:", 25, 50);

        if ((castle_cow + castle_taunt + castle_rabbit) != 100) {
            ThreadManager::WriteLoggerQueue("Castle attack chances do not add up to 100%");
            ThreadManager::WriteLoggerQueue("\a");;
            cout << "Castle attack chances do not add up to 100%. Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }
        instance->setHit_points(castle_hp);
        instance->setAttack_rate(castle_rate);
        instance->setAttack_chance_taunt(castle_taunt);
        instance->setAttack_chance_cow(castle_cow);
        instance->setAttack_chance_rabbit(castle_rabbit);
        instance->setDamage_weak(castle_weak);
        instance->setDamage_strong(castle_strong);
        instance->setValid_target_count(Knight::getKnight_count());

        for (int i = 0; i < instance->getValid_target_count(); i++)
        {
            instance->validateTarget(i);
        }

        ThreadManager::WriteLoggerQueue("Castle successfully initialized");
        return instance;
    }
    else {
        ThreadManager::WriteLoggerQueue("Unable to open Castle Setup File");
        ThreadManager::WriteLoggerQueue("\a");
        cout << "Unable to open Castle Setup File. Program Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

// From the input stream (castle file), get a line, validate the limits, and return the value
int Castle::GetFileIntegerInputInRange(std::ifstream& castleName, string fieldName, string logName, int lowerLimit, int upperLimit) {
    int logNameLength = logName.length();
    string line;
    int intConvertedFromLine = 0;

    // Get a line from the castle setup file
    if (getline(castleName, line) && line.compare(0, logNameLength, logName) == 0){
        try {
            // Pull the integer value from that line
            intConvertedFromLine = std::stoi(line.substr(logNameLength, line.length() - logNameLength), nullptr);
        } catch (...) {
            ThreadManager::WriteLoggerQueue("Exception occurred parsing castle " + fieldName);
            ThreadManager::WriteLoggerQueue("\a");;
            cout << "Exception occurred parsing castle " << fieldName << ". Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        // Make sure the value is in legal bounds
        if (intConvertedFromLine < lowerLimit || intConvertedFromLine > upperLimit) {
            ThreadManager::WriteLoggerQueue("Castle " + fieldName + " out of bounds");
            ThreadManager::WriteLoggerQueue("\a");;
            cout << "Knight " << fieldName << " out of bounds. Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }
    } else {
        ThreadManager::WriteLoggerQueue("Castle " + fieldName + " line not found or out of order");
        ThreadManager::WriteLoggerQueue("\a");;
        cout << "Castle " << fieldName << " line not found or out of order. Program Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    // Write the line to the log
    ThreadManager::WriteLoggerQueue(logName + std::to_string(intConvertedFromLine));

    return intConvertedFromLine;
}
// End Castle Setup

// Start Knight Target Functions

// Mark a certain knight to be attackable
void Castle::validateTarget(int knight) {
    if (knight >= 0 && knight < 5)
        valid_targets[knight] = true;
}

// Mark a certain knight to not be attacked
void Castle::invalidateTarget(int knight) {
    if (knight >= 0 && knight < 5)
        valid_targets[knight] = false;
}

// Is this target valid?
bool Castle::isTargetValid(int target) {
    if (target >= 0 && target < 5)
        return valid_targets[target];

    return false;
}

// Select a knight randomly from the valid ones
int Castle::selectRandomValidKnight() {
    int r = rand() % getValid_target_count() + 1;
    int t = 0;

    // This code makes our selection ignore knights that are not valid targets
    for (int i = 0; i < 5; i++)
    {
        if (isTargetValid(i))
            t++;

        if (t == r)
            return i;
    }
}
// End Castle Helpers

// Start Castle functions for threaded process
void *Castle::CastleAttackerProcess(void *args)
{
    // Set up our signal action to point sigusr1 signals to our handler
    struct sigaction action;
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = CastleSigHandler;
    sigaction(SIGUSR1, &action, NULL);

    // Seed our random number generator
    srand(time(NULL));

    // First set up the valid targets array to number of knights
    Instance()->setValid_target_count(Knight::getKnight_count());
    for (int i = 0; i < Instance()->getValid_target_count(); i++)
        Instance()->validateTarget(i);

    struct timespec ts = {0, Instance()->getAttack_rate() * 1000L}; // nanoseconds -> microseconds

    struct Message message; // Lets go ahead and create a message so it doesnt need to be created every loop
    message.from = 0; // From Castle

    while (true)
    {
        nanosleep(&ts, NULL);

        if (Instance()->getValid_target_count() == 0)
            break;

        int roll = rand() % 100 + 1; // 1 - 100

        if (roll <= Instance()->getAttack_chance_taunt())
        {
            message.type = 0; // TAUNT
            message.damage = Instance()->getDamage_weak();

            int target = Instance()->selectRandomValidKnight();
            if (target == -1) // If no valid knights
                break;

            ThreadManager::WriteKnightQueue(target, message);
        }
        else if (roll <= Instance()->getAttack_chance_taunt() + Instance()->getAttack_chance_cow())
        {
            message.type = 1; // COW
            message.damage = Instance()->getDamage_weak();

            for (int i = 0; i < 5; i++)
            {
                if (Instance()->isTargetValid(i))
                {
                    ThreadManager::WriteKnightQueue(i, message);
                }
            }
        }
        else
        {
            message.type = 2; // RABBIT
            message.damage = Instance()->getDamage_strong();

            int target = Instance()->selectRandomValidKnight();
            if (target == -1) // If no valid knights
                break;

            ThreadManager::WriteKnightQueue(target, message);
        }
    }

    // All knights ded
    ThreadManager::WriteParentPipe(-1);

    // Message to inform bookkeeper of the victory
    message.from = 0;
    message.type = -1;
    message.damage = 0;
    ThreadManager::WriteCastleQueue(message);
}

void *Castle::CastleBookkeeperProcess(void *args)
{
    string exitmessage;

    while (true)
    {
        struct Message message = ThreadManager::ReadCastleQueue();

        // Check for message from castle_attacker saying that all knights are dead
        if (message.type == -1)
        {
            exitmessage = "Castle: \"La victoire est à nous!\"";
            std::cout << exitmessage << endl;
            ThreadManager::WriteLoggerQueue(exitmessage);
            break;
        }

        // Log message that comes in
        ThreadManager::WriteLoggerQueue("Target:Castle;Type:Knight;Damage:" + std::to_string(message.damage));

        // Lower castle HP by damage amount
        Instance()->setHit_points(Instance()->getHit_points() - message.damage);

        // If castle is dead
        if (Instance()->getHit_points() <= 0)
        {
            ThreadManager::WriteParentPipe(0);

            exitmessage = "Castle: \"Quel désastre!\"";
            ThreadManager::KillCastleAttackerThread();
            std::cout << exitmessage << endl;
            ThreadManager::WriteLoggerQueue(exitmessage);
            break;
        }
    }
}

void Castle::CastleSigHandler(int sig, siginfo_t *si, void *ucontext)
{
    int knight = si->si_value.sival_int;

    // Need to check if target is valid to prevent decrementing valid_knight_count twice from a knight running then dying
    if (instance->isTargetValid(knight))
    {
        instance->invalidateTarget(knight);
        instance->setValid_target_count(instance->getValid_target_count() - 1);
    }

    // Notify knight bookkeeper of their imminent death
    struct Message message;
    message.from = 0;
    message.type = -1;
    message.damage = 0;
    ThreadManager::WriteKnightQueue(knight, message);
}
// End Castle functions for threaded process