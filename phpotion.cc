#include "phpotion.h"
#include "point.h"
#include "playerCharacter.h"
#include <string>
using namespace std;

PHPotion::PHPotion(Game *game, Point coordinate): Potion(game, coordinate) {

}

PHPotion::~PHPotion() {
  
}

string PHPotion::messageString() {
  if (PHPotion::isDiscovered) {
    return "PH";
  }
  return Potion::undiscoveredName;
}

void PHPotion::discover() {
  PHPotion::isDiscovered = true;
}

bool PHPotion::isDiscovered = false;

void PHPotion::getIngestedBy(PlayerCharacter *playerCharacter) {
  LOG("Ingested PH");
  playerCharacter->setHpThroughPotion(playerCharacter->getHp() - 10);
}


string PHPotion::symbol = "3";
