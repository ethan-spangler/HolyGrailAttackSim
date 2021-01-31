//
// Created by Ethan on 9/11/2019.
//

#include <fstream>
#include "Knight.h"


// Start Constructors
Knight::Knight(){
}

Knight::Knight(std::string name, int hitPoints, int bravery, int attackRate, int damage) : name(std::move(name)),
                                                                                                  hit_points(hitPoints),
                                                                                                  bravery(bravery),
                                                                                                  attack_rate(
                                                                                                          attackRate),
                                                                                                  damage(damage) {}

// End Constructors

// Start Getters and Setters
const std::string &Knight::getName() const {
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
// End Getters and Setters


