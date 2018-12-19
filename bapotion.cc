#include "bapotion.h"
#include "point.h"
#include "playerCharacter.h"
#include <string>
using namespace std;

BAPotion::BAPotion(Game *game, Point coordinate): Potion(game, coordinate) {

}

BAPotion::~BAPotion() {

}

string BAPotion::messageString() {
  if (BAPotion::isDiscovered) {
    return "BA";
  }
  return Potion::undiscoveredName;
}

void BAPotion::discover() {
  BAPotion::isDiscovered = true;
}

bool BAPotion::isDiscovered = false;

void BAPotion::getIngestedBy(PlayerCharacter *playerCharacter) {
  LOG("Ingested BA");
  playerCharacter->setAttackBoost(5);
}


string BAPotion::symbol = "1";
