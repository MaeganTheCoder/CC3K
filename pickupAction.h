#ifndef PICKUPACTION_H_
#define PICKUPACTION_H_

#include "action.h"
#include "playerCharacter.h"
#include "direction.h"
#include <string>

class Treasure;
class Floor;

class PickupAction: public Action {
    Direction direction;
    PlayerCharacter *character;
    Floor *floor;
    Potion *potion;
    Treasure *treasure;

    void setMessage();
  public:
    PickupAction(Direction d, PlayerCharacter *character, Floor* floor);
    ~PickupAction();
    void act() override;
    bool involvesPlayerCharacter() override;
};

#endif
