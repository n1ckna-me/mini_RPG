#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Characters.h"
using namespace std ;

enum class Floor{
    none,
    floor1,
    floor2,
    floor3
};

class Stage {
private:
    Floor floor;
    int time;
    Hero* hero;
    std::vector<Villan*> enemies;
    bool completed;

public:
    Stage()
        : floor(Floor::none), time(0), hero(NULL), completed(false) {}

    Stage(Floor floor, int time, Hero *hero, bool completed)
        : floor(floor), time(time), hero(hero), completed(completed) {}

    void set_completed(bool completed);
    void set_time(int time);
    bool get_completed() const;
    Floor get_floor() const;
    int get_time() const;

    void addEnemy(Villan *enemy);
    void startStage(Hero *hero);
    void fight(Hero* hero, Villan* v);
    void bonus_sys(Hero *hero);
};
        




        
        
