#include "werewolf.h"
#include "enemy.h"
#include "point.h"
#include <memory>
using namespace std;

Werewolf::Werewolf(Game *game, Point coordinates): Enemy(game, coordinates) {
  stats = new Specs(30, 5, 120, "Werewolf");
}

Werewolf::~Werewolf() {

}

string Werewolf::messageString() {
  return "W";
}

string Werewolf::getSymbol() {
  return Werewolf::symbol;
}

string Werewolf::symbol = "\033[31mW";
