#ifndef __WEREWOLF__
#define __WEREWOLF__

#include "enemy.h"
#include "point.h"
#include <memory>

class Werewolf : public Enemy {
  public:
    Werewolf(Game *game, Point coordinates);
    ~Werewolf();

    std::string getSymbol() override;

    static std::string symbol;
    std::string messageString() override;
};

#endif
