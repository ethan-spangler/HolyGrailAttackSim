//
// Created by Ethan on 9/11/2019.
//

#include "Castle.h"

// Start Constructors
Castle::Castle() {}
Castle::Castle(int hitPoints, int attackRate, int attackChanceTaunt, int attackChanceCow, int attackChanceRabbit,
               int damageWeak, int damageStrong) : hit_points(hitPoints), attack_rate(attackRate),
                                                   attack_chance_taunt(attackChanceTaunt),
                                                   attack_chance_cow(attackChanceCow),
                                                   attack_chance_rabbit(attackChanceRabbit), damage_weak(damageWeak),
                                                   damage_strong(damageStrong) {}
// End Constructors

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


// End Getters and Setters
