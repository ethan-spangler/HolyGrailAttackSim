//
// Created by Ethan on 9/11/2019.
//


#ifndef LOGGING_KNIGHT_H
#define LOGGING_KNIGHT_H

#include <iostream>
#include <string>
#include <utility>
#include "Helper.h"

class Knight {
private:
    std::string name;
    int hit_points;
    int bravery;
    int attack_rate;
    int damage;

    static std::string names_for_randomizer[];

public:
    Knight();
    Knight(std::string name, int hitPoints, int bravery, int attackRate, int damage);

    const std::string &getName() const;
    void setName(const std::string &name);
    [[nodiscard]] int getHitPoints() const;
    void setHitPoints(int hitPoints);
    [[nodiscard]] int getBravery() const;
    void setBravery(int bravery);
    [[nodiscard]] int getAttackRate() const;
    void setAttackRate(int attackRate);
    [[nodiscard]] int getDamage() const;
    void setDamage(int damage);
};
#endif //LOGGING_KNIGHT_H