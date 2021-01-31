//
// Created by Ethan on 9/11/2019.
//

#include "Knight.h"

int Knight::knight_count = 0;

// Start Constructors
Knight::Knight(){}
Knight::Knight(std::string name, int hitPoints, int bravery, int attackRate, int damage){
    this->name = name;
    this->hit_points = hitPoints;
    this->bravery = bravery;
    this->attack_rate = attackRate;
    this->damage = damage;
    this->alive = true;
    this->present = true;
}

// End Constructors

// Start Getters and Setters
std::string Knight::getName() const {
    return name;
}

void Knight::setName(const std::string &name) {
    Knight::name = name;
}

int Knight::getHitPoints() const {
    return hit_points;
}

void Knight::setHitPoints(int hitPoints) {
    hit_points = hitPoints;
}

int Knight::getBravery() const {
    return bravery;
}

void Knight::setBravery(int bravery) {
    Knight::bravery = bravery;
}

int Knight::getAttackRate() const {
    return attack_rate;
}

void Knight::setAttackRate(int attackRate) {
    attack_rate = attackRate;
}

int Knight::getDamage() const {
    return damage;
}

void Knight::setDamage(int damage) {
    Knight::damage = damage;
}

bool Knight::isAlive() const {
    return alive;
}

void Knight::setAlive(bool alive) {
    Knight::alive = alive;
}

bool Knight::isPresent() const {
    return present;
}

void Knight::setPresent(bool present) {
    Knight::present = present;
}

// End Getters and Setters

