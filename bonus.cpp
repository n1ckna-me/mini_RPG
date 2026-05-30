#include<iostream>
#include<vector>
#include "bonus.h"
#include "characters.h"
#include "tools.h"

void Bonus::set_value(int val){this->value = val;}

int Bonus::get_value() const{return value;}
BonusType Bonus::get_type() const{return type;}

void Bonus::apply(Hero &hero){
    switch(get_type()){

        case BonusType::heal:{
            int addHp;
            int hp = hero.get_hp();
            
            int healAmount = (hero.get_maxHp() * get_value()) / 100;
            addHp = healAmount + hp;

            if(addHp > hero.get_maxHp()){
                addHp = hero.get_maxHp();
            }

            hero.set_hp(addHp);
            break;
        }
        case BonusType::att:{
            int att = hero.get_att();
            int addAtt = att + ((att*get_value())/100);

            hero.set_att(addAtt);
            break;
        }
        case BonusType::def:{
            int def = hero.get_def();
            int addDef = def + (std::max(1, (def * get_value())/ 100));

            hero.set_def(addDef);
            break;
        }
        case BonusType::speed:{
            int speed = hero.get_speed();
            int addSpeed = speed + (std::max(1, (speed * get_value())/ 100));

            hero.set_speed(addSpeed);
            break;
        }
    }
}