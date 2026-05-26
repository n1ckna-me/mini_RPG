#include<iostream>
#include<string>
#include<conio.h>
#include<chrono>
#include<cstdlib>
#include "Characters.h"
#include "bonus.h"

int random_nbr(int min, int max);

bool timer(int sec, auto& last){
    auto curTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(curTime - last).count();

    if(elapsed >= sec){
        return true;
    }
    return false;
}

int main(){
    std::string input;
    int intInput;
    Hero *hero;

    std::cout << "u r the hero how can save the kingdome!\n" <<
                "choose ur hero (1-Mage, 2-Spartan, 3-Assassin)\n";
    do{
        std::cout << "to chouse type the convinient int to the hero : ";
        std::cin >> intInput;

        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(1000, '\n');

            std::cout << "invalid input!\n";
            intInput = -1;
        }
    }while(intInput < 0 || intInput > 3);

    switch(intInput){
        case 1 :{
            hero = new Mage("Mage", 200, 5, 20, 10, 200, {1});
            std::cout << "the Mage has the bigest hp, the harest attack,\n" <<
                "but she's slow and her defence is mid.\n" <<
                "Her specila attack is to double her attack!!";
            break;
        }
        case 2 :{
            hero = new Spartan("Spartan", 200, 3, 15, 15, 200, {1});
            std::cout << "The Spartan has mid hp and attack, but he has the heviest sheiled\n" <<
                "and of cours that slow him down!\n" <<
                "His special attack is to tackel the villan and stun him for 5sec!!";
            break;
        }
        case 3 :{
            hero = new Assassin("Assassin", 200, 10, 15, 5, 200, {1});
            std::cout << "The Assassin the quick one, allthought he has a mid hp and a light sheild,\n" <<
                "but his speed give him the ability to dodge and attack multiple time.\n" <<
                "his spicial attack is to attack 4 time in row with half the power!\n";
            break;
        }
    };

    Villan v("Monster", 50, 5, 30, 10, 50);
    std::cout << "\n";

    std::cout << "a: Attack\n"
                "d: dodge\n"
                "e: spical attack\n";

    bool att_cooldown = true;
    bool villan_att = false;
    bool dodged = false;
    bool warning = false;
    bool abi_cooldown = true;
    bool render = true;
    auto lastAtt = std::chrono::steady_clock::now();
    auto lastVillAtt = std::chrono::steady_clock::now();
    auto lastAbi = std::chrono::steady_clock::now();
    auto lastRender = std::chrono::steady_clock::now();

    while(v.is_alive() && hero->is_alive()){

        if(!att_cooldown){
            if(timer(1, lastAtt)){
                att_cooldown = true;
            }
        }
        if(!villan_att){
            if(timer(2, lastVillAtt) && !warning){
                std::cout << "dodge!!\n";
                warning = true;
            }
            if (timer(3, lastVillAtt)){
                villan_att = true;
            }
        }
        if(!abi_cooldown){
            if(timer(3, lastAbi) && !v.get_stunned()){
                abi_cooldown = true;
            }
        }
        if(v.get_stunned()){
            if(timer(5, lastAbi)){
                v.set_stunned(false);
            }
        }
        if(!render){
            if(timer(1, lastRender)){
                render = true;
            }
        }

        if(_kbhit()){

            char key = _getch();

            if(key == 'a' || key == 'A'){
                if(att_cooldown){
                    lastAtt = std::chrono::steady_clock::now();

                    std::cout << "Attack!\n";

                    int dmg = hero->add_dmg();
                    hero->attack(v, dmg);

                    
                    att_cooldown = false;
                }else{
                    std::cout << "on cooldown!\n";
                }
            }

            if(key == 'd' || key == 'D'){
                if(warning){
                    std::cout << "dodged in time!\n";
                    dodged = true;
                }else{
                    dodged = false;
                }
            }

            if(key == 'e' || key == 'E'){
                if(abi_cooldown){
                    lastAbi = std::chrono::steady_clock::now();
                    hero->use_ability(v, 1);
                    
                    abi_cooldown = false;
                }else{
                    std::cout << "on cooldown!\n";
                }
            }
        }

        if(villan_att && !v.get_stunned()){
            if(!dodged){
                lastVillAtt = std::chrono::steady_clock::now();

                v.attack(*hero, v.get_att());
                villan_att = false;
                warning = false;
            }else{
                lastVillAtt = std::chrono::steady_clock::now();

                warning = false;
                villan_att = false;
                dodged = false;
            }
        }

        if(render){
            lastRender = std::chrono::steady_clock::now();

            hero->hpBar();
            v.hpBar();
            render = false;
        }
    }

    Bonus heal(BonusType::heal, random_nbr(40, 80));
    Bonus att(BonusType::att, random_nbr(5, 15));
    Bonus def(BonusType::def, random_nbr(5, 20));

    std::cout << "u've killed the monster, and now u have 3 bonuses to choose from :\n"
              << "1: healing " << heal.get_value() << "%\n"
              << "2: attack increase " << att.get_value() << "%\n"
              << "3: defense increase " << def.get_value() << "%\n"
              << "choose the convient nbr :";
    std::cin >> intInput;

    switch(intInput){
        case 1:
            heal.apply(*hero);
            break;
        case 2:
            att.apply(*hero);
            break;
        case 3:
            def.apply(*hero);
            break;
    }

    hero->show_stats();

    return 0;
}