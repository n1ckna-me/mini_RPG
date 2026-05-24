#include <string>
#include <vector>

class Villan;

class Character{
    private:
        std::string name;
        int hp;
        int speed;
        int att;
        int def;
    public:
        Character()
            : name("") ,hp(0), speed(0), att(0), def(0) {}
        Character(std::string name, int hp, int speed, int att, int def);

        void set_name(std::string name);
        void set_speed(int speed);
        void set_hp(int hp);
        void set_att(int att);
        void set_def(int def);

        std::string get_name() const;
        int get_speed() const;
        int get_hp() const;
        int get_att() const;
        int get_def() const;

        bool is_alive() const;
        virtual void take_damage(int dmg);
        virtual void attack(Character& target, int att_dmg);
        void hpBar(int hp) const;
};

class Hero : public Character{
    private:
        std::vector<int> abilities; 
    public:
        Hero(std::string name, int hp, int speed, int att, int def, std::vector <int> abilities)
            : Character(name, hp, speed, att, def),
            abilities(abilities) {}

        void set_abilitie(std::vector<int> abilities);
        std::vector<int> get_abilities() const;

        int add_dmg();
        void attack(Character& target, int att_dmg) override;
        bool hero_dodged();
        virtual void use_ability(Villan& target, int ability);
};

class Mage : public Hero{
    public:
        Mage(std::string name, int hp, int speed, int att, int def, std::vector <int> abilities)
            : Hero(name, hp, speed, att, def, abilities) {}
        void use_ability(Villan& target, int ability) override;
};
class Spartan : public Hero{
    public:
        Spartan(std::string name, int hp, int speed, int att, int def, std::vector <int> abilities)
            : Hero(name, hp, speed, att, def, abilities) {}
        void use_ability(Villan& target, int ability) override;
};
class Assassin : public Hero{
    public:
        Assassin(std::string name, int hp, int speed, int att, int def, std::vector <int> abilities)
            : Hero(name, hp, speed, att, def, abilities) {}
        void use_ability(Villan& target, int ability) override;
};

class Villan : public Character{
    private:
        bool stunned;
    public:
        Villan(std::string name, int hp, int speed, int att, int def)
            : Character(name, hp, speed, att, def), stunned(false) {}

        bool get_stunned() const;
        void set_stunned(bool state);
        
        void take_damage(int dmg) override;
        void attack(Character& target, int att_dmg) override;
};

class Boss : public Villan{
    public:
        Boss(std::string name, int hp, int speed, int att, int def)
            : Villan(name, hp, speed, att, def) {}

};