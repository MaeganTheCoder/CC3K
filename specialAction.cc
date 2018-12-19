#include "specialAction.h"
#include "game.h"
using namespace std;

SpecialAction::SpecialAction(string action, Character *character, Floor *floor): action{action}, character{character}, floor{floor} {}

SpecialAction::~SpecialAction() {

}

void SpecialAction::act() {
  Game *game = character->getGame();
  if (action == "r") {
    game->setIsReset(true);
    message = "Reset game.";
  }
  if (action == "q") {
    game->setIsQuit(true);
    message = "Quit game.";
  }
}

bool SpecialAction::involvesPlayerCharacter() {
  // special actions always are about the player character
  return true;
}
