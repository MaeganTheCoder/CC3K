#ifndef __DRAGONHORDE__
#define __DRAGONHORDE__

#include "treasure.h"
#include "point.h"
#include "dragon.h"
#include <string>

class DragonHorde : public Treasure {
    Dragon *guardDragon;
  public:
    DragonHorde(Game *game, Point coordinate, Dragon *dragon);
    DragonHorde(Game *game, Point coordinate);
    bool playerNextToHorde();
    static std::string symbol;
    std::string messageString() override;
    Dragon * getGuardDragon();
    void setGuardDragon(Dragon* d);
};

#endif

