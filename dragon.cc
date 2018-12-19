#include "game.h"
#include "dragon.h"
#include "dragonHorde.h"
#include "enemy.h"
#include "point.h"
#include "attackAction.h"
#include "moveAction.h"
#include <memory>
using namespace std;

Dragon::Dragon(Game *game, Point coordinates): Enemy(game, coordinates), guard{nullptr} {
  stats = new Specs(20, 20, 150, "Dragon");
}

Dragon::~Dragon() {

}

string Dragon::messageString() {
  return "D";
}

string Dragon::getSymbol() {
  return Dragon::symbol;
}

string Dragon::symbol = "\033[31mD";

Action *Dragon::createAction() {
  if (guard->playerNextToHorde()) {
    return new AttackAction(this, game->getPlayerCharacter());
  }
  return new MoveAction(getRandomDirection(), this, game->getCurrentFloor()); 
}

void Dragon::setGuard(DragonHorde* treasure) {
  guard=treasure;
}

DragonHorde* Dragon::getGuard() {
 return guard;
}
