#include "dragonHorde.h"
#include "pickupAction.h"
#include "treasure.h"
#include "character.h"
#include "floor.h"
#include "direction.h"
#include "log.h"
#include "playerCharacter.h"
#include "potion.h"
#include <string>
using namespace std;

PickupAction::PickupAction(Direction d, PlayerCharacter *character, Floor *floor): direction{d}, character{character}, floor{floor} {
    
}

PickupAction::~PickupAction() {

}

void PickupAction::act() {
  LOG("called act");

  Point targetPoint = Point(character->getCoordinates(), direction);
  Tile *destination = floor->getTile(targetPoint);
 
  potion = dynamic_cast<Potion *>(destination->occupant);

  if (potion) {
    destination->occupant = nullptr;
    potion->getIngestedBy(character);
    potion->discover();
    setMessage();
    delete potion;
    return;
  }

}

void PickupAction::setMessage() {
  ostringstream oss;
  oss << character->messageString();
  if (potion) {
    oss << " uses " << potion->messageString() << "."; 
  }
  message = oss.str();
}

bool PickupAction::involvesPlayerCharacter() {
  // could conceivably extend pickup actions to enemies as well, so we keep this function ready.
  return dynamic_cast<PlayerCharacter*>(character);
}
