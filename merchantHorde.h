#ifndef __MERCHANTHORDE__
#define __MERCHANTHORDE__

#include "treasure.h"
#include "point.h"
#include <string>

class MerchantHorde : public Treasure {
  public:
    MerchantHorde(Game *game, Point coordinate);

    static std::string symbol;
    std::string messageString() override;
};

#endif

