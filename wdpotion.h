#ifndef __WDPOTION__
#define __WDPOTION__

#include "potion.h"
#include "point.h"
#include <string>

class WDPotion : public Potion {
  public:
    WDPotion(Game *game, Point coordinate);
    ~WDPotion();

    static std::string symbol;
    void getIngestedBy(PlayerCharacter *character) override;
    std::string messageString() override;
    void discover() override;

    static bool isDiscovered;
};

#endif

