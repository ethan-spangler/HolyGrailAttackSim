//
// Created by Ethan on 9/11/2019.
//


#ifndef LOGGING_KNIGHT_H
#define LOGGING_KNIGHT_H

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include "Helper.h"
#include "Log.h"
#include "PipeManager.h"
#include "AttackMessage.h"

using os_logging::Log;

class Knight {
private:
    std::string name;
    int hit_points;
    int bravery;
    int attack_rate;
    int damage;

    bool alive;
    bool present;
public:
    bool isPresent() const;

    void setPresent(bool present);
    // if false, they dun ran away
public:
    bool isAlive() const;

    void setAlive(bool alive);

private:

    static int knight_count;

public:
    Knight();
    Knight(std::string name, int hitPoints, int bravery, int attackRate, int damage);

    std::string getName() const;
    void setName(const std::string &name);
    [[nodiscard]] int getHitPoints() const;
    void setHitPoints(int hitPoints);
    [[nodiscard]] int getBravery() const;
    void setBravery(int bravery);
    [[nodiscard]] int getAttackRate() const;
    void setAttackRate(int attackRate);
    [[nodiscard]] int getDamage() const;
    void setDamage(int damage);

    static void checkMistakeCount(int mistakeCount);

    static Knight* CreateKnightsFromFile();
    static Knight* CreateKnightsRandomly();
    static Knight* CreateKnightsFromUserInput();

    static int GetKnightCount();

    static int GetUserIntegerInputInRange(string fieldName, string prompt, int lowerLimit, int upperLimit);
    static int GetFileIntegerInputInRange(std::ifstream& knightFile, string fieldName, string logName, int lowerLimit, int upperLimit);

    static void KnightAttackerProcessor(Knight knight, int knight_number);
    static void KnightBookkeeperProcessor(Knight knight, int knight_number, int pid_knight_attacker);
};
#endif //LOGGING_KNIGHT_H