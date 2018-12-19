#ifndef __TROLL__
#define __TROLL__

#include "enemy.h"
#include "point.h"
#include <memory>

class Troll : public Enemy {
  public:
    Troll(Game *game, Point coordinates);
    ~Troll();

    std::string getSymbol() override;

    static std::string symbol;
    std::string messageString() override;
};

#endif

