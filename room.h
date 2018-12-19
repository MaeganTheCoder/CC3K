#ifndef ROOM_H_
#define ROOM_H_

#include <vector>

class Tile;
class Point;
class Floor;

class Room {
  Floor *floor;
  std::vector<Tile*> roomTiles;
  int roomNumber;
  bool hasStairs;
  bool hasPlayer;
 public:
  Room(Floor *floor, int roomNumber, std::vector<Tile*> roomTiles);
  ~Room();
  Tile *getRandTile();
  void setHasStairs(bool val);
  void setHasPlayer(bool val);
  bool getHasStairs();
  bool getHasPlayer();
  Floor *getFloor();
};

#endif
