#ifndef __GOBLIN__
#define __GOBLIN__

#include "enemy.h"
#include "point.h"
#include <memory>

class Goblin : public Enemy {
  public:
    Goblin(Game *game, Point coordinates);
    ~Goblin();

    std::string getSymbol() override;

    static std::string symbol;
    std::string messageString() override;
};

#endif
