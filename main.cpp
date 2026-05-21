#include<iostream>
#include "Characters.h"
#include<string>
#include<conio.h>
#include<chrono>

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
            hero = new Mage("Mage", 200, 5, 20, 10, {1});
            std::cout << "the Mage has the bigest hp, the harest attack,\n" <<
                "but she's slow and her defence is mid.\n" <<
                "Her specila attack is to double her attack!!";
            break;
        }
        case 2 :{
            hero = new Spartan("Spartan", 150, 3, 15, 15, {1});
            std::cout << "The Spartan has mid hp and attack, but he has the heviest sheiled\n" <<
                "and of cours that slow him down!\n" <<
                "His special attack is to tackel the villan and stun him for 5sec!!";
            break;
        }
        case 3 :{
            hero = new Assassin("Assassin", 150, 10, 15, 5, {1});
            std::cout << "The Assassin the quick one, allthought he has a mid hp and a light sheild,\n" <<
                "but his speed give him the ability to dodge and attack multiple time.\n" <<
                "his spicial attack is to attack 4 time in row with half the power!\n";
            break;
        }
    };

    Villan v("Monster", 400, 5, 30, 10);
    std::cout << "\n";

    std::cout << "a: Attack\n"
                "d: dodge\n";

    bool att_cooldown = true;
    bool villan_att = false;
    bool dodged = false;
    bool warning = false;
    auto lastAtt = std::chrono::steady_clock::now();
    auto lastVillAtt = std::chrono::steady_clock::now();
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

            
        }

        if(villan_att){
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
    }

    return 0;
}