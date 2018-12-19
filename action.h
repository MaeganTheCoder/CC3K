#ifndef __ACTION__
#define __ACTION__

#include <string>
#include <iostream>
#include <sstream>

class Floor;
class Character;

class Action {
  protected:
    std::string message;
  public:
    virtual ~Action() =0;
    virtual void act() =0;
    std::string getMessage();
    virtual bool involvesPlayerCharacter() =0;
};

#endif
