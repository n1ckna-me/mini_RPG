#include<iostream>
#include<random>
#include<chrono>
#include "Characters.h"

std::mt19937 gen(std::random_device{}());

int random_nbr(int min, int max){
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

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

void Hero::set_abilitie(std::vector<int> abilities){this -> abilities = abilities;}
std::vector<int> Hero::get_abilities() const{return abilities;}

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
    int shield_bonus = random_nbr(0, 50);
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

void Hero::attack(Character& target, int att_dmg){
    Character::attack(target, att_dmg);
    
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

int Hero::add_dmg(){
    int nbr = random_nbr(0, 20);
    int bonus_att = (nbr * get_att())/100;

    return bonus_att + get_att();
}

bool Hero::hero_dodged(){
    std::string input;

    auto start = std::chrono::steady_clock::now();

    do{
        std::cout <<"u have 3 sec to dodge the villan attack! press D !!";
        std::cin >> input;
    }while(input != "d" && input != "D");

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    return elapsed.count() <= 3;
}

void Hero::use_ability(Villan& target, int ability){
    return;
}

void Mage::use_ability(Villan &target, int ability){
    int nbr_uta = get_abilities().size();
    if(ability > nbr_uta){
        std::cout << "u have no shuch ability like this!!\n";
    }else{
        switch(ability){
            case 1:
                std::cout << "u've used the double attack!\n";
                Character::attack(target, get_att()*2);
                break;
            case 2:
                break;
            case 3:
                break;
        }

    }
}

void Spartan::use_ability(Villan &target, int ability){
    int nbr_uta = get_abilities().size();
    if(ability > nbr_uta){
        std::cout << "u have no shuch ability like this!!\n";
    }else{
        switch(ability){
            case 1:
                std::cout << "u've used ur sheiled to tackle " << target.get_name() << 
                "\nnow he's stant for 5sec !\n";

                target.set_stunned(true);
                break;
            case 2:
                break;
            case 3:
                break;
        }
    }
}

void Assassin::use_ability(Villan &target, int ability){
    int nbr_uta = get_abilities().size();
    if(ability > nbr_uta){
        std::cout << "u have no shuch ability like this!!\n";
    }else{
        switch(ability){
            case 1:
                std::cout << "u've used srowded steps\n";
                for(int i = 0; i<4; i++){
                    Character::attack(target, get_att()/2);
                }
                break;
            case 2:
                break;
            case 3:
                break;
        }

    }
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