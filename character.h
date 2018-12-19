#ifndef __CHARACTER__
#define __CHARACTER__

#include "occupant.h"
#include "point.h"
#include "specs.h"
#include <memory>
#include <string>

class Action;

class Character : public Occupant {
  protected:

  public:
    Specs *stats;
    Character(Game *game, Point coordinates);
    virtual ~Character() =0;
    virtual Action* createAction() =0;

    virtual int getHitProbability() =0;
    virtual bool applyDamage(int damage);
    bool isDead();

    int getHp();
    int getAtk();
    int getDef();
    double getGold();
    void setHp(int newHp);
    void setAttackBoost(int boost);
    void setDefenceBoost(int boost);
};

#endif
