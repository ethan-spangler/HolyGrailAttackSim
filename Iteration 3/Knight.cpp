//
// Created by Ethan on 12/1/2019.
//

#include "Knight.h"

// Init static variables
int Knight::knight_count = 0;
string Knight::knight_setup_file_name;

// Start Constructors
Knight::Knight(){}
Knight::Knight(int number, const string &name, int hit_points, int bravery, int attack_rate, int damage) :
    knight_number(number),
    name(name),
    hit_points(hit_points),
    bravery(bravery),
    attack_rate(attack_rate),
    damage(damage)
    {
        present = true;
        alive = true;
    }

Knight::Knight(Knight* knight):
    knight_number(knight->knight_number),
    name(knight->name),
    hit_points(knight->hit_points),
    bravery(knight->bravery),
    attack_rate(knight->attack_rate),
    damage(knight->damage),
    present(knight->present),
    alive(knight->alive){}

// End Constructors

// Start Knight Creation
Knight* Knight::CreateKnightsFromFile(){

    Knight* knights;
    string line;

    std::ifstream knight_file;
    knight_file.open(knight_setup_file_name);

    if (knight_file.is_open())
    {
        ThreadManager::WriteLoggerQueue("Knight setup file opened successfully");

        knight_count = GetFileIntegerInputInRange(knight_file, "Count", "count:", 0, 6);
        if (knight_count < 1 || knight_count > 5)
        {
            ThreadManager::WriteLoggerQueue("Knight count out of bounds");
            ThreadManager::WriteLoggerQueue("\a");
            cout << "Knight count out of bounds. Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        knights = new Knight[knight_count];

        if (getline(knight_file, line) && line.length() > 1)
        {
            ThreadManager::WriteLoggerQueue("Missing blank line in knight file");
            ThreadManager::WriteLoggerQueue("\a");
            cout << "Missing blank line in knight file. Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < knight_count; i++)
        {
            // Knight Fields
            string knight_name;
            int knight_hp;
            int knight_bravery;
            int knight_rate;
            int knight_damage;

            // name
            if (getline(knight_file, line) && line.compare(0, 5, "name:") == 0) {
                if (line.length() > 56 || line.length() < 8) {
                    ThreadManager::WriteLoggerQueue("Knight name incorrect length");
                    ThreadManager::WriteLoggerQueue("\a");
                    cout << "Knight name not between 2 and 50 characters in length. Program Exiting..." << endl;
                    exit(EXIT_FAILURE);
                }
                knight_name = std::move(line.substr(5, line.length()-6));
            } else {
                ThreadManager::WriteLoggerQueue("Knight Name line not found or out of order");
                ThreadManager::WriteLoggerQueue("\a");
                cout << "Knight Name line not found or out of order. Program Exiting..." << endl;
                exit(EXIT_FAILURE);
            }
            ThreadManager::WriteLoggerQueue("name:" + knight_name);

            knight_hp = GetFileIntegerInputInRange(knight_file, "Hitpoints", "hp:", 25, 50);

            knight_bravery = GetFileIntegerInputInRange(knight_file, "Bravery", "bravery:", 0, knight_hp);

            knight_rate = GetFileIntegerInputInRange(knight_file, "Attack Rate", "rate:", 10, 50);

            knight_damage = GetFileIntegerInputInRange(knight_file, "Damage", "damage:", 1, 9);

            knights[i] = Knight(i, knight_name, knight_hp, knight_bravery, knight_rate, knight_damage);
            ThreadManager::WriteLoggerQueue("Knight successfully initialized");

            if (i < knight_count - 1)
            {
                if (getline(knight_file, line) && line.length() > 1)
                {
                    ThreadManager::WriteLoggerQueue("Missing blank line in knight file. Program Exiting...");
                    ThreadManager::WriteLoggerQueue("\a");
                    cout << "Missing blank line in knight file. Program Exiting..." << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    } else {
        ThreadManager::WriteLoggerQueue("Unable to open Knight Setup File");
        ThreadManager::WriteLoggerQueue("\a");
        cout << "Unable to open Knight Setup File. Program Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    return knights;
}
// End Knight Creation

// Start Getters/Setters
int Knight::getKnight_Number() const
{
    return knight_number;
}

const string &Knight::getName() const
{
    return name;
}

void Knight::setName(const string &name)
{
    Knight::name = name;
}

int Knight::getHit_points() const
{
    return hit_points;
}

void Knight::setHit_points(int hit_points)
{
    Knight::hit_points = hit_points;
}

int Knight::getBravery() const
{
    return bravery;
}

void Knight::setBravery(int bravery)
{
    Knight::bravery = bravery;
}

int Knight::getAttack_rate() const
{
    return attack_rate;
}

void Knight::setAttack_rate(int attack_rate)
{
    Knight::attack_rate = attack_rate;
}

int Knight::getDamage() const
{
    return damage;
}

void Knight::setDamage(int damage)
{
    Knight::damage = damage;
}

int Knight::getKnight_count()
{
    return knight_count;
}

void Knight::setKnight_count(int knight_count)
{
    Knight::knight_count = knight_count;
}

bool Knight::isAlive() const
{
    return alive;
}

void Knight::setAlive(bool alive)
{
    Knight::alive = alive;
}

bool Knight::isPresent() const
{
    return present;
}

void Knight::setPresent(bool present)
{
    Knight::present = present;
}

const string &Knight::getKnight_setup_file_name()
{
    return knight_setup_file_name;
}

void Knight::setKnight_setup_file_name(const string &knight_setup_file_name)
{
    Knight::knight_setup_file_name = knight_setup_file_name;
}
// End Getters/Setters





// Knight Helpers

// Get line from knight setup file stream, validate limits, and return int value
int Knight::GetFileIntegerInputInRange(std::ifstream& knightFile, string fieldName, string logName, int lowerLimit, int upperLimit) {
    int logNameLength = logName.length();
    string line;
    int intConvertedFromLine = 0;

    if (getline(knightFile, line) && line.compare(0, logNameLength, logName) == 0){
        try {
            intConvertedFromLine = std::stoi(line.substr(logNameLength, line.length() - logNameLength), nullptr);
        } catch (...) {
            ThreadManager::WriteLoggerQueue("Exception occurred parsing knight " + fieldName);
            ThreadManager::WriteLoggerQueue("\a");
            cout << "Exception occurred parsing knight " << fieldName << ". Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        if (intConvertedFromLine < lowerLimit || intConvertedFromLine > upperLimit) {
            ThreadManager::WriteLoggerQueue("Knight " + fieldName + " out of bounds");
            ThreadManager::WriteLoggerQueue("\a");
            cout << "Knight " << fieldName << " out of bounds. Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

    } else {
        ThreadManager::WriteLoggerQueue("Knight " + fieldName + " line not found or out of order");
        ThreadManager::WriteLoggerQueue("\a");
        cout << "Knight " << fieldName << " line not found or out of order. Program Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    ThreadManager::WriteLoggerQueue(logName + std::to_string(intConvertedFromLine));
    return intConvertedFromLine;
}
// End Knight Helpers

// Start knight functions for threaded process
void *Knight::KnightAttackerProcess(void *args)
{
    Knight knight = *(Knight*) args;
    struct timespec ts = {0, knight.getAttack_rate() * 1000L}; // nanoseconds -> microseconds

    Message message;
    message.from = knight.getKnight_Number() + 1;
    message.type = 3; // Knight attack
    message.damage = knight.getDamage();
    while(true) // This keeps on going until the attacker process is killed with SIGTERM
    {
        nanosleep(&ts, NULL); // Sleep for knight attack rate in microseconds

        // Attack the castle by notifying it's bookkeeping process
        ThreadManager::WriteCastleQueue(message);
    }
}

void *Knight::KnightBookkeeperProcess(void *args)
{
    Knight knight = *(Knight*) args;
    string exit_message;
    while (true)
    {
        struct Message message = ThreadManager::ReadKnightQueue(knight.getKnight_Number());
        // Check if castle is dead
        if (message.damage == -1)
        {
            ThreadManager::KillKnightAttackerThread(knight.getKnight_Number());

            std::cout << knight.getName() + ": \"Huzzah! Down with the French!\"" << endl;
            ThreadManager::WriteLoggerQueue(knight.getName() + ": \"Huzzah! Down with the French!\"");
            break;
        }

        // Check for exit message from castle bookkeeper
        if (message.type == -1)
        {
            break;
        }

        // Convert integer type to string type
        std::string attack_type;
        switch (message.type)
        {
            case 0:
                attack_type = "Taunt";
                break;
            case 1:
                attack_type = "Cow";
                break;
            case 2:
                attack_type = "Rabbit";
                break;
            default:
                break;
        }

        // Log message that comes in
        ThreadManager::WriteLoggerQueue("Target:" + knight.getName() + ";Type:" + attack_type + ";Damage:"
                                        + std::to_string(message.damage));

        // Lower HP by damage amount
        knight.setHit_points(knight.getHit_points() - message.damage);

        // If knight is dead
        if (knight.getHit_points() <= 0 && knight.isAlive())
        {
            knight.setAlive(false); // Prevent knight from dying twice
            knight.setPresent(false); // prevent the dead knight from fleeing
            ThreadManager::WriteParentPipe(knight.getKnight_Number() + 1);

            // Kill off the attacker process
            ThreadManager::KillKnightAttackerThread(knight.getKnight_Number());
            exit_message = knight.getName() + " KILLED by " + attack_type;

            // Spit out death message to standard output and logger
            cout << exit_message << endl;
            ThreadManager::WriteLoggerQueue(exit_message);
        }

        // If knight is too scared, they will run away
        if (knight.getHit_points() < knight.getBravery() && knight.isPresent())
        {
            knight.setPresent(false);
            ThreadManager::WriteParentPipe(knight.getKnight_Number() + 1);

            // Kill off the attacker process
            ThreadManager::KillKnightAttackerThread(knight.getKnight_Number());
            exit_message = knight.getName() + " RUNS AWAY from " + attack_type;

            // Spit out run away message to standard output and to the logger
            cout << exit_message << endl;
            ThreadManager::WriteLoggerQueue(exit_message);
        }
    }
}
// End knight functions for threaded process