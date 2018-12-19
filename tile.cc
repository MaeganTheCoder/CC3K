#include "tile.h"
#include <iostream>
#include "log.h"
using namespace std;

Tile::Tile(Point coordinate, char symbol):
 symbol{string(1,symbol)}, coordinate{coordinate}, occupant{nullptr} {
  if (symbol == '.') {
    isOccupiableByPlayer = true;
    isOccupiableByEnemy = true;  
  } else if (symbol == '|') {
    isOccupiableByPlayer = false;
    isOccupiableByEnemy = false;  
  } else if (symbol == '-') {
    isOccupiableByPlayer = false;
    isOccupiableByEnemy = false;  
  } else if (symbol == ' ') { 
    isOccupiableByPlayer = false;
    isOccupiableByEnemy = false;  
  } else if (symbol == '+') {
    isOccupiableByPlayer = true;
    isOccupiableByEnemy = false;  
  } else if (symbol == '#') {
    isOccupiableByPlayer = true;
    isOccupiableByEnemy = false;  
  }
}

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
