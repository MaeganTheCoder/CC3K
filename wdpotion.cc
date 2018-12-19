#include "wdpotion.h"
#include "point.h"
#include "playerCharacter.h"
#include <string>
using namespace std;

WDPotion::WDPotion(Game *game, Point coordinate): Potion(game, coordinate) {

}

WDPotion::~WDPotion() {

}

string WDPotion::messageString() {
  if (WDPotion::isDiscovered) {
    return "WD";
  }
  return Potion::undiscoveredName;
}

void WDPotion::discover() {
  WDPotion::isDiscovered = true;
}

bool WDPotion::isDiscovered = false;

void WDPotion::getIngestedBy(PlayerCharacter *playerCharacter) {
  LOG("Ingested WD");
  playerCharacter->setDefenceBoost(-5);
}


string WDPotion::symbol = "5";
