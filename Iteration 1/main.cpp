#include <iostream>
#include "Log.h"
#include "Helper.h"
#include "Castle.h"
#include "Knight.h"

using os_logging::Log;
using std::cout;
using std::endl;

int main(int argc, char** argv) {

    // Validate and parse command line arguments
    if (!Helper::parse_cli_arguments(argc, argv)) return EXIT_FAILURE;

    // Set up logfile
    Log log;
    if (Helper::log_file_name.empty())
        log = Log();
    else
        log = Log(Helper::log_file_name);
    log.open();

    // Read, Parse, and Validate castle setup file
    Castle castle;
    {
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
            log.writeLogRecord("Castle setup file opened successfully");

            // HP
            if (getline(castle_file, line) && line.compare(0, 3, "hp:") == 0) {
                try {
                    castle_hp = std::stoi(line.substr(3, line.length() - 3), nullptr);
                } catch (...) {
                    log.writeLogRecord("Exception occurred parsing castle hp. Program Exiting...");
                    log.close();
                    cout << "Exception occurred parsing castle hp. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                if (castle_hp > 300 || castle_hp < 100) {
                    log.writeLogRecord("Castle hp out of bounds. Program Exiting...");
                    log.close();
                    cout << "Castle hp out of bounds. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                log.writeLogRecord("hp:" + std::to_string(castle_hp));
            } else {
                log.writeLogRecord("Castle hp line not found or out of order");
                log.close();
                cout << "Castle hp line not found or out of order" << endl;
                return EXIT_FAILURE;
            }

            // Rate
            if (getline(castle_file, line) && line.compare(0, 5, "rate:") == 0) {
                try {
                    castle_rate = std::stoi(line.substr(5, line.length() - 5), nullptr);
                } catch (...) {
                    log.writeLogRecord("Exception occurred parsing castle rate. Program Exiting...");
                    log.close();
                    cout << "Exception occurred parsing castle rate. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                if (castle_rate > 100 || castle_rate < 1) {
                    log.writeLogRecord("Castle rate out of bounds. Program Exiting...");
                    log.close();
                    cout << "Castle rate out of bounds. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                log.writeLogRecord("rate:" + std::to_string(castle_rate));
            } else {
                log.writeLogRecord("Castle rate line not found or out of order");
                log.close();
                cout << "Castle rate line not found or out of order" << endl;
                return EXIT_FAILURE;
            }

            // taunt
            if (getline(castle_file, line) && line.compare(0, 6, "taunt:") == 0) {
                try {
                    castle_taunt = std::stoi(line.substr(6, line.length() - 6), nullptr);

                } catch (...) {
                    log.writeLogRecord("Exception occurred parsing castle taunt. Program Exiting...");
                    log.close();
                    cout << "Exception occurred parsing castle taunt. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                if (castle_taunt > 89 || castle_taunt < 75) {
                    log.writeLogRecord("Castle taunt out of bounds. Program Exiting...");
                    log.close();
                    cout << "Castle taunt out of bounds. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                log.writeLogRecord("taunt:" + std::to_string(castle_taunt));
            } else {
                log.writeLogRecord("Castle taunt line not found or out of order");
                log.close();
                cout << "Castle taunt line not found or out of order" << endl;
                return EXIT_FAILURE;
            }

            // cow
            if (getline(castle_file, line) && line.compare(0, 4, "cow:") == 0) {
                try {
                    castle_cow = std::stoi(line.substr(4, line.length() - 4), nullptr);
                } catch (...) {
                    log.writeLogRecord("Exception occurred parsing castle cow. Program Exiting...");
                    log.close();
                    cout << "Exception occurred parsing castle cow. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                if (castle_cow > 20 || castle_cow < 10) {
                    log.writeLogRecord("Castle cow out of bounds. Program Exiting...");
                    log.close();
                    cout << "Castle cow out of bounds. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                log.writeLogRecord("cow:" + std::to_string(castle_cow));
            } else {
                log.writeLogRecord("Castle cow line not found or out of order");
                log.close();
                cout << "Castle cow line not found or out of order" << endl;
                return EXIT_FAILURE;
            }

            // rabbit
            if (getline(castle_file, line) && line.compare(0, 7, "rabbit:") == 0) {
                try {
                    castle_rabbit = std::stoi(line.substr(7, line.length() - 7), nullptr);
                } catch (...) {
                    log.writeLogRecord("Exception occurred parsing castle rabbit. Program Exiting...");
                    log.close();
                    cout << "Exception occurred parsing castle rabbit. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                if (castle_rabbit > 5 || castle_rabbit < 1) {
                    log.writeLogRecord("Castle rabbit out of bounds. Program Exiting...");
                    log.close();
                    cout << "Castle rabbit out of bounds. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                log.writeLogRecord("rabbit:" + std::to_string(castle_rabbit));
            } else {
                log.writeLogRecord("Castle rabbit line not found or out of order");
                log.close();
                cout << "Castle rabbit line not found or out of order" << endl;
                return EXIT_FAILURE;
            }

            // weak
            if (getline(castle_file, line) && line.compare(0, 5, "weak:") == 0) {
                try {
                    castle_weak = std::stoi(line.substr(5, line.length() - 5), nullptr);
                } catch (...) {
                    log.writeLogRecord("Exception occurred parsing castle weak. Program Exiting...");
                    log.close();
                    cout << "Exception occurred parsing castle weak. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                if (castle_weak > 9 || castle_weak < 1) {
                    log.writeLogRecord("Castle weak out of bounds. Program Exiting...");
                    log.close();
                    cout << "Castle weak out of bounds. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                log.writeLogRecord("weak:" + std::to_string(castle_weak));
            } else {
                log.writeLogRecord("Castle weak line not found or out of order");
                log.close();
                cout << "Castle weak line not found or out of order" << endl;
                return EXIT_FAILURE;
            }

            // strong
            if (getline(castle_file, line) && line.compare(0, 7, "strong:") == 0) {
                try {
                    castle_strong = std::stoi(line.substr(7, line.length() - 7), nullptr);
                } catch (...) {
                    log.writeLogRecord("Exception occurred parsing castle strong. Program Exiting...");
                    log.close();
                    cout << "Exception occurred parsing castle strong. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                if (castle_strong > 50 || castle_strong < 25) {
                    log.writeLogRecord("Castle strong out of bounds. Program Exiting...");
                    log.close();
                    cout << "Castle strong out of bounds. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                log.writeLogRecord("strong:" + std::to_string(castle_strong));
            } else {
                log.writeLogRecord("Castle strong line not found or out of order");
                log.close();
                cout << "Castle strong line not found or out of order" << endl;
                return EXIT_FAILURE;
            }

            if ((castle_cow + castle_taunt + castle_rabbit) != 100) {
                log.writeLogRecord("Castle attack chances do not add up to 100%. Program Exiting...");
                log.close();
                cout << "Castle attack chances do not add up to 100%. Program Exiting..." << endl;
                return EXIT_FAILURE;
            }

            castle = Castle(castle_hp, castle_rate, castle_taunt, castle_cow, castle_rabbit, castle_weak, castle_strong);
            log.writeLogRecord("Castle successfully initialized");
        }
        else {
            log.writeLogRecord("Unable to open Castle Setup File. Program Exiting...");
            log.close();
            cout << "Unable to open Castle Setup File. Program Exiting..." << endl;
            return EXIT_FAILURE;
        }
    }

    // TODO - Read in knights stuff
    Knight* knights;
    {
        // 21 knight names for randomizer
        std::string names_for_randomizer[] = {"Adam", "Benjamin", "Batch", "Gulko", "Raseem", "Bedwyr", "Digon",
                                                     "Roland", "Oliver", "Anthony", "Harrison", "Ross", "Fry", "Philip",
                                                     "Artor", "Nele", "Aldus", "Lovet", "Ligart", "Deryk", "Ramondin"};

        int knight_count;

        string knight_name;
        int knight_hp;
        int knight_bravery;
        int knight_rate;
        int knight_damage;

        string line;
        std::ifstream knight_file;

        bool user_input = Helper::knight_file_name.empty();
        int mistakes_count = 0; // User can have up to 3 mistakes before walking the plank

        if (!user_input) knight_file.open(Helper::knight_file_name);
        std::istream& input = user_input ? std::cin : knight_file;

        // Check if user wants to randomize Knights
        if (user_input) {
            cout << "Would you like to randomize all of your Knights? (yes|no)";
            getline(input, line);

            if (line == "yes") {
                srand(time(NULL));

                knight_count = rand() % 5 + 1; // 1 - 5
                Knight temp[knight_count]; // create temporary array
                knights = temp; // move it to knights object
                for (int i = 0; i < knight_count; i++)
                {
                    knight_name = names_for_randomizer[rand() % 21];
                    log.writeLogRecord("name:" + knight_name);

                    knight_hp = rand() % 26 + 25; // 25 - 50
                    log.writeLogRecord("hp:" + std::to_string(knight_hp));

                    knight_bravery = rand() % knight_hp; // 0 - hp
                    log.writeLogRecord("bravery:" + std::to_string(knight_bravery));

                    knight_rate = rand() % 41 + 10; // 10 - 50
                    log.writeLogRecord("rate:" + std::to_string(knight_rate));

                    knight_damage = rand() % 9 + 1; // 1 - 9
                    log.writeLogRecord("damage:" + std::to_string(knight_damage));


                    knights[i] = Knight(knight_name, knight_hp, knight_bravery, knight_rate, knight_damage);
                    log.writeLogRecord("Knight successfully initialized");
                }
            }
            else
            {
                bool valid = false;

                // count
                while (!valid) {
                    cout << "How many Knights are in your party? ";
                    getline(input, line);

                    try {
                        knight_count = std::stoi(line, nullptr);
                        if (knight_count < 1 || knight_count > 5)
                        {
                            cout << "Please enter a number between 1 and 5." << endl;
                            mistakes_count++;
                        } else {
                            valid = true;
                        }
                    } catch (...) {
                        cout << "Please enter a number between 1 and 5." << endl;
                        mistakes_count++;
                    }

                    if (mistakes_count > 3) {
                        log.writeLogRecord("User made more than 3 mistakes in a row. Program Exiting...");
                        log.close();
                        cout << "User made more than 3 mistakes in a row. Program Exiting..." << endl;
                        return EXIT_FAILURE;
                    }
                }

                // For each knight...
                for (int i = 0; i < knight_count; i++) {
                    //name
                    mistakes_count = 0;
                    valid = false;
                    while(!valid) {
                        cout << "What is the name of this knight? ";
                        getline(input, line);

                        if (line.length() > 50 || line.length() < 2)
                        {
                            cout << "Please enter a string between 2 and 50 characters.";
                            mistakes_count++;
                        } else {
                            knight_name = std::move(line);
                            valid = true;
                            log.writeLogRecord("name:" + knight_name);
                        }

                        if (mistakes_count > 3) {
                            log.writeLogRecord("User made more than 3 mistakes in a row. Program Exiting...");
                            log.close();
                            cout << "User made more than 3 mistakes in a row. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }
                    }

                    //hp
                    mistakes_count = 0;
                    valid = false;
                    while (!valid) {
                        cout << "How much HP does this knight have? [25, 50] ";
                        getline(input, line);

                        try {
                            knight_hp = std::stoi(line, nullptr);

                            if (knight_hp > 50 || knight_hp < 25) {
                                cout << "Please enter a number between 25 and 50." << endl;
                                mistakes_count++;
                            } else {
                                valid = true;
                                log.writeLogRecord("hp:" + std::to_string(knight_hp));
                            }
                        } catch (...) {
                            cout << "Please enter a number between 25 and 50." << endl;
                            mistakes_count++;
                        }

                        if (mistakes_count > 3) {
                            log.writeLogRecord("User made more than 3 mistakes in a row. Program Exiting...");
                            log.close();
                            cout << "User made more than 3 mistakes in a row. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }
                    }

                    //bravery
                    mistakes_count = 0;
                    valid = false;
                    while (!valid) {
                        cout << "How much bravery does this knight have? (up to " << knight_hp << ") ";
                        getline(input, line);

                        try {
                            knight_bravery = std::stoi(line, nullptr);

                            if (knight_bravery > knight_hp || knight_bravery < 0) {
                                cout << "Please enter a number between 0 and" << knight_hp << endl;
                                mistakes_count++;
                            } else {
                                valid = true;
                                log.writeLogRecord("bravery:" + std::to_string(knight_bravery));
                            }
                        } catch (...) {
                            cout << "Please enter a number between 0 and" << knight_hp << endl;                            mistakes_count++;
                        }

                        if (mistakes_count > 3) {
                            log.writeLogRecord("User made more than 3 mistakes in a row. Program Exiting...");
                            log.close();
                            cout << "User made more than 3 mistakes in a row. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }
                    }

                    //rate
                    mistakes_count = 0;
                    valid = false;
                    while (!valid) {
                        cout << "What attack rate does this knight have? [10, 50] ";
                        getline(input, line);

                        try {
                            knight_rate = std::stoi(line, nullptr);

                            if (knight_rate > 50 || knight_rate < 10) {
                                cout << "Please enter a number between 10 and 50" << endl;
                                mistakes_count++;
                            } else {
                                valid = true;
                                log.writeLogRecord("rate:" + std::to_string(knight_rate));
                            }
                        } catch (...) {
                            cout << "Please enter a number between 10 and 50" << endl;
                        }

                        if (mistakes_count > 3) {
                            log.writeLogRecord("User made more than 3 mistakes in a row. Program Exiting...");
                            log.close();
                            cout << "User made more than 3 mistakes in a row. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }
                    }

                    //damage
                    mistakes_count = 0;
                    valid = false;
                    while (!valid) {
                        cout << "What attack damage does this knight have? [1, 9] ";
                        getline(input, line);

                        try {
                            knight_damage = std::stoi(line, nullptr);

                            if (knight_damage > 9 || knight_damage < 1) {
                                cout << "Please enter a number between 1 and 9" << endl;
                                mistakes_count++;
                            } else {
                                valid = true;
                                log.writeLogRecord("damage:" + std::to_string(knight_damage));
                            }
                        } catch (...) {
                            cout << "Please enter a number between 1 and 9" << endl;
                        }

                        if (mistakes_count > 3) {
                            log.writeLogRecord("User made more than 3 mistakes in a row. Program Exiting...");
                            log.close();
                            cout << "User made more than 3 mistakes in a row. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }
                    }

                    knights[i] = Knight(knight_name, knight_hp, knight_bravery, knight_rate, knight_damage);
                    log.writeLogRecord("Knight successfully initialized");
                }
            }
        } else { // Get from file
            if (knight_file.is_open())
            {
                log.writeLogRecord("Knight setup file opened successfully");

                // Count
                if (getline(knight_file, line) && line.compare(0, 6, "count:") == 0) {
                    try {
                        knight_count = std::stoi(line.substr(6, line.length() - 6), nullptr);
                    } catch (...) {
                        log.writeLogRecord("Exception occurred parsing knight count. Program Exiting...");
                        log.close();
                        cout << "Exception occurred parsing knight count. Program Exiting..." << endl;
                        return EXIT_FAILURE;
                    }

                    log.writeLogRecord("count" + std::to_string(knight_count));
                } else {
                    log.writeLogRecord("Knight count line not found or out of order");
                    log.close();
                    cout << "Knight count line not found or out of order" << endl;
                    return EXIT_FAILURE;
                }

                Knight temp[knight_count]; // create temporary array
                knights = temp; // move it to knights object


                if (getline(knight_file, line) && line.length() > 1)
                {
                    log.writeLogRecord("Missing blank line in knight file. Program Exiting...");
                    log.close();
                    cout << "Missing blank line in knight file. Program Exiting..." << endl;
                    return EXIT_FAILURE;
                }

                for (int i = 0; i < knight_count; i++)
                {
                    // name
                    if (getline(knight_file, line) && line.compare(0, 5, "name:") == 0) {
                        if (line.length() > 56 || line.length() < 8) {
                            log.writeLogRecord("Knight name not between 2 and 50 characters in length. Program Exiting...");
                            log.close();
                            cout << "Knight name not between 2 and 50 characters in length. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }

                        knight_name = std::move(line);

                        log.writeLogRecord("name:" + knight_name);
                    } else {
                        log.writeLogRecord("Knight name line not found or out of order");
                        log.close();
                        cout << "Knight name line not found or out of order" << endl;
                        return EXIT_FAILURE;
                    }

                    // hp
                    if (getline(knight_file, line) && line.compare(0, 3, "hp:") == 0) {
                        try {
                            knight_hp = std::stoi(line.substr(3, line.length() - 3), nullptr);
                        } catch (...) {
                            log.writeLogRecord("Exception occurred parsing knight hp. Program Exiting...");
                            log.close();
                            cout << "Exception occurred parsing knight hp. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }

                        if (knight_hp > 50 || knight_hp < 25) {
                            log.writeLogRecord("Knight hp out of bounds. Program Exiting...");
                            log.close();
                            cout << "Knight hp out of bounds. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }

                        log.writeLogRecord("hp:" + std::to_string(knight_hp));
                    } else {
                        log.writeLogRecord("Knight hp line not found or out of order");
                        log.close();
                        cout << "Knight hp line not found or out of order" << endl;
                        return EXIT_FAILURE;
                    }

                    // bravery
                    if (getline(knight_file, line) && line.compare(0, 8, "bravery:") == 0) {
                        try {
                            knight_bravery = std::stoi(line.substr(8, line.length() - 8), nullptr);
                        } catch (...) {
                            log.writeLogRecord("Exception occurred parsing knight bravery. Program Exiting...");
                            log.close();
                            cout << "Exception occurred parsing knight bravery. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }

                        if (knight_bravery > knight_hp) {
                            log.writeLogRecord("Knight bravery out of bounds. Program Exiting...");
                            log.close();
                            cout << "Knight bravery out of bounds. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }

                        log.writeLogRecord("bravery:" + std::to_string(knight_hp));
                    } else {
                        log.writeLogRecord("Knight bravery line not found or out of order");
                        log.close();
                        cout << "Knight bravery line not found or out of order" << endl;
                        return EXIT_FAILURE;
                    }

                    // rate
                    if (getline(knight_file, line) && line.compare(0, 5, "rate:") == 0) {
                        try {
                            knight_rate = std::stoi(line.substr(5, line.length() - 5), nullptr);
                        } catch (...) {
                            log.writeLogRecord("Exception occurred parsing knight rate. Program Exiting...");
                            log.close();
                            cout << "Exception occurred parsing knight rate. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }

                        if (knight_rate > 50 || knight_rate < 10) {
                            log.writeLogRecord("Knight rate out of bounds. Program Exiting...");
                            log.close();
                            cout << "Knight rate out of bounds. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }

                        log.writeLogRecord("rate:" + std::to_string(knight_rate));
                    } else {
                        log.writeLogRecord("Knight rate line not found or out of order");
                        log.close();
                        cout << "Knight rate line not found or out of order" << endl;
                        return EXIT_FAILURE;
                    }

                    // damage
                    if (getline(knight_file, line) && line.compare(0, 7, "damage:") == 0) {
                        try {
                            knight_damage = std::stoi(line.substr(7, line.length() - 7), nullptr);
                        } catch (...) {
                            log.writeLogRecord("Exception occurred parsing knight damage. Program Exiting...");
                            log.close();
                            cout << "Exception occurred parsing knight damage. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }

                        if (knight_damage > 9 || knight_damage < 1) {
                            log.writeLogRecord("Knight damage out of bounds. Program Exiting...");
                            log.close();
                            cout << "Knight damage out of bounds. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }

                        log.writeLogRecord("damage:" + std::to_string(knight_damage));
                    } else {
                        log.writeLogRecord("Knight damage line not found or out of order");
                        log.close();
                        cout << "Knight damage line not found or out of order" << endl;
                        return EXIT_FAILURE;
                    }

                    knights[i] = Knight(knight_name, knight_hp, knight_bravery, knight_rate, knight_damage);
                    log.writeLogRecord("Knight successfully initialized");

                    if (i < knight_count - 1)
                    {
                        if (getline(knight_file, line) && line.length() > 1)
                        {
                            log.writeLogRecord("Missing blank line in knight file. Program Exiting...");
                            log.close();
                            cout << "Missing blank line in knight file. Program Exiting..." << endl;
                            return EXIT_FAILURE;
                        }
                    }
                }
            } else {
                log.writeLogRecord("Unable to open Knight Setup File. Program Exiting...");
                log.close();
                cout << "Unable to open Knight Setup File. Program Exiting..." << endl;
                return EXIT_FAILURE;
            }
        }
    }

    log.close();
    return EXIT_SUCCESS;
}