#ifndef TILE_H_
#define TILE_H_

#include <string>
#include "point.h"
#include "occupant.h"

class Tile {
 protected:
  std::string symbol;
  Point coordinate;
  bool isOccupiableByPlayer, isOccupiableByEnemy;
 public:
  Occupant *occupant;
  Tile(Point coordinate);
  virtual  ~Tile()=0; //pure virtual method
  std::string getSymbol();
  Point getCoordinate();
  bool getIsOccupiableByPlayer();
  bool getIsOccupiableByEnemy();
};

#endif
