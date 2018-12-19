#include "chooseRace.h"
#include "point.h"
#include "playerCharacter.h"
#include "specs.h"
#include "game.h"
using namespace std;

ChooseRace::ChooseRace(string action, Character *character): action{action}, character{character} {}

ChooseRace::~ChooseRace() {

}

void ChooseRace::act() { 
  delete character->stats;

  if (action == "h") {
    character->stats = new HumanSpecs();
    message = "Player Character became a Human.";
  } else if (action == "e") {
    character->stats = new ElfSpecs();
    message = "Player Character became an Elf.";
  } else if (action == "o") {
    character->stats = new OrcSpecs();
    message = "Player Character became an Orc.";
  } else if (action == "d") {
    character->stats = new DwarfSpecs();
    message = "Player Character became a Dward.";
  }
}

bool ChooseRace::involvesPlayerCharacter() {
  return true;
}
