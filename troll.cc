#include "troll.h"
#include "enemy.h"
#include "point.h"
#include <memory>
using namespace std;

Troll::Troll(Game *game, Point coordinates): Enemy(game, coordinates) {
  stats = new Specs(25, 15, 120, "Troll");
}

Troll::~Troll() {

}

string Troll::messageString() {
  return "T";
}

string Troll::getSymbol() {
  return Troll::symbol;
}

string Troll::symbol = "\033[31mT";

