#include "character.h"
#include "point.h"
#include "specs.h"
#include "game.h"
#include "log.h"
#include <memory>
#include <string>
#include "action.h"
using namespace std;

Character::Character(Game *game, Point coordinates): Occupant(game, coordinates) {

}

Character::~Character() {
delete stats;}

int Character::getHp() {
  return stats->getHp();
}

int Character::getAtk() {
  return stats->getAtk();
}

int Character::getDef() {
  return stats->getDef();
}

double Character::getGold() {
  return stats->getGold();
}

void Character::setHp(int newHp) {
  stats->setHp(newHp);
}

void Character::setAttackBoost(int boost) {
  stats->setAttackBoost(boost);
}

void Character::setDefenceBoost(int boost) {
  stats->setDefenceBoost(boost);
}

bool Character::isDead() {
  return getHp() <= 0;
}

// return true if character still lives, false otherwise.
bool Character::applyDamage(int damage) {
  LOG("Health before hit: " << getHp());
  stats->setHp(stats->getHp()-damage);
  LOG("Health after hit: " << getHp());

  if (isDead()) {
    LOG("DEATH TO ME!!");
    game->onCharacterDies(this);
    return false;
  }

  return true;
}
