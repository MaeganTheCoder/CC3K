#include "playerCharacter.h"
#include "floor.h"
#include "enemy.h"
#include "action.h"
#include "point.h"
#include "chooseRace.h"
#include "game.h"
#include "specialAction.h"
#include "pickupAction.h"
#include "moveAction.h"
#include "attackAction.h"
#include "log.h"
#include <memory>
#include <iostream>
#include <string>
using namespace std;

PlayerCharacter::PlayerCharacter(Game *game, Point coordinates): Character(game, coordinates), firstCommand{true} {
  stats = new HumanSpecs();
}

string PlayerCharacter::messageString() {
  return "PC";
}

string PlayerCharacter::getSymbol() {
  return PlayerCharacter::symbol;
}

Action *PlayerCharacter::createAction() {
  PlayerCharacter *character = game->getPlayerCharacter();
  Floor *floor = game->getCurrentFloor();
  string s;
  Direction d;
  Action *a = nullptr;
  while (cin >> s) {
    if (s == "h" || s == "e" || s== "d" || s== "o") {
      // Can only change race on first turn.
      if (!firstCommand) {
        continue;
      }
      a = new ChooseRace(s, character);
    } else if (s == "no" || s == "so" || s == "ea" || s == "we" ||
               s== "ne"  || s == "nw" || s == "se" || s == "sw") {
      d=getDirection(s);
      a =  new MoveAction(d, character, floor);
    } else if (s == "r" || s == "q") {
      a = new SpecialAction(s, character, floor);
    } else if (s == "u") {
      cin >> s;
      if (s == "no" || s == "so" || s == "ea" || s == "we" ||
               s== "ne"  || s == "nw" || s == "se" || s == "sw") {
        d=getDirection(s);
        a = new PickupAction(d, character, floor);
      }
    } else if (s == "a") {
      cin >> s;
      if (s == "no" || s == "so" || s == "ea" || s == "we" ||
               s== "ne"  || s == "nw" || s == "se" || s == "sw") {
        a = createAttackAction(s);
      }
    }
    
    if (a) {
      firstCommand = false;
      return a;
    }
  }
  return nullptr;
}

int PlayerCharacter::getHitProbability() {
  return 100;
}

Direction PlayerCharacter::getDirection(string s) {
  Direction d;

  if (s == "no") {
    d = Direction::n;
  } else if (s == "so") {
    d = Direction::s;
  } else if (s == "ea") {
    d = Direction::e;
  } else if (s == "we") {
    d = Direction::w;
  } else if (s == "ne") {
    d = Direction::ne;
  } else if (s == "nw") {
    d = Direction::nw;
  } else if (s == "se") {
    d = Direction::se;
  } else if (s == "sw") {
    d = Direction::sw;
  }

  return d;
}

double PlayerCharacter::calculateScore() {
  return stats->calculateScore();
}

Action *PlayerCharacter::createAttackAction(string s) {
  Direction d = getDirection(s);
  Point targetPoint = Point(getCoordinates(), d);
  Occupant *target = game->getCurrentFloor()->getTile(targetPoint)->occupant;
  LOG("created attack action");
  Enemy *targetEnemy = dynamic_cast<Enemy *>(target);
  LOG("dynamic cast");
  // we may be returning a null enemy in which case we lose our turn.
  return new AttackAction(this, targetEnemy);
}

void PlayerCharacter::resetStats() {
  stats->reset();
}

void PlayerCharacter::setHpThroughPotion(int newHp) {
  stats->setHpThroughPotion(newHp);
}

string PlayerCharacter::getRaceName() {
  return stats->getRaceName();
}

void PlayerCharacter::addGold(int amount) {
  stats->addGold(amount);
}

string PlayerCharacter::symbol = "\033[34m@";
