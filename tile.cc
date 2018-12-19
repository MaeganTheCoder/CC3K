#include "tile.h"
#include <iostream>
#include "log.h"
using namespace std;

Tile::Tile(Point coordinate):
 symbol{""}, coordinate{coordinate}, occupant{nullptr} {}

Tile::~Tile() {
}

string Tile::getSymbol(){
 if (occupant!=nullptr) {
   return occupant->getSymbol();
 } else {
   return symbol;
 }
}

Point Tile::getCoordinate() {
 return coordinate;
}

bool Tile::getIsOccupiableByPlayer() {
  return isOccupiableByPlayer;
}

bool Tile::getIsOccupiableByEnemy() {
  return isOccupiableByEnemy;
}
