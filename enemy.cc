#include "enemy.h"
#include "character.h"
#include "point.h"
#include "action.h"
#include "moveAction.h"
#include "attackAction.h"
#include "game.h"
#include <memory>
using namespace std;

Enemy::Enemy(Game *game, Point coordinates): Character(game, coordinates) {

}

Enemy::~Enemy() {

}

Action *Enemy::createAction() {
  if (isNextTo(game->getPlayerCharacter())) {
    return new AttackAction(this, game->getPlayerCharacter());
  }

  return new MoveAction(getRandomDirection(), this, game->getCurrentFloor());
}

int Enemy::getHitProbability() {
  return 50;
}

Direction Enemy::getRandomDirection() {
  int r = rand() % 8;
  //LOG("rand = " << r);
  Direction d;
  if (r==0) {
    d = Direction::n;
  } else if (r==1) {
    d = Direction::s;
  } else if (r==2) {
    d = Direction::w;
  } else if (r==3) {
    d = Direction::e;
  } else if (r==4) {
    d = Direction::ne;
  } else if (r==5) {
    d = Direction::nw;
  } else if (r==6) {
    d = Direction::sw;
  } else {
    d = Direction::se;
  }

  return d;
}

