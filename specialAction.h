#ifndef SPECIALACTION_H_
#define SPECIALACTION_H_

#include "action.h"
#include "character.h"
#include "direction.h"
#include <string>

class Floor;

class SpecialAction : public Action {
  std::string action;
  Character *character;
  Floor *floor;
  public:
    SpecialAction(std::string action, Character *character, Floor* floor);
    ~SpecialAction();
    void act() override;
    bool involvesPlayerCharacter() override;
};

#endif
