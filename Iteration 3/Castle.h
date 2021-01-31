//
// Created by Ethan on 12/1/2019.
//

#ifndef HW6_CASTLE_H
#define HW6_CASTLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <signal.h>

#include "ThreadManager.h"
#include "AttackMessage.h"
#include "Knight.h"

using std::cout;

using std::endl;
using std::string;
using std::fstream;
using std::ofstream;
using std::ifstream;

class Castle
{

private:
    // Private setup for singleton
    Castle(){}; // Cannot call constructor
    Castle(Castle const&){}; // cannot use copy constructor
    Castle& operator=(Castle const&){}; // cannot use assignment constructor
    static Castle* instance;
    // End private setup for singleton

    // Castle Stats
    int hit_points;
    int attack_rate;
    int attack_chance_taunt;
    int attack_chance_cow;
    int attack_chance_rabbit;
    int damage_weak;
    int damage_strong;

    // Target (knight) Data
    bool* valid_targets;
    int valid_target_count;

    static string castle_setup_file_name;
public:
    // Singleton Instance
    static Castle* Instance();

    // Getters/Setters
    int getHit_points() const;
    void setHit_points(int hit_points);
    int getAttack_rate() const;
    void setAttack_rate(int attack_rate);
    int getAttack_chance_taunt() const;
    void setAttack_chance_taunt(int attack_chance_taunt);
    int getAttack_chance_cow() const;
    void setAttack_chance_cow(int attack_chance_cow);
    int getAttack_chance_rabbit() const;
    void setAttack_chance_rabbit(int attack_chance_rabbit);
    int getDamage_weak() const;
    void setDamage_weak(int damage_weak);
    int getDamage_strong() const;
    void setDamage_strong(int damage_strong);
    bool *getValid_targets() const;
    void setValid_targets(bool *valid_targets);
    int getValid_target_count() const;
    void setValid_target_count(int valid_target_count);
    static const string &getCastle_setup_file_name();
    static void setCastle_setup_file_name(const string &castle_setup_file_name);

    // Castle Creation
    static Castle* CreateCastleFromFile();
    static int GetFileIntegerInputInRange(std::ifstream& castleName, string fieldName, string logName, int lowerLimit, int upperLimit);

    // Knight Target Functions
    void validateTarget(int target);
    void invalidateTarget(int target);
    bool isTargetValid(int target);
    int selectRandomValidKnight();

    // Castle functions for threaded process
    static void* CastleAttackerProcess(void *args);
    static void* CastleBookkeeperProcess(void *args);
    static void CastleSigHandler(int sig, siginfo_t *si, void *ucontext);
};


#endif //HW6_CASTLE_H
