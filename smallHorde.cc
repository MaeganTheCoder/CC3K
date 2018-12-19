#include "smallHorde.h"
#include "treasure.h"
#include "point.h"
#include <string>
using namespace std;

SmallHorde::SmallHorde(Game *game, Point coordinate): Treasure(game, coordinate) {
  goldValue = 2;
}

string SmallHorde::messageString() {
  return "Small Horde";
}

string SmallHorde::symbol = "7";
