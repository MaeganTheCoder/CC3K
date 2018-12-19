#include "bdpotion.h"
#include "point.h"
#include "playerCharacter.h"
#include <string>
using namespace std;

BDPotion::BDPotion(Game *game, Point coordinate): Potion(game, coordinate) {

}

BDPotion::~BDPotion() {

}

string BDPotion::messageString() {
  if (BDPotion::isDiscovered) {
    return "BD";
  }
  return Potion::undiscoveredName;
}

void BDPotion::discover() {
  BDPotion::isDiscovered = true;
}

bool BDPotion::isDiscovered = false;

void BDPotion::getIngestedBy(PlayerCharacter *playerCharacter) {
  LOG("Ingested BD");
  playerCharacter->setDefenceBoost(5);
}


string BDPotion::symbol = "2";
