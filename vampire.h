#ifndef __VAMPIRE__
#define __VAMPIRE__

#include "enemy.h"
#include "point.h"
#include <memory>

class Vampire : public Enemy {
  public:
    Vampire(Game *game, Point coordinates);
    ~Vampire();

    std::string getSymbol() override;

    static std::string symbol;
    std::string messageString() override;
};

#endif
