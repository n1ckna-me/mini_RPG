#pragma once
#include<string>
#include "Characters.h"

enum class BonusType{
    heal,
    att,
    def,
    speed
};

class Bonus{
    private: 
        BonusType type;
        int value;
    public:
        Bonus(BonusType type, int val)
            : type(type), value(val) {}

        void set_value(int val);

        BonusType get_type() const;
        int get_value() const;

        void apply(Hero& hero);
};