#ifndef __WAPOTION__
#define __WAPOTION__

#include "potion.h"
#include "point.h"
#include <string>

class WAPotion : public Potion {
  public:
    WAPotion(Game *game, Point coordinate);
    ~WAPotion();

    static std::string symbol;
    void getIngestedBy(PlayerCharacter *character) override;
    std::string messageString() override;
    void discover() override;

    static bool isDiscovered;
};

#endif

