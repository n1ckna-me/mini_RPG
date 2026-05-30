#include<iostream>
#include<string>
#include<chrono>
#include<random>
#include<thread>
#include "stage.h"
#include "tools.h"

int main(){
    std::string input;
    int intInput;
    Hero *hero;

    std::cout << "u r the hero how can save the kingdome!\n" <<
                "choose ur hero (1-Mage, 2-Spartan, 3-Assassin)\n";

    intInput = input_check(3);

    switch(intInput){
        case 1 :{
            hero = new Mage("Mage", 200, 5, 20, 10, 200, 20, 4);
            std::cout << "the Mage has the bigest hp, the harest attack,\n" <<
                "but she's slow and her defence is mid.\n" <<
                "Her specila attack is to double her attack!!";
            break;
        }
        case 2 :{
            hero = new Spartan("Spartan", 200, 3, 15, 15, 200, 5, 4);
            std::cout << "The Spartan has mid hp and attack, but he has the heviest sheiled\n" <<
                "and of cours that slow him down!\n" <<
                "His special attack is to tackel the villan and stun him for 5sec!!";
            break;
        }
        case 3 :{
            hero = new Assassin("Assassin", 200, 10, 15, 5, 200, 15, 4);
            std::cout << "The Assassin the quick one, allthought he has a mid hp and a light sheild,\n" <<
                "but his speed give him the ability to dodge and attack multiple time.\n" <<
                "his spicial attack is to attack 4 time in row with half the power!\n";
            break;
        }
    };
    std::cout << "\n";

    std::cout << "a: Attack\n"
                "d: dodge\n"
                "e: spical attack\n"
                "s: show stats\n";

    std::this_thread::sleep_for(std::chrono::seconds(4));

    Stage* stage1 = NULL;
    Stage* stage2 = NULL;
    Stage* stage3 = NULL;

    stage1 = new Stage(Floor::floor1, 0, hero, false);

    stage1->startStage(hero);

    if(stage1->get_completed()){

        if(hero->is_alive()){
            std::cout << "after finishing first floor in ";

            time_converter(stage1->get_time());

            std::cout <<",\nu moved to the next one.\n"
                      << "now ur up to some new monsters\n";

            stage2 = new Stage(Floor::floor2, 0, hero, false);
        }else{
            std::cout << "YOU DIED!";
            delete stage1;
            delete hero;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return 0;
        }
    }

    delete stage1;
    stage2->startStage(hero);

    if(stage2->get_completed()){

        if(hero->is_alive()){
            std::cout << "after finishing second floor in "; 

            time_converter(stage2->get_time()) ;

            std::cout <<",\nu moved to the next one.\n"
                      << "now ur up to some new monsters\n";

            stage3 = new Stage(Floor::floor3, 0, hero, false);
        }else{
            std::cout << "YOU DIED!";
            delete stage2;
            delete hero;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return 0;
        }
    }

    delete stage2;
    stage3->startStage(hero);

    if(stage3->get_completed()){

        if(hero->is_alive()){
            std::cout << "after finishing third floor in ";

            time_converter(stage3->get_time());

            std::cout <<"\nu managed to get cure of the curse from the King Ragnarok\n"
                      << "now u returned to kingdem with some big news\n"
                      << "gongratse u've finished the game! thanks for playin!\n";
            
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }else{
            std::cout << "YOU DIED!";
            delete stage3;
            delete hero;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return 0;
        }
    }

    delete stage3;
    delete hero;
    return 0;
}