#pragma once
#include <string>
#include <vector>

class Villan;

class Character{
    private:
        std::string name;
        int hp;
        int maxHp;
        int speed;
        int att;
        int def;
    public:
        Character()
            : name("") ,hp(0), speed(0), att(0), def(0), maxHp(0) {}
        Character(std::string name, int hp, int speed, int att, int def, int maxHp);

        void set_name(std::string name);
        void set_speed(int speed);
        void set_hp(int hp);
        void set_att(int att);
        void set_def(int def);
        void set_maxHp(int maxHp);

        std::string get_name() const;
        int get_speed() const;
        int get_hp() const;
        int get_att() const;
        int get_def() const;
        int get_maxHp() const;

        bool is_alive() const;
        virtual void take_damage(int dmg);
        virtual void attack(Character& target, int att_dmg);
        void hpBar() const;
        virtual float att_Cooldown(int baseCooldown) const;
};

class Hero : public Character{
    private:
        int abiVal;
        int abiCooldown;
    public:
        Hero(std::string name, int hp, int speed, int att, int def, int maxHp, int abiVal, int abiCooldown)
            : Character(name, hp, speed, att, def, maxHp), abiVal(abiVal), abiCooldown(abiCooldown) {}

        void set_abiVal(int abiVal);
        void set_abiCooldown(int abiCooldown);

        int get_abiVal() const;
        int get_abiCooldown() const;
    
        int add_dmg(int att_dmg);
        void attack(Character& target, int att_dmg) override;
        float att_Cooldown(int baseCooldown) const override;
        virtual void use_ability(Villan& target);
        virtual void generate_upgrade();
        void show_stats() const;
        float dodge_warning(int baseWarning) const;
};

class Mage : public Hero{
    public:
        Mage(std::string name, int hp, int speed, int att, int def, int maxHp, int abi_val, int abiCooldown)
            : Hero(name, hp, speed, att, def, maxHp, abi_val, abiCooldown) {}

        void use_ability(Villan& target) override;
        void generate_upgrade() override;
};
class Spartan : public Hero{
    public:
        Spartan(std::string name, int hp, int speed, int att, int def, int maxHp, int abi_val, int abiCooldown)
            : Hero(name, hp, speed, att, def, maxHp, abi_val, abiCooldown) {}

        void use_ability(Villan& target) override;
        void generate_upgrade() override;
};
class Assassin : public Hero{
    public:
        Assassin(std::string name, int hp, int speed, int att, int def, int maxHp, int abi_val, int abiCooldown)
            : Hero(name, hp, speed, att, def, maxHp, abi_val, abiCooldown) {}

        void use_ability(Villan& target) override;
        void generate_upgrade() override;
};

class Villan : public Character{
    private:
        bool stunned;
    public:
        Villan(std::string name, int hp, int speed, int att, int def, int maxHp)
            : Character(name, hp, speed, att, def, maxHp), stunned(false) {}

        bool get_stunned() const;
        void set_stunned(bool state);
        
        void take_damage(int dmg) override;
        void attack(Character& target, int att_dmg) override;
};

class Boss1 : public Villan{
    public:
        Boss1()
            :  Villan("Velthorax", 300, 10, 25, 10, 300) {}

};

class Boss2 : public Villan{
    public:
        Boss2()
            : Villan("Drakmor", 350, 10, 30, 5, 350) {}

};

class Boss3 : public Villan{
    public:
        Boss3()
            : Villan("King Ragnarok", 400, 15, 40, 15, 400) {}

};