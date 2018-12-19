#include "treasure.h"
#include "occupant.h"
#include "point.h"
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

Treasure::Treasure(Game *game, Point coordinate): Occupant(game, coordinate) {

}

Treasure::~Treasure() {

}

int Treasure::getGoldValue() {
  return goldValue;
}

string Treasure::getSymbol() {
  return "\033[1;33mG";
}
