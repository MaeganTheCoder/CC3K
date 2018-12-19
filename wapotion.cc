#include "wapotion.h"
#include "point.h"
#include "playerCharacter.h"
#include <string>
using namespace std;

WAPotion::WAPotion(Game *game, Point coordinate): Potion(game, coordinate) {

}

WAPotion::~WAPotion() {

}

string WAPotion::messageString() {
  if (WAPotion::isDiscovered) {
    return "WA";
  }
  return Potion::undiscoveredName;
}

void WAPotion::discover() {
  WAPotion::isDiscovered = true;
}

bool WAPotion::isDiscovered = false;

void WAPotion::getIngestedBy(PlayerCharacter *playerCharacter) {
  LOG("Ingested WA");
  playerCharacter->setAttackBoost(-5);
}


string WAPotion::symbol = "4";
