#include "potion.h"
#include <string>
using namespace std;

Potion::Potion(Game *game, Point coordinate): Occupant(game, coordinate) {

}

Potion::~Potion() {

}

string Potion::getSymbol() {
  return "\033[32mP";
}

string Potion::undiscoveredName = "an unknown potion";
