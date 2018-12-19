#ifndef __FLOOR__
#define __FLOOR__

#include "tile.h"
#include "point.h"
#include "playerCharacter.h"
#include <string>
#include <vector>
#include "room.h"

class Game;

class Floor {
    int floorNum;
    PlayerCharacter* pc;
    Game *game;
    bool hasReachedStairs;
    int enemyCount;
    int potionCount;
    int treasureCount;
    int pCCount;
    int stairCount;
    PlayerCharacter *playerCharacter;
    std::vector<std::vector<Tile *>> tiles;
    std::vector<Tile *> createRowOfTiles(std::string row, int rowNumber);
    Tile *createTile(char c, Point coordinates);
    std::vector<Room*> rooms;
    bool hasCreatedCharacters;
    void generatePlayerCharacter();
    void generateStairs();
    void generateEnemy();
    Tile * getRandomTile();
  public:
    Floor(int floorNum, PlayerCharacter *pc, Game *game);
    ~Floor();
    Tile* findDragonHorde(Tile* t);
    void linkDragons();
    void createFloor(std::vector<std::string> data);
    std::string getFloorAsString();
    void setRooms();
    void populate();
    Tile *getTile(Point coordinates);
    Tile *getTile(int row, int col);
    uint getRowCount();
    uint getColCount();
    Game *getGame();
    int getFloorNum();
    bool getHasReachedStairs();
    void setHasReachedStairs(bool val);

    PlayerCharacter *getPlayerCharacter();
    std::vector<Occupant *> getNeighbourOccupants(Tile *tile);

    static int MaxEnemies;
    static int MaxPotions;
    static int MaxTreasures;
    static int MaxPlayerCharacters;
    static int MaxStairs;
};

#endif
