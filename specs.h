#ifndef __SPECS__
#define __SPECS__

#include <string>

class Potion;

class Specs {
  protected:
    int atk;
    int def;
    int hp;
    int maxHp;
    int atkBoost;
    int defBoost;
    double gold;
    std::string raceName;

  public:
    Specs(int atk, int def, int hp, std::string raceName);
    virtual ~Specs();

    int getAtk();
    int getDef();
    int getHp();
    virtual void setAttackBoost(int boost);
    virtual void setDefenceBoost(int boost);
    double getGold();
    void setHp(int newHp);
    virtual void setHpThroughPotion(int newHp);

    virtual double calculateScore();

    void reset();

    virtual void addGold(int amount);

    std::string getRaceName();
};

class HumanSpecs : public Specs {
  public:
    HumanSpecs();

    double calculateScore() override;
};

class OrcSpecs : public Specs {
  public:
    OrcSpecs();

    void addGold(int amount) override;
};

class ElfSpecs : public Specs {
  public:
    ElfSpecs();

    void setDefenceBoost(int boost) override;
    void setAttackBoost(int boost) override;    
    void setHpThroughPotion(int newHp) override;
};

class DwarfSpecs : public Specs {
  public:
    DwarfSpecs();

    void addGold(int amount) override;
};

#endif
