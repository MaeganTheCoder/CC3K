#ifndef __POTION__
#define __POTION__

#include "occupant.h"
#include "point.h"
#include "playerCharacter.h"
#include "log.h"
#include <string>

class Potion : public Occupant {
  public:
    Potion(Game *game, Point coordinate);
    ~Potion() =0;
    std::string getSymbol() override;
    virtual void getIngestedBy(PlayerCharacter *playerCharacter) =0;
    virtual void discover() =0;

    static std::string undiscoveredName;
};

#endif
