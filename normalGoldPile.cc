#include "normalGoldPile.h"
#include "treasure.h"
#include "point.h"
#include <string>
using namespace std;

NormalGoldPile::NormalGoldPile(Game *game, Point coordinate): Treasure(game, coordinate) {
  NormalGoldPile::goldValue = 1;
}

string NormalGoldPile::messageString() {
  return "Normal Gold Pile";
}


string NormalGoldPile::symbol = "6";
