#include "vampire.h"
#include "enemy.h"
#include "point.h"
#include <memory>
using namespace std;

Vampire::Vampire(Game *game, Point coordinates): Enemy(game, coordinates) {
  stats = new Specs(25, 25, 50, "Vampire");
}

Vampire::~Vampire() {

}

string Vampire::messageString() {
  return "V";
}

string Vampire::getSymbol() {
  return Vampire::symbol;
}

string Vampire::symbol = "\033[31mV";
