#ifndef __BAPOTION__
#define __BAPOTION__

#include "potion.h"
#include "point.h"
#include <string>

class BAPotion : public Potion {
  public:
    BAPotion(Game *game, Point coordinate);
    ~BAPotion();

    static std::string symbol;
    void getIngestedBy(PlayerCharacter *playerCharacter) override;
    std::string messageString() override;
    void discover() override;

    static bool isDiscovered;
};

#endif

