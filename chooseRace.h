#ifndef CHOOSERACE_H_
#define CHOOSERACE_H_

#include "action.h"
#include "character.h"
#include "direction.h"
#include <string>

class Floor;

class ChooseRace : public Action {
  std::string action;
  Character *character;
  public:
    ChooseRace(std::string action, Character *character);
    ~ChooseRace();
    void act() override;
    bool involvesPlayerCharacter() override;
};

#endif
