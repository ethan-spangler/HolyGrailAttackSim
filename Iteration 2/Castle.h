//
// Created by Ethan on 9/11/2019.
//

#ifndef LOGGING_CASTLE_H
#define LOGGING_CASTLE_H

#include "Log.h"
#include "Helper.h"
#include "PipeManager.h"
#include "AttackMessage.h"
#include "Knight.h"
#include <signal.h>

using os_logging::Log;
using std::ifstream;

class Castle {

private:
    int hit_points;
    int attack_rate;
    int attack_chance_taunt;
    int attack_chance_cow;
    int attack_chance_rabbit;
    int damage_weak;
    int damage_strong;

    static bool* valid_targets;
    static int valid_target_count;

public:
    Castle();
    Castle(int hitPoints, int attackRate, int attackChanceTaunt, int attackChanceCow, int attackChanceRabbit,
           int damageWeak, int damageStrong);

    [[nodiscard]] int getHitPoints() const;
    void setHitPoints(int hitPoints);
    [[nodiscard]] int getAttackRate() const;
    void setAttackRate(int attackRate);
    [[nodiscard]] int getAttackChanceTaunt() const;
    void setAttackChanceTaunt(int attackChanceTaunt);
    [[nodiscard]] int getAttackChanceCow() const;
    void setAttackChanceCow(int attackChanceCow);
    [[nodiscard]] int getAttackChanceRabbit() const;
    void setAttackChanceRabbit(int attackChanceRabbit);
    [[nodiscard]] int getDamageWeak() const;
    void setDamageWeak(int damageWeak);
    [[nodiscard]] int getDamageStrong() const;
    void setDamageStrong(int damageStrong);

    static int getValid_target_count();
    static void setValid_target_count(int valid_target_count);

    static void validateTarget(int target);
    static void invalidateTarget(int target);
    static bool isTargetValid(int target);
    static int selectRandomValidKnight();

    static Castle CreateCastleFromFile();
    static int GetFileIntegerInputInRange(std::ifstream& castleFile, string fieldName, string logName, int lowerLimit, int upperLimit);

    static void CastleAttackerProcessor(Castle castle);
    static void CastleBookkeeperProcessor(Castle castle, int pid_castle_attacker);

    static void sigusr1_handler(int sig, siginfo_t *si, void *ucontext);
};
#endif //LOGGING_CASTLE_H