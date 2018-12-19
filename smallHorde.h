#ifndef __SMALLHORDE__
#define __SMALLHORDE__

#include "treasure.h"
#include "point.h"
#include <string>

class SmallHorde : public Treasure {
  public:
    SmallHorde(Game *game, Point coordinate);
    
    static std::string symbol;
    std::string messageString() override;
};

#endif