Knight* Knight::CreateKnightsFromFile(){

    Knight* knights;
    string line;

    std::ifstream knight_file;
    knight_file.open(Helper::knight_file_name);

    if (knight_file.is_open())
    {
        PipeManager::write_logger("Knight setup file opened successfully");

        knight_count = GetFileIntegerInputInRange(knight_file, "Count", "count:", 0, 6);
        if (knight_count < 1 || knight_count > 5)
        {
            PipeManager::write_logger("Knight count out of bounds");
            PipeManager::write_logger("\a");
            cout << "Knight count out of bounds. Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        knights = new Knight[knight_count];

        if (getline(knight_file, line) && line.length() > 1)
        {
            PipeManager::write_logger("Missing blank line in knight file");
            PipeManager::write_logger("\a");
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
                    PipeManager::write_logger("Knight name incorrect length");
                    PipeManager::write_logger("\a");
                    cout << "Knight name not between 2 and 50 characters in length. Program Exiting..." << endl;
                    exit(EXIT_FAILURE);
                }
                knight_name = std::move(line.substr(5, line.length()-6));
            } else {
                PipeManager::write_logger("Knight Name line not found or out of order");
                PipeManager::write_logger("\a");
                cout << "Knight Name line not found or out of order. Program Exiting..." << endl;
                exit(EXIT_FAILURE);
            }
            PipeManager::write_logger("name:" + knight_name);

            knight_hp = GetFileIntegerInputInRange(knight_file, "Hitpoints", "hp:", 25, 50);

            knight_bravery = GetFileIntegerInputInRange(knight_file, "Bravery", "bravery:", 0, knight_hp);

            knight_rate = GetFileIntegerInputInRange(knight_file, "Attack Rate", "rate:", 10, 50);

            knight_damage = GetFileIntegerInputInRange(knight_file, "Damage", "damage:", 1, 9);

            knights[i] = Knight(knight_name, knight_hp, knight_bravery, knight_rate, knight_damage);
            PipeManager::write_logger("Knight successfully initialized");

            if (i < knight_count - 1)
            {
                if (getline(knight_file, line) && line.length() > 1)
                {
                    PipeManager::write_logger("Missing blank line in knight file. Program Exiting...");
                    PipeManager::write_logger("\a");
                    cout << "Missing blank line in knight file. Program Exiting..." << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    } else {
        PipeManager::write_logger("Unable to open Knight Setup File");
        PipeManager::write_logger("\a");
        cout << "Unable to open Knight Setup File. Program Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    return knights;
}

Knight* Knight::CreateKnightsRandomly() {
    srand(time(NULL));
    std::string names_for_randomizer[] = {"Adam", "Benjamin", "Batch", "Gulko", "Raseem", "Bedwyr", "Digon",
                                          "Roland", "Oliver", "Anthony", "Harrison", "Ross", "Fry", "Philip",
                                          "Artor", "Nele", "Aldus", "Lovet", "Ligart", "Deryk", "Ramondin"};

    knight_count = rand() % 5 + 1; // 1 - 5
    Knight temp[knight_count]; // create temporary array

    string knight_name;
    int knight_hp;
    int knight_bravery;
    int knight_rate;
    int knight_damage;

    for (int i = 0; i < knight_count; i++)
    {
        knight_name = names_for_randomizer[rand() % 21];
        PipeManager::write_logger("name:" + knight_name);

        knight_hp = rand() % 26 + 25; // 25 - 50
        PipeManager::write_logger("hp:" + std::to_string(knight_hp));

        knight_bravery = rand() % knight_hp; // 0 - hp
        PipeManager::write_logger("bravery:" + std::to_string(knight_bravery));

        knight_rate = rand() % 41 + 10; // 10 - 50
        PipeManager::write_logger("rate:" + std::to_string(knight_rate));

        knight_damage = rand() % 9 + 1; // 1 - 9
        PipeManager::write_logger("damage:" + std::to_string(knight_damage));


        temp[i] = Knight(knight_name, knight_hp, knight_bravery, knight_rate, knight_damage);
        PipeManager::write_logger("Knight successfully initialized");
    }

    return temp;
}

Knight* Knight::CreateKnightsFromUserInput() {
    Knight* knights;
    std::istream& input = std::cin;
    string line;

    cout << "Would you like to randomize all of your Knights? (yes|no)";
    getline(input, line);

    if (line != "no") { // Gonna go ahead an assume that if they didn't specificly put no, then we will randomize
        knights = CreateKnightsRandomly();
    }
    else {
        knight_count = GetUserIntegerInputInRange("Knight Count", "How many knights are in your party", 1, 5);

        knights = new Knight[knight_count];
        // For each knight...
        for (int i = 0; i < knight_count; i++) {

            // Knight Fields
            string knight_name;
            int knight_hp;
            int knight_bravery;
            int knight_rate;
            int knight_damage;

            {//name on its own block so block-scope variables get cleaned up
                int mistake_count = 0;
                bool valid = false;
                do {
                    cout << "What is the name of this knight? ";
                    getline(input, line);

                    if (line.length() > 50 || line.length() < 2) {
                        mistake_count++;
                        cout << "Name should be between 2 and 50 characters in length";
                        PipeManager::write_logger(
                                "User inputted knight name of incorrect length. Consecutive Mistake Count: "
                                + std::to_string(mistake_count));
                    } else {
                        knight_name = std::move(line);
                        valid = true;
                    }

                    checkMistakeCount(mistake_count);
                } while (!valid);
            }
            PipeManager::write_logger("name:" + knight_name);

            knight_hp = GetUserIntegerInputInRange("Knight HP", "How many hitpoints does this knight have?", 25, 50);
            PipeManager::write_logger("hp:" + std::to_string(knight_hp));

            knight_bravery = GetUserIntegerInputInRange("Knight Bravery", "How much bravery does this knight have?",
                    0, knight_hp);
            PipeManager::write_logger("bravery:" + std::to_string(knight_bravery));

            knight_rate = GetUserIntegerInputInRange("Knight Attack Rate", "What attack rate does this knight have?",
                    10, 50);
            PipeManager::write_logger("rate:" + std::to_string(knight_rate));

            knight_damage = GetUserIntegerInputInRange("Knight Damage", "How much damage does this knight do?", 1, 9);
            PipeManager::write_logger("damage:" + std::to_string(knight_damage));

            knights[i] = Knight(knight_name, knight_hp, knight_bravery, knight_rate, knight_damage);
            PipeManager::write_logger("Knight successfully initialized");
        }
    }

    return knights;
}

int Knight::GetUserIntegerInputInRange(string fieldName, string prompt, int lowerLimit, int upperLimit) {
    std::istream& input = std::cin;
    string lineOfInput;
    int intConvertedFromLineOfInput = 0;
    int mistake_count = 0;
    bool valid = false;

    do {
        cout << prompt << " [" << lowerLimit << ", " << upperLimit << "] ";
        getline(input, lineOfInput);

        try {
            intConvertedFromLineOfInput = std::stoi(lineOfInput, nullptr);

            if (intConvertedFromLineOfInput < lowerLimit || intConvertedFromLineOfInput > upperLimit) {
                mistake_count++;

                cout << "Input outside of numerical range [" << lowerLimit << ", " << upperLimit
                     << "]. Consecutive Mistakes: "<< mistake_count << endl;

                PipeManager::write_logger("User inputted out of range input for " + fieldName
                                                + ". Consecutive Mistake Count: " + std::to_string(mistake_count));
            } else {
                valid = true;
            }
        } catch (...) {
            mistake_count++;
            cout << "Invalid integer provided. Consecutive Mistakes: " << mistake_count << endl;
            PipeManager::write_logger("User inputted out of range input for " + fieldName
                                            + ". Consecutive Mistake Count: " + std::to_string(mistake_count));
        }

        checkMistakeCount(mistake_count);
    } while (!valid);
    return intConvertedFromLineOfInput;
}

int Knight::GetFileIntegerInputInRange(std::ifstream& knightFile, string fieldName, string logName, int lowerLimit, int upperLimit) {
    int logNameLength = logName.length();
    string line;
    int intConvertedFromLine = 0;

    if (getline(knightFile, line) && line.compare(0, logNameLength, logName) == 0){
        try {
            intConvertedFromLine = std::stoi(line.substr(logNameLength, line.length() - logNameLength), nullptr);
        } catch (...) {
            PipeManager::write_logger("Exception occurred parsing knight " + fieldName);
            PipeManager::write_logger("\a");
            cout << "Exception occurred parsing knight " << fieldName << ". Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        if (intConvertedFromLine < lowerLimit || intConvertedFromLine > upperLimit) {
            PipeManager::write_logger("Knight " + fieldName + " out of bounds");
            PipeManager::write_logger("\a");
            cout << "Knight " << fieldName << " out of bounds. Program Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

    } else {
        PipeManager::write_logger("Knight " + fieldName + " line not found or out of order");
        PipeManager::write_logger("\a");
        cout << "Knight " << fieldName << " line not found or out of order. Program Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    PipeManager::write_logger(logName + std::to_string(intConvertedFromLine));
    return intConvertedFromLine;
}

void Knight::checkMistakeCount(int mistakeCount) {
    if (mistakeCount >= 3)
    {
        PipeManager::write_logger("User made more than 3 mistakes in a row. Program Exiting...");
        PipeManager::write_logger("\a");
        cout << "Consecutive mistake count too high. Program Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

int Knight::GetKnightCount() {
    return knight_count;
}

void Knight::KnightAttackerProcessor(Knight knight, int knight_number) {
    struct timespec ts = {0, knight.getAttackRate() * 1000L}; // nanoseconds -> microseconds

    struct Message message;
    message.from = knight_number;
    message.type = 3;
    message.damage = knight.getDamage();

    while(true) // This keeps on going until the attacker process is killed with SIGTERM
    {
        nanosleep(&ts, NULL); // Sleep for knight attack rate in microseconds

        PipeManager::write_castle_bookkeep(message);
    }
}

void Knight::KnightBookkeeperProcessor(Knight knight, int knight_number, int pid_knight_attacker) {
    string exit_message;

    while (true)
    {
        struct Message message = PipeManager::read_knight_bookkeep(knight_number-1);

        // Check if castle is dead
        if (message.damage == -1)
        {
            kill(pid_knight_attacker, SIGTERM);

            std::cout << knight.getName() + ": \"Huzzah! Down with the French!\"" << endl;
            PipeManager::write_logger(knight.getName() + ": \"Huzzah! Down with the French!\"");
            exit(1);
        }

        // Check for exit message
        if (message.type == -1)
        {
            exit(1);
        }

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
        PipeManager::write_logger("Target:" + knight.getName() + ";Type:" + attack_type + ";Damage:"
                                  + std::to_string(message.damage));

        // Lower HP by damage amount
        knight.setHitPoints(knight.getHitPoints() - message.damage);

        // If knight is dead
        if (knight.getHitPoints() <= 0 && knight.isAlive())
        {
            knight.setAlive(false); // Prevent knight from dying twice
            knight.setPresent(false); // prevent the dead knight from fleeing
            PipeManager::write_parent(knight_number);

            kill(pid_knight_attacker, SIGTERM);
            exit_message = knight.getName() + " KILLED by " + attack_type;

            cout << exit_message << endl;
            PipeManager:: write_logger(exit_message);
        }

        // If knight is too scared, they will run away
        if (knight.getHitPoints() < knight.getBravery() && knight.isPresent())
        {
            knight.setPresent(false);
            PipeManager::write_parent(knight_number);

            kill(pid_knight_attacker, SIGTERM);
            exit_message = knight.getName() + " RUNS AWAY from " + attack_type;

            cout << exit_message << endl;
            PipeManager:: write_logger(exit_message);
        }
    }
}

