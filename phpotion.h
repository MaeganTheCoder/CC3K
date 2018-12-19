#ifndef __PHPOTION__
#define __PHPOTION__

#include "potion.h"
#include "point.h"
#include <string>

class PHPotion : public Potion {
  public:
    PHPotion(Game *game, Point coordinate);
    ~PHPotion();

    static std::string symbol;
    void getIngestedBy(PlayerCharacter *character) override;
    std::string messageString() override;
    void discover() override;

    static bool isDiscovered;
};

#endif

