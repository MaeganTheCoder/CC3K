#include "stairs.h"
#include "point.h"
#include <string>
using namespace std;

Stairs::Stairs(Game *game, Point coordinates): Occupant(game, coordinates) {

}

Stairs::~Stairs() {

}

string Stairs::messageString() {
  return "Stairs";
}

string Stairs::getSymbol() {
  return Stairs::symbol;
}

string Stairs::symbol = "\033[36m\\";
