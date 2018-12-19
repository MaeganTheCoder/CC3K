#include "treasure.h"
#include "dragonHorde.h"
#include "moveAction.h"
#include "dragon.h"
#include "character.h"
#include "floor.h"
#include "direction.h"
#include "log.h"
#include "playerCharacter.h"
#include "enemy.h"
#include "stairs.h"
#include "treasure.h"
#include "potion.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

MoveAction::MoveAction(Direction d, Character *character, Floor *floor): direction{d}, character{character}, floor{floor} {
  
}

MoveAction::~MoveAction() {

}

void MoveAction::act() {
  //LOG("called act");
  ostringstream oss;
  
  Tile* currentTile = floor->getTile(character->getCoordinates());
  currentTile->occupant=nullptr;

  Point destinationCoordinates = Point(character->getCoordinates(), direction);
  Tile *destination = floor->getTile(destinationCoordinates);

  Treasure* treasure = dynamic_cast<Treasure *>(destination->occupant);

  // Did we hit floors?
  if (dynamic_cast<PlayerCharacter*>(character) && dynamic_cast<Stairs*>(destination->occupant)) {
    currentTile->occupant = character;
    floor->setHasReachedStairs(true);
    return;
  }
   
  if (treasure) {
    //check if its a dragonhorde, cant pick up unless guarddragon is dead
    if (dynamic_cast<DragonHorde*>(treasure)) {
     DragonHorde* dg = dynamic_cast<DragonHorde*>(treasure);
     if (dg->getGuardDragon()==nullptr) {
       LOG("guard dragon is nullptr");
       destination->occupant = nullptr;
       character->stats->addGold(treasure->getGoldValue());
       delete treasure;
       return;
     } else {
       LOG("guard dragon is not nullptr");
       return;

     }  
    }
    destination->occupant = character;
    character->setCoordinates(destination->getCoordinate());
    oss << character->messageString() << " moves " << getDirectionString() << writeVisibleItems(destination);
    oss << " and picks up " << treasure->getGoldValue() << " Gold.";
    message = oss.str();
    character->stats->addGold(treasure->getGoldValue());
    delete treasure;
    return;
  }

  //LOG("is the destination okay?");
  //if the destination is not okay or the character is a dragon (they don't move)
  if ((dynamic_cast<PlayerCharacter*>(character) && !destination->getIsOccupiableByPlayer()) ||
      (dynamic_cast<Enemy*>(character) && !destination->getIsOccupiableByEnemy()) ||
      destination->occupant != nullptr || dynamic_cast<Dragon*>(character)) {
    //LOG("No!");
    currentTile->occupant = character;
    oss << character->messageString() << " tries to move " << getDirectionString() << " but can't.";
    message = oss.str();
    return;
  }
   
  //LOG("Yes!");
  destination->occupant = character;
  character->setCoordinates(destination->getCoordinate()); 
  oss << character->messageString() << " moves " << getDirectionString() << writeVisibleItems(destination) << ".";
  message = oss.str();
}

string MoveAction::getDirectionString() {
  switch (direction) {
    case Direction::nw:
      return "North-West";
    case Direction::n:
      return "North";
    case Direction::ne:
      return "North-East";
    case Direction::w:
      return "West";
    case Direction::e:
      return "East";
    case Direction::sw:
      return "South-West";
    case Direction::s:
      return "South";
    case Direction::se:
      return "South-East";
    default:
      return "UNKNOWN";
  }
}

string MoveAction::writeVisibleItems(Tile *tile) {
  ostringstream oss;
  vector<Occupant*> neighbours = floor->getNeighbourOccupants(tile);
  neighbours = keepPotionsAndTreasures(neighbours);
  if (neighbours.size() > 0) {
    oss << " and sees " << neighbours[0]->messageString();
    for (uint i = 1; i < neighbours.size(); ++i) {
      oss << " and " << neighbours[i]->messageString();
    }
    return oss.str();
  }
  return "";
}

vector<Occupant*> MoveAction::keepPotionsAndTreasures(vector<Occupant*> occupants) {
  vector<Occupant*> potionsAndTreasures;

  for (uint i = 0; i < occupants.size(); ++i) {
    if (dynamic_cast<Potion*>(occupants[i])) {
      potionsAndTreasures.emplace_back(occupants[i]);
    }
  }

  return potionsAndTreasures;
}

bool MoveAction::involvesPlayerCharacter() {
  return dynamic_cast<PlayerCharacter*>(character);
}
