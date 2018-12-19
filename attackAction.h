#ifndef __ATTACKACTION__
#define __ATTACKACTION__

#include "action.h"
#include "character.h"
#include "direction.h"
#include <string>

class Floor;

class AttackAction : public Action {
    Character *attacker;
    Character *defender;
    std::string attackerName;
    std::string defenderName;
    int calculateDamage();
    bool doesAttackHit();
    void setMissMessage();
    void setHitMessage(int damage);
  public:
    AttackAction(Character *attacker, Character *defender);
    ~AttackAction();
    void act() override;
    bool involvesPlayerCharacter() override;
};

#endif

