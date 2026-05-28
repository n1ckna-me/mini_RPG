#include<iostream>
#include<chrono>
#include "Characters.h"

int random_nbr(int min, int max);
int input_check();

Character::Character(std::string name, int hp, int speed, int att, int def, int maxHp){
    this -> name = name;
    this -> hp = hp;
    this -> speed = speed;
    this -> att = att;
    this -> def = def;
    this -> maxHp = maxHp;
}

std::string Character::get_name() const{return name;}
int Character::get_hp() const{return hp;}
int Character::get_speed() const{return speed;}
int Character::get_att() const{return att;}
int Character::get_def() const{return def;}
int Character::get_maxHp() const{return maxHp;}

void Character::set_name(std::string name){this -> name = name;}
void Character::set_speed(int speed){this -> speed = speed;}
void Character::set_hp(int hp){this -> hp = hp;}
void Character::set_att(int att){this -> att = att;}
void Character::set_def(int def){this -> def = def;}
void Character::set_maxHp(int maxHp){this->maxHp = maxHp;}

void Hero::set_abiVal(int abiVal){this->abiVal = abiVal;}
void Hero::set_abiCooldown(int abiCooldown){this->abiCooldown = abiCooldown;}

int Hero::get_abiVal() const{return abiVal;}
int Hero::get_abiCooldown() const{return abiCooldown;}

void Villan::set_stunned(bool state){this->stunned = state;}
bool Villan::get_stunned() const{return stunned;}

bool Character::is_alive() const{
    return hp > 0;
}

void Character::take_damage(int dmg){
        hp -= dmg;
        if(hp < 0) hp = 0;
}

void Villan::take_damage(int dmg){
    int shield_bonus = random_nbr(0, 30);
    int bonus_def = (shield_bonus * get_def()) / 100;

    int total_def = get_def() + bonus_def;

    int final_dmg = dmg - bonus_def;
    if(final_dmg < 0) final_dmg = 0;

    Character::take_damage(final_dmg);
    std::cout << get_name() << " defended with: " << total_def << "\n";
}

void Character::attack(Character& target, int att_dmg){
    int dmg = att_dmg - target.get_def();
    if (dmg < 0) dmg = 0;
    
    target.take_damage(dmg);
}

float Character::att_Cooldown(int baseCooldown) const{
    float cooldown = baseCooldown * (10.0f / get_speed());

    return cooldown;
}

float Hero::att_Cooldown(int baseCooldown) const{
    float cooldown = baseCooldown - (get_speed() * 0.05f);

    return cooldown;
}

void Hero::attack(Character& target, int att_dmg){
    int dmg = add_dmg(att_dmg);

    Character::attack(target, dmg);
    
    std::cout << "u attacked !! with: "<< att_dmg << "\n";
    std::cout  << target.get_name() << " HP: " << target.get_hp() << "\n\n";
}

void Villan::attack(Character& target, int att_dmg){
    std::cout <<"Too slow! You got hit" << "\n";

    Character::attack(target, att_dmg);

    std::cout << get_name() <<" attacked with: "<< get_att() << "\n";
    std::cout << "u defended with: " << target.get_def() << "\n";
    std::cout << "ur HP: " << target.get_hp() << "\n\n";
}

int Hero::add_dmg(int att_dmg){
    int nbr = random_nbr(0, 20);
    int bonus_att = (nbr * att_dmg)/100;

    return bonus_att + att_dmg;
}

float Hero::dodge_warning(int baseWarning) const{
    float warning = baseWarning * (1 + get_speed() * 0.1f);

    return warning;
}

void Hero::use_ability(Villan& target){return;}

void Mage::use_ability(Villan& target){
        std::cout << "u've used the double attack!\n";

        Character::attack(target, get_abiVal());
}

void Spartan::use_ability(Villan& target){
    std::cout << "u've used ur sheiled to tackle " << target.get_name() 
              << "\nnow he's stant for 5sec !\n";

    Character::attack(target, get_abiVal());
    target.set_stunned(true);
}
int hitNbr = 3;
void Assassin::use_ability(Villan& target){
    std::cout << "u've used srowded steps\n";

    int dmg = add_dmg(get_att()/2);

    target.set_hp(target.get_hp() - (dmg*4));

    std::cout << "u've attacked " << hitNbr << " times, with " 
              << hitNbr*dmg << ", u were to fast the villan couldn't deffend!!";
}

void Character::hpBar() const{

    int curHp = (get_hp() * 100)/ get_maxHp();

    std::cout << get_name() <<" "<< get_hp() << " HP [";
    for(int i=0; i<curHp; i++){
        std::cout << "#";
    }
    for(int j=0; j<100 - curHp; j++){
        std::cout << ".";
    }
    std::cout << "]\n";
}

void Hero::show_stats() const{
    std::cout << "Hero stats ("<< get_name() <<") : \n"
              <<"* Attack : " << get_att()
              << "\n* Defense : " << get_def()
              << "\n* Speed : " << get_speed() << "\n";

    Character::hpBar();
}

void Hero::generate_upgrade(){
    std::cout << "after defeating the Boss u've got 2 upgrage for ur ability to choose from : ";
}

void Mage::generate_upgrade(){
    Hero::generate_upgrade();

    int bonusPower = random_nbr(10, 15);

    std::cout << "1: power increase by" << bonusPower <<"%\n"
              << "2: cooldown decrease by 1sec\n";

    int input = input_check();

    switch(input){
        case 1:{
            int power = get_abiVal();
            int addPower = power + ((power*bonusPower)/100);

            set_abiVal(addPower);
            break;
        }
        case 2:{
            set_abiCooldown(get_abiCooldown()-1);
            break;
        }
    }
}

void Spartan::generate_upgrade(){
    Hero::generate_upgrade();

    int bonusPower = random_nbr(5, 10);

    std::cout << "1: stun time increase by 1sec\n"
              << "2: tackl power increase by " << bonusPower <<"%\n";

    int input = input_check();

    switch(input){
        case 1:{
            set_abiCooldown(get_abiCooldown()+1);
            break;
        }
        case 2:{
            int power = get_abiVal();
            int addPower = power + ((power*bonusPower)/100);

            set_abiVal(addPower);
            break;
        }
    }
}

void Assassin::generate_upgrade(){
    Hero::generate_upgrade();

    std::cout << "1: hits increase by one\n"
              << "2: cooldown decrease by 1sec\n";

    int input = input_check();

    switch(input){
        case 1:{
            hitNbr++;
            break;
        }
        case 2:{
            set_abiCooldown(get_abiCooldown()-1);
            break;
        }
    }
}