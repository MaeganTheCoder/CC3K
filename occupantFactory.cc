#include "occupantFactory.h"
#include "playerCharacter.h"
#include "enemy.h"
#include "werewolf.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "dragon.h"
#include "phoenix.h"
#include "merchant.h"
#include "potion.h"
#include "rhpotion.h"
#include "bapotion.h"
#include "bdpotion.h"
#include "phpotion.h"
#include "wapotion.h"
#include "wdpotion.h" 
#include "treasure.h"
#include "normalGoldPile.h"
#include "smallHorde.h"
#include "merchantHorde.h"
#include "dragonHorde.h"
#include "tile.h"
#include "room.h"
#include "point.h"
#include "floor.h"
#include "game.h"
#include "log.h"
#include <vector>
using namespace std;

OccupantFactory::OccupantFactory(Game *game, vector<Room *> rooms): game{game}, rooms{rooms} {

}

PlayerCharacter *OccupantFactory::placePlayerCharacter() {
  Room *room = pickPlayerRoom();
  Tile *tile = pickFreeTile(room);
  PlayerCharacter *pc = game->getPlayerCharacter();
  pc->setCoordinates(tile->getCoordinate());
  tile->occupant = pc;
  room->setHasPlayer(true);
  return pc;
}

Enemy *OccupantFactory::placeEnemy() {
  Room *room = pickRandRoom();
  Tile *tile = pickFreeTile(room);
  Enemy *enemy = createEnemy(tile->getCoordinate());
  tile->occupant = enemy;
  return enemy;
}

Stairs *OccupantFactory::placeStairs() {
  Room *room = pickStairsRoom();
  Tile *tile = pickFreeTile(room);
  Stairs *stairs = createStairs(tile->getCoordinate());
  tile->occupant = stairs;
  room->setHasStairs(true);
  return stairs;
}

Potion *OccupantFactory::placePotion() {
  Room *room = pickRandRoom();
  Tile *tile = pickFreeTile(room);
  Potion *potion = createPotion(tile->getCoordinate());
  tile->occupant = potion;
  return potion;
}

Treasure *OccupantFactory::placeTreasure() {
  Room *room = pickRandRoom();
  Tile *tile = pickFreeTile(room);
  Treasure *treasure = createTreasure(tile->getCoordinate(), room);
  tile->occupant = treasure;
  return treasure;
}

Stairs *OccupantFactory::createStairs(Point coordinate) {
  return new Stairs(game, coordinate);
}

Enemy *OccupantFactory::createEnemy(Point coordinate) {
  Enemy *occupant;
  int r = rand() % 18;
  if (r < 4) {
   occupant = new Werewolf(game, coordinate);
  } else if (r < 7) {
   occupant = new Vampire(game, coordinate);
  } else if (r < 12) {
   occupant = new Goblin(game, coordinate);
  } else if (r < 14) {
   occupant = new Troll(game, coordinate);
  } else if (r < 16) {
   occupant = new Phoenix(game, coordinate);
  } else {
   occupant = new Merchant(game, coordinate);
  }

  return occupant;
}

Potion *OccupantFactory::createPotion(Point coordinate) {
  Potion *potion;
  int r = rand() % 6;
  if (r == 0) {
    potion = new RHPotion(game, coordinate);
  } else if (r == 1) {
    potion = new BAPotion(game, coordinate);
  } else if (r == 2) {
    potion = new BDPotion(game, coordinate);
  } else if (r == 3) {
    potion = new PHPotion(game, coordinate);
  } else if (r == 4) {
    potion = new WAPotion(game, coordinate);
  } else {
    potion = new WDPotion(game, coordinate);
  }

  return potion;
}

Treasure *OccupantFactory::createTreasure(Point coordinate, Room *room) {
  Treasure *treasure;
  int r = rand() % 8;
  if (r < 5) {
    treasure = new NormalGoldPile(game, coordinate);
    LOG("NORMAL GOLD : " << coordinate.print());
  } else if (r < 7) {
    treasure = new SmallHorde(game, coordinate);
    LOG("Small Gold : " << coordinate.print());
  } else {
    Dragon *dragon = createNeighbouringDragon(coordinate, room);
    treasure = new DragonHorde(game, coordinate, dragon);
    DragonHorde* dragonhorde = dynamic_cast<DragonHorde*>(treasure);
    dragon->setGuard(dragonhorde);
    LOG("Dragon Gold : " << coordinate.print());
  }
  
  return treasure;
}

Room *OccupantFactory::pickRandRoom() {
  int r = rand() % rooms.size();
  return rooms.at(r);
}

Room *OccupantFactory::pickPlayerRoom() {
  int r = rand() % rooms.size();
  while (rooms.at(r)->getHasStairs()) {
    r = rand() % rooms.size();
  }
  return rooms.at(r);
}

Room *OccupantFactory::pickStairsRoom() {
  int r = rand() % rooms.size();
  while (rooms.at(r)->getHasPlayer()) {
    r = rand() % rooms.size();
  }
  return rooms.at(r);
}

Tile *OccupantFactory::pickFreeTile(Room *room) {
  Tile *t = room->getRandTile();
  while (t->occupant != nullptr) {
    t = room->getRandTile();
  }
  return t;
}

Dragon *OccupantFactory::createNeighbouringDragon(Point coordinate, Room *room) {
  Tile *tile = nullptr;
  Floor *floor = room->getFloor();
  // What if there are no available spaces adjacent to treasure? (answer atm, infinite loop!)
  while (tile == nullptr || tile->occupant != nullptr || !tile->getIsOccupiableByEnemy()) {
    int r = rand() % 8;
    if (r == 0) {
      tile = floor->getTile(coordinate.getRow()-1, coordinate.getCol()-1);
    }
    if (r == 1) {
      tile = floor->getTile(coordinate.getRow(), coordinate.getCol()-1);
    }
    if (r == 2) {
      tile = floor->getTile(coordinate.getRow()+1, coordinate.getCol()-1);
    }
    if (r == 3) {
      tile = floor->getTile(coordinate.getRow()-1, coordinate.getCol());
    }
    if (r == 4) {
      tile = floor->getTile(coordinate.getRow()+1, coordinate.getCol());
    }
    if (r == 5) {
      tile = floor->getTile(coordinate.getRow()-1, coordinate.getCol()+1);
    }
    if (r == 6) {
      tile = floor->getTile(coordinate.getRow(), coordinate.getCol()+1);
    }
    if (r == 7) {
      tile = floor->getTile(coordinate.getRow()+1, coordinate.getCol()+1);
    }
  } 

  Dragon *dragon = new Dragon(game, tile->getCoordinate());
  tile->occupant = dragon;
  return dragon;
}
