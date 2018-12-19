#ifndef __OCCUPANTFACTORY__
#define __OCCUPANTFACTORY__

#include "playerCharacter.h"
#include "enemy.h"
#include "stairs.h"
#include "room.h"
#include "point.h"
#include "potion.h"
#include "treasure.h"
#include "dragon.h"
#include <vector>

class Game;

class OccupantFactory {
    Game *game;
    std::vector<Room *> rooms;

    PlayerCharacter *createPlayerCharacter(Point coordinate);
    Enemy *createEnemy(Point coordinate);
    Stairs *createStairs(Point coordinate);
    Potion *createPotion(Point coordinate);
    Treasure *createTreasure(Point coordinate, Room *room);
    Room *pickPlayerRoom();
    Room *pickStairsRoom();
    Room *pickRandRoom();
    Tile *pickFreeTile(Room *room);

    Dragon *createNeighbouringDragon(Point coordinate, Room *room);
  public:
    OccupantFactory(Game *game, std::vector<Room *> rooms);

    PlayerCharacter *placePlayerCharacter();
    Enemy *placeEnemy();
    Stairs *placeStairs();
    Potion *placePotion();
    Treasure *placeTreasure();
};

#endif
