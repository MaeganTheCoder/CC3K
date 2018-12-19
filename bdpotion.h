#ifndef __BDPOTION__
#define __BDPOTION__

#include "potion.h"
#include "point.h"
#include <string>

class BDPotion : public Potion {
  public:
    BDPotion(Game *game, Point coordinate);
    ~BDPotion();

    static std::string symbol;
    void getIngestedBy(PlayerCharacter *character) override;
    std::string messageString() override;
    void discover() override;

    static bool isDiscovered;
};

#endif

