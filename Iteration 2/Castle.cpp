//
// Created by Ethan on 9/11/2019.
//

#include "Castle.h"

bool* Castle::valid_targets = nullptr;
int Castle::valid_target_count = 0;


// Start Constructors
Castle::Castle() {}
Castle::Castle(int hitPoints, int attackRate, int attackChanceTaunt, int attackChanceCow, int attackChanceRabbit,
               int damageWeak, int damageStrong){
    hit_points = hitPoints;
    attack_rate = attackRate;
    attack_chance_taunt = attackChanceTaunt;
    attack_chance_cow = attackChanceCow;
    attack_chance_rabbit = attackChanceRabbit;
    damage_weak = damageWeak;
    damage_strong = damageStrong;

    Castle::valid_targets = new bool[5];
    for(int i = 0; i < 5; i++)
        Castle::valid_targets[i] = false;
}
// End Constructors

void Castle::sigusr1_handler(int sig, siginfo_t *si, void *ucontext) {
    int knight = si->si_value.sival_int;
    invalidateTarget(knight);
    setValid_target_count(getValid_target_count()-1);

    struct Message message;
    message.from = 0;
    message.type = -1;
    message.damage = 0;

    PipeManager::write_knight_bookkeep(knight, message);
}

// Start Getters and Setters
int Castle::getHitPoints() const {
    return hit_points;
}

void Castle::setHitPoints(int hitPoints) {
    hit_points = hitPoints;
}

int Castle::getAttackRate() const {
    return attack_rate;
}

void Castle::setAttackRate(int attackRate) {
    attack_rate = attackRate;
}

int Castle::getAttackChanceTaunt() const {
    return attack_chance_taunt;
}

void Castle::setAttackChanceTaunt(int attackChanceTaunt) {
    attack_chance_taunt = attackChanceTaunt;
}

int Castle::getAttackChanceCow() const {
    return attack_chance_cow;
}

void Castle::setAttackChanceCow(int attackChanceCow) {
    attack_chance_cow = attackChanceCow;
}

int Castle::getAttackChanceRabbit() const {
    return attack_chance_rabbit;
}

void Castle::setAttackChanceRabbit(int attackChanceRabbit) {
    attack_chance_rabbit = attackChanceRabbit;
}

int Castle::getDamageWeak() const {
    return damage_weak;
}

void Castle::setDamageWeak(int damageWeak) {
    damage_weak = damageWeak;
}

int Castle::getDamageStrong() const {
    return damage_strong;
}

void Castle::setDamageStrong(int damageStrong) {
    damage_strong = damageStrong;
}

int Castle::getValid_target_count() {
    return valid_target_count;
}

void Castle::setValid_target_count(int valid_target_count) {
    Castle::valid_target_count = valid_target_count;
}

// End Getters and Setters

