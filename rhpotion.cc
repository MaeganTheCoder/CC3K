#include "rhpotion.h"
#include "playerCharacter.h"
#include "point.h"
#include <string>
using namespace std;

RHPotion::RHPotion(Game *game, Point coordinate): Potion(game, coordinate) {

}

RHPotion::~RHPotion() {

}

string RHPotion::messageString() {
  if (RHPotion::isDiscovered) {
    return "RH";
  }
  return Potion::undiscoveredName;
}

void RHPotion::discover() {
  RHPotion::isDiscovered = true;
}

bool RHPotion::isDiscovered = false;

void RHPotion::getIngestedBy(PlayerCharacter *playerCharacter) {
  LOG("Ingested RH");
  playerCharacter->setHpThroughPotion(playerCharacter->getHp() + 10);
}

string RHPotion::symbol = "0";
