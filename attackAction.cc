#include "attackAction.h"
#include "dragon.h"
#include "character.h"
#include "floor.h"
#include "direction.h"
#include "log.h"
#include "playerCharacter.h"
#include "enemy.h"
#include <string>
#include <cmath>
using namespace std;

AttackAction::AttackAction(Character *attacker, Character *defender): attacker{attacker}, defender{defender} {
  attackerName = attacker->messageString();
  if (defender != nullptr) defenderName = defender->messageString();
}

AttackAction::~AttackAction() {

}

void AttackAction::act() {
  LOG("AttackAction::act() START");
  
  if (!defender) {
    LOG("We have a null defender, no attacking to be done...");
    return;
  }

  if (!doesAttackHit()) {
    setMissMessage();
    return;
  }

  int damage = calculateDamage();

  bool survived = defender->applyDamage(damage);

  if (!survived) {
    LOG("somebody died");
    defender = nullptr;
  }

  setHitMessage(damage);

  LOG("Attack ended...");
}

int AttackAction::calculateDamage() {
  double denom = 100 + defender->getDef();
  double term = 100 / denom;
  int result = round(term + 0.5);
  int damage = result * attacker->getAtk();
  LOG("Atk: " << attacker->getAtk() << " Def: " << defender->getDef() << " Damage: " << damage);
  return damage;
}

bool AttackAction::doesAttackHit() {
  int probOfHit = attacker->getHitProbability();

  int r = rand() % 100;
  
  return r < probOfHit;
}

void AttackAction::setMissMessage() {
  ostringstream oss;
  oss << attackerName << " attacks " << defenderName << " but misses.";
  message = oss.str();
}

void AttackAction::setHitMessage(int damage) {
  ostringstream oss;

  oss << attackerName << " deals " << damage << " damage to " << defenderName;

  if (!defender) {
    // if defender died, it is now null...
    oss << " (0 HP)";
  } else if (!dynamic_cast<PlayerCharacter*>(defender)) {
    oss << " (" << defender->getHp() << " HP)";
  }
  oss << ".";

  message = oss.str();
}

bool AttackAction::involvesPlayerCharacter() {
  // won't catch pc when pc dies, but we don't need to print message then anyways.  Not pretty, but does work.
  return dynamic_cast<PlayerCharacter*>(attacker) ||
         dynamic_cast<PlayerCharacter*>(defender);
}
