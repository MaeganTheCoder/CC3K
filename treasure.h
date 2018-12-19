#ifndef __TREASURE__
#define __TREASURE__

#include "occupant.h"
#include "point.h"
#include <string>

class Treasure : public Occupant {
  protected:
    int goldValue;
  public:
    Treasure(Game *game, Point coordinate);
    ~Treasure() =0;
      
    std::string getSymbol() override;
    int getGoldValue();
};

#endif
