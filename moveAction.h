#ifndef __MOVEACTION__
#define __MOVEACTION__

#include "action.h"
#include "character.h"
#include "direction.h"
#include <string>
#include <vector>

class Tile;
class Floor;

class MoveAction : public Action {
    Direction direction;
    Character *character;
    Floor *floor;

    std::string getDirectionString();
    std::string writeVisibleItems(Tile *tile);
    std::vector<Occupant *> keepPotionsAndTreasures(std::vector<Occupant *> occupants);
  public:
    MoveAction(Direction d, Character *character, Floor* floor);
    ~MoveAction();
    void act() override;
    bool involvesPlayerCharacter() override;
};

#endif
