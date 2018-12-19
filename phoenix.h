#ifndef __PHOENIX__
#define __PHOENIX__

#include "enemy.h"
#include "point.h"
#include <memory>

class Phoenix : public Enemy {
  public:
    Phoenix(Game *game, Point coordinates);
    ~Phoenix();

    std::string getSymbol() override;

    static std::string symbol;
    std::string messageString() override;
};

#endif

