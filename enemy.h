#ifndef __ENEMY__
#define __ENEMY__

#include "character.h"
#include "point.h"
#include "direction.h"
#include <memory>

class Action;

class Enemy : public Character {
  protected:
    Direction getRandomDirection();
  public:
    Enemy(Game *game, Point coordinates);
    ~Enemy();

    Action *createAction() override;
    int getHitProbability() override;
};

#endif
