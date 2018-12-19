#ifndef __MERCHANT__
#define __MERCHANT__

#include "enemy.h"
#include "point.h"
#include <memory>

class Action;

class Merchant : public Enemy {
  public:
    Merchant(Game *game, Point coordinates);
    ~Merchant();

    std::string getSymbol() override;

    static std::string symbol;
    static bool isHostile;

    std::string messageString() override;

    Action *createAction() override;
    bool applyDamage(int damage) override;
};

#endif

