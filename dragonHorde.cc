#include "game.h"
#include "dragonHorde.h"
#include "treasure.h"
#include "point.h"
#include "dragon.h"
#include <string>
#include "game.h"
using namespace std;

DragonHorde::DragonHorde(Game *game, Point coordinate, Dragon *dragon): Treasure(game, coordinate), guardDragon{dragon} {
  goldValue = 6;
}

DragonHorde::DragonHorde(Game *game, Point coordinate): Treasure(game, coordinate), guardDragon{nullptr} {
  goldValue = 6;
}

string DragonHorde::messageString() {
  return "Dragon Horde";
}


string DragonHorde::symbol = "9";

Dragon * DragonHorde::getGuardDragon() {
  return guardDragon;
}

bool DragonHorde::playerNextToHorde() {
  return isNextTo(game->getPlayerCharacter());
}

void DragonHorde::setGuardDragon(Dragon* d) {
  guardDragon = d;
}
