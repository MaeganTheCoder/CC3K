#ifndef __PLAYERCHARACTER__
#define __PLAYERCHARACTER__

#include "character.h"
#include "point.h"
#include <memory>
#include <string>

class Action;

class PlayerCharacter : public Character {
    bool firstCommand;
    Direction getDirection(std::string s);
    Action *createAttackAction(std::string s);
  public:
    PlayerCharacter(Game *game, Point coordinates);
    
    std::string getRaceName();

    static std::string symbol;
    double calculateScore();

    std::string getSymbol() override;
    int getHitProbability() override;
    void addGold(int amount);
    void resetStats();
    void setHpThroughPotion(int newHp);

    Action *createAction() override;
    std::string messageString() override;
};

#endif
