//
// Created by Ethan on 12/1/2019.
//

#ifndef HW6_KNIGHT_H
#define HW6_KNIGHT_H

#include <iostream>
#include <fstream>
#include <string>
#include <signal.h>
#include <pthread.h>

#include "ThreadManager.h"
#include "AttackMessage.h"

using std::endl;
using std::cout;
using std::string;
using std::fstream;
using std::ofstream;
using std::ifstream;

class Knight
{
private:

    // Knight Stats
    string name;
    int hit_points;
    int bravery;
    int attack_rate;
    int damage;
    int knight_number;

    // Is this knight alive, and have they run away yet?
    bool alive;
    bool present;

    static int knight_count;
    static string knight_setup_file_name;
public:
    // Constructors
    Knight();
    Knight(int number, const string &name, int hit_points, int bravery, int attack_rate, int damage);
    Knight(Knight* knight);

    // Knight Creation
    static Knight* CreateKnightsFromFile();

    // Getters/Setters
    const string &getName() const;
    void setName(const string &name);
    int getHit_points() const;
    void setHit_points(int hit_points);
    int getBravery() const;
    void setBravery(int bravery);
    int getAttack_rate() const;
    void setAttack_rate(int attack_rate);
    int getDamage() const;
    void setDamage(int damage);
    bool isAlive() const;
    void setAlive(bool alive);
    bool isPresent() const;
    void setPresent(bool present);
    int getKnight_Number() const;
    static const string &getKnight_setup_file_name();
    static void setKnight_setup_file_name(const string &knight_setup_file_name);
    static int getKnight_count();
    static void setKnight_count(int knight_count);

    // Helpers
    static int GetFileIntegerInputInRange(std::ifstream& knightFile, string fieldName, string logName, int lowerLimit, int upperLimit);

    // Knight functions for threaded process
    static void *KnightAttackerProcess(void *args);
    static void *KnightBookkeeperProcess(void *args);
};


#endif //HW6_KNIGHT_H
