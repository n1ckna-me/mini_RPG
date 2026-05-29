#include<iostream>
#include<conio.h>
#include<chrono>
#include "bonus.h"
#include "stage.h"
#include "tools.h"

void Stage::set_time(int time){this->time = time;}
void Stage::set_completed(bool completed){this->completed = completed;}
bool Stage::get_completed() const{return completed;}
Floor Stage::get_floor() const{return floor;}
int Stage::get_time() const{return time;}

void Stage::addEnemy(Villan *enemy){enemies.push_back(enemy);}

void Stage::bonus_sys(Hero *hero){
    Bonus heal(BonusType::heal, random_nbr(40, 80));
    Bonus att(BonusType::att, random_nbr(5, 15));
    Bonus def(BonusType::def, random_nbr(5, 20));
    Bonus speed(BonusType::speed, random_nbr(5,10));

    std::cout << "u've killed the monster, and now u have 4 bonuses to choose from :\n"
              << "1: healing " << heal.get_value() << "%\n"
              << "2: attack increase " << att.get_value() << "%\n"
              << "3: defense increase " << def.get_value() << "%\n"
              << "4: speed increase " << speed.get_value() << "%\n";
    
    int input = input_check(4);

    switch(input){
        case 1:
            heal.apply(*hero);
            break;
        case 2:
            att.apply(*hero);
            break;
        case 3:
            def.apply(*hero);
            break;
        case 4:
            speed.apply(*hero);
            break;
    }

    hero->show_stats();
}

void Stage::fight(Hero *hero, Villan *v){
    std::cout << "start the fight!\n";

    bool att_cooldown = true;
    bool villan_att = false;
    bool dodged = false;
    bool warning = false;
    bool abi_cooldown = true;
    bool render = true;
    bool showen = false;
    auto lastAtt = std::chrono::steady_clock::now();
    auto lastVillAtt = std::chrono::steady_clock::now();
    auto lastAbi = std::chrono::steady_clock::now();
    auto lastRender = std::chrono::steady_clock::now();
    auto lastStats = std::chrono::steady_clock::now();

    while(v->is_alive() && hero->is_alive()){

        if(!att_cooldown){
            if(timer(hero->att_Cooldown(2), lastAtt)){
                att_cooldown = true;
            }
        }
        if(!villan_att){
            float time = hero->dodge_warning(v->att_Cooldown(4)-0.5);
            if(timer(time, lastVillAtt) && !warning){
                std::cout << "dodge!!\n";
                warning = true;
            }
            if (timer(v->att_Cooldown(4), lastVillAtt)){
                villan_att = true;
            }
        }
        if(!abi_cooldown){
            if(timer(hero->get_abiCooldown(), lastAbi) && !v->get_stunned()){
                abi_cooldown = true;
            }
        }
        if(v->get_stunned()){
            if(timer(hero->get_abiCooldown(), lastAbi)){
                v->set_stunned(false);
            }
        }
        if(!render){
            if(timer(3, lastRender)){
                render = true;
            }
        }
        if(showen){
            if(timer(3, lastStats)){
                showen = false;
            }
        }

        if(_kbhit()){

            char key = _getch();

            if(key == 'a' || key == 'A'){
                if(att_cooldown){
                    lastAtt = std::chrono::steady_clock::now();

                    std::cout << "Attack!\n";
                    hero->attack(*v, hero->get_att());

                    
                    att_cooldown = false;
                }else{
                    std::cout << "on cooldown!\n";
                }
            }

            if(key == 'd' || key == 'D'){
                if(warning && !dodged){
                    std::cout << "dodged in time!\n";
                    dodged = true;
                }
            }

            if(key == 'e' || key == 'E'){
                if(abi_cooldown){
                    lastAbi = std::chrono::steady_clock::now();
                    hero->use_ability(*v);
                    
                    abi_cooldown = false;
                }else{
                    std::cout << "on cooldown!\n";
                }
            }
            if(key == 's' || key == 'S'){
                if(!showen){
                    lastStats = std::chrono::steady_clock::now();

                    hero->show_stats();
                    v->show_stats();

                    showen = true;
                }
            }
        }

        if(villan_att && !v->get_stunned()){
            if(!dodged){
                lastVillAtt = std::chrono::steady_clock::now();

                v->attack(*hero, v->get_att());
                villan_att = false;
                warning = false;
            }else{
                lastVillAtt = std::chrono::steady_clock::now();

                warning = false;
                villan_att = false;
                dodged = false;
            }
        }

        /*if(render){
            lastRender = std::chrono::steady_clock::now();

            hero->hpBar();
            v.hpBar();
            render = false;
        }*/
    }

    if(hero->is_alive()){
        Stage::bonus_sys(hero);
    }
}

void Stage::startStage(Hero *hero){
    auto start = std::chrono::steady_clock::now();

    std::cout << "the stage started!\n";

    Villan* boss = NULL;

    switch(get_floor()){
        case Floor::floor1:{
            Stage::addEnemy(new Villan("goblin", 100, 6, 15, 5,100));
            Stage::addEnemy(new Villan("orc", 100, 7, 20, 7, 100));
            boss = new Boss1();
            break;
        }
        case Floor::floor2:{
            Stage::addEnemy(new Villan("Manticor", 150, 7, 25, 10,150));
            Stage::addEnemy(new Villan("Lamia", 150, 10, 20, 10, 150));
            boss = new Boss2();
            break;
        }
        case Floor::floor3:{
            Stage::addEnemy(new Villan("Siren", 200, 10, 25, 10,200));
            Stage::addEnemy(new Villan("Werewolf", 200, 10, 30, 15, 200));
            boss = new Boss3();
            break;
        }
    }

    while(!enemies.empty() && hero->is_alive()){
        std::cout << "choose the enemy : \n";
        
        int size = enemies.size();
        
        for(int i=0; i<size; i++){
            std::cout << i+1 << ": " << enemies[i]->get_name() << "\n";
        }

        int choice = input_check(size) - 1;

        Stage::fight(hero, enemies[choice]);

        delete enemies[choice];
        enemies.erase(enemies.begin() + choice);
    }

    if(hero->is_alive()){
        std::cout << "after deafiting the monsters, u'r up thier boss : " << boss->get_name() << "\n";

        Stage::fight(hero, boss);

        delete boss;
        if(hero->is_alive()){
            hero->generate_upgrade();
        }
    }

    auto end = std::chrono::steady_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    set_time(elapsed);

    Stage::set_completed(true);
}