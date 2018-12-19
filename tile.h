#ifndef TILE_H_
#define TILE_H_

#include <string>
#include "point.h"
#include "occupant.h"

using namespace std;

class Tile {

 protected:
  string symbol;
  Point coordinate;
  bool isOccupiableByPlayer, isOccupiableByEnemy;

 public:
  Occupant *occupant;
  Tile(Point coordinate, char symbol);
  ~Tile();
  string getSymbol();
  Point getCoordinate();
  bool getIsOccupiableByPlayer();
  bool getIsOccupiableByEnemy();

};

#endif
