#include "merchant.h"
#include "enemy.h"
#include "point.h"
#include "moveAction.h"
#include "game.h"
#include <memory>
using namespace std;

Merchant::Merchant(Game *game, Point coordinates): Enemy(game, coordinates) {
  stats = new Specs(70, 5, 30, "Merchant");
}

Merchant::~Merchant() {

}

string Merchant::messageString() {
  return "M";
}

string Merchant::getSymbol() {
  return Merchant::symbol;
}

bool Merchant::isHostile = false;
string Merchant::symbol = "\033[31mM";

Action *Merchant::createAction() {
  if (!Merchant::isHostile) {
    return new MoveAction(getRandomDirection(), this, game->getCurrentFloor());
  }

  return Enemy::createAction();
}

bool Merchant::applyDamage(int damage) {
  Merchant::isHostile = true;
  return Character::applyDamage(damage);
}
