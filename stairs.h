#ifndef __STAIRS__
#define __STAIRS__

#include "point.h"
#include "occupant.h"
#include <string>

class Stairs : public Occupant {
  public:
    Stairs(Game *game, Point coordinates);
    ~Stairs();
    std::string getSymbol() override;
    
    static std::string symbol;
    std::string messageString() override;
};

#endif