Castle Castle::CreateCastleFromFile() {
    int castle_hp;
    int castle_rate;
    int castle_taunt;
    int castle_cow;
    int castle_rabbit;
    int castle_weak;
    int castle_strong;

    string line;
    ifstream castle_file(Helper::castle_file_name);

    if (castle_file.is_open())
    {
        PipeManager::write_logger("Castle setup file opened successfully");


        castle_hp = GetFileIntegerInputInRange(castle_file, "Hitpoints", "hp:", 100, 300);
        castle_rate = GetFileIntegerInputInRange(castle_file, "Attack Rate", "rate:", 1, 100);
        castle_taunt = GetFileIntegerInputInRange(castle_file, "Taunt Attack Chance", "taunt:", 75, 89);
        castle_cow = GetFileIntegerInputInRange(castle_file, "Cow Attack Chance", "cow:", 10, 20);
        castle_rabbit = GetFileIntegerInputInRange(castle_file, "Rabbit Attack Chance", "rabbit:", 1, 5);
        castle_weak = GetFileIntegerInputInRange(castle_file, "Weak Attack Damage", "weak:", 1, 9);
        castle_strong = GetFileIntegerInputInRange(castle_file, "Strong Attack Damage", "strong:", 25, 50);


        if ((castle_cow + castle_taunt + castle_rabbit) != 100) {
            PipeManager::write_logger("Castle attack chances do not add up to 100%");
            PipeManager::write_logger("\a");;
            cout << "Castle attack chances do not add up to 100%. Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        Castle castle = Castle(castle_hp, castle_rate, castle_taunt, castle_cow, castle_rabbit, castle_weak, castle_strong);
        PipeManager::write_logger("Castle successfully initialized");
        return castle;
    }
    else {
        PipeManager::write_logger("Unable to open Castle Setup File");
        PipeManager::write_logger("\a");;
        cout << "Unable to open Castle Setup File. Program Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

int Castle::GetFileIntegerInputInRange(std::ifstream& castleName, string fieldName, string logName, int lowerLimit, int upperLimit) {
    int logNameLength = logName.length();
    string line;
    int intConvertedFromLine = 0;

    if (getline(castleName, line) && line.compare(0, logNameLength, logName) == 0){
        try {
            intConvertedFromLine = std::stoi(line.substr(logNameLength, line.length() - logNameLength), nullptr);
        } catch (...) {
            PipeManager::write_logger("Exception occurred parsing castle " + fieldName);
            PipeManager::write_logger("\a");;
            cout << "Exception occurred parsing castle " << fieldName << ". Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        if (intConvertedFromLine < lowerLimit || intConvertedFromLine > upperLimit) {
            PipeManager::write_logger("Castle " + fieldName + " out of bounds");
            PipeManager::write_logger("\a");;
            cout << "Knight " << fieldName << " out of bounds. Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }
    } else {
        PipeManager::write_logger("Castle " + fieldName + " line not found or out of order");
        PipeManager::write_logger("\a");;
        cout << "Castle " << fieldName << " line not found or out of order. Program Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    PipeManager::write_logger(logName + std::to_string(intConvertedFromLine));
    return intConvertedFromLine;
}

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

void Castle::CastleAttackerProcessor(Castle castle) {
    // Set up stuff for sigusr1 signal
    struct sigaction action;
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = Castle::sigusr1_handler;

    sigaction(SIGUSR1, &action, NULL);
    // End setup for sigusr1 signal

    // First set up the valid targets array to number of knights
    castle.setValid_target_count(Knight::GetKnightCount());
    for (int i = 0; i < castle.getValid_target_count(); i++)
        castle.validateTarget(i);

    struct timespec ts = {0, castle.getAttackRate() * 1000L}; // nanoseconds -> microseconds

    struct Message message; // Lets go ahead and create a message so it doesnt need to be created every loop
    message.from = 0; // From Castle

    while (true)
    {
        nanosleep(&ts, NULL);

        if (getValid_target_count() == 0)
            break;

        int roll = rand() % 100 + 1; // 1 - 100

        if (roll <= castle.attack_chance_taunt)
        {
            message.type = 0; // TAUNT
            message.damage = castle.getDamageWeak();

            int target = castle.selectRandomValidKnight();
            if (target == -1) // If no valid knights
                break;

            PipeManager::write_knight_bookkeep(target, message);
        }
        else if (roll <= castle.attack_chance_taunt + castle.attack_chance_cow)
        {
            message.type = 1; // COW
            message.damage = castle.getDamageWeak();

            for (int i = 0; i < 5; i++)
            {
                if (castle.isTargetValid(i))
                    PipeManager::write_knight_bookkeep(i, message);
            }
        }
        else
        {
            message.type = 2; // RABBIT
            message.damage = castle.getDamageStrong();

            int target = castle.selectRandomValidKnight();
            if (target == -1) // If no valid knights
                break;

            PipeManager::write_knight_bookkeep(target, message);
        }
    }

    // All knights ded
    PipeManager::write_parent(-1);

    // Message to inform bookkeeper of the victory
    message.from = 0;
    message.type = -1;
    message.damage = 0;
    PipeManager::write_castle_bookkeep(message);

    exit(1);
}

void Castle::CastleBookkeeperProcessor(Castle castle, int pid_castle_attacker) {
    string exitmessage;
    while (true)
    {
        struct Message message = PipeManager::read_castle_bookkeep();

        // Check for message from castle_attacker saying that all knights are dead
        if (message.type == -1)
        {
            exitmessage = "Castle: \"La victoire est à nous!\"";
            std::cout << exitmessage << endl;
            PipeManager::write_logger(exitmessage);
            exit(1);
        }

        // Log message that comes in
        PipeManager::write_logger("Target:Castle;Type:Knight;Damage:" + std::to_string(message.damage));

        // Lower castle HP by damage amount
        castle.setHitPoints(castle.getHitPoints() - message.damage);

        // If castle is dead
        if (castle.getHitPoints() <= 0)
        {
            PipeManager::write_parent(0);

            exitmessage = "Castle: \"Quel désastre!\"";
            kill(pid_castle_attacker, SIGTERM);
            std::cout << exitmessage << endl;
            PipeManager::write_logger(exitmessage);
            exit(1);
        }
    }
}


