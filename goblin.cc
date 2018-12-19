#include "goblin.h"
#include "enemy.h"
#include "point.h"
#include <memory>
using namespace std;

Goblin::Goblin(Game *game, Point coordinates): Enemy(game, coordinates) {
  stats = new Specs(5, 10, 70, "Goblin");
}

Goblin::~Goblin() {

}

string Goblin::messageString() {
  return "N";
}

string Goblin::getSymbol() {
  return Goblin::symbol;
}

string Goblin::symbol = "\033[31mN";

