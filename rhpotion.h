#ifndef __RHPOTION__
#define __RHPOTION__

#include "potion.h"
#include "point.h"
#include <string>

class RHPotion : public Potion {
  public:
    RHPotion(Game *game, Point coordinate);
    ~RHPotion();

    static std::string symbol;
    void getIngestedBy(PlayerCharacter *character) override;
    std::string messageString() override;
    void discover() override;

    static bool isDiscovered;
};

#endif
