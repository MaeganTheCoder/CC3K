#include "room.h"
#include "tile.h"
#include "floor.h"
#include <vector>
#include "point.h"

using namespace std;

Room::Room(Floor *floor, int roomNumber, vector<Tile*> roomTiles):
 floor{floor}, roomTiles{roomTiles}, roomNumber{roomNumber}, hasStairs{false}, hasPlayer{false} {}

Room::~Room() {
}

Tile *Room::getRandTile() {
  int r = rand() % roomTiles.size();
  return roomTiles.at(r);
}
/*
Tile *Room::getTile(int x, int y) {
 Tile *tile = nullptr;
 for (auto t : roomTiles) {
  if (t->getCoordinate().getX() == x && t->getCoordinate().getY() == y) {
   tile = t;
  }
 }
 
 return tile;
}
*/
void Room:: setHasPlayer(bool val) {
  hasPlayer=val;
}

bool Room::getHasPlayer() {
  return hasPlayer;
}
 
void Room:: setHasStairs(bool val) {
  hasStairs=val;
}

bool Room::getHasStairs() {
  return hasStairs;
}

Floor *Room::getFloor() {
  return floor;
}
