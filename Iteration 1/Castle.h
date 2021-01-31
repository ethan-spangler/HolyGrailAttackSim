//
// Created by Ethan on 9/11/2019.
//

#ifndef LOGGING_CASTLE_H
#define LOGGING_CASTLE_H

class Castle {

private:
    int hit_points;
    int attack_rate;
    int attack_chance_taunt;
    int attack_chance_cow;
    int attack_chance_rabbit;
    int damage_weak;
    int damage_strong;

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
};
#endif //LOGGING_CASTLE_H