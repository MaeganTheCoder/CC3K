#include "phoenix.h"
#include "enemy.h"
#include "point.h"
#include <memory>
using namespace std;

Phoenix::Phoenix(Game *game, Point coordinates): Enemy(game, coordinates) {
  stats = new Specs(35, 20, 50, "Phoenix");
}

Phoenix::~Phoenix() {

}

string Phoenix::messageString() {
  return "X";
}

string Phoenix::getSymbol() {
  return Phoenix::symbol;
}

string Phoenix::symbol = "\033[31mX";

