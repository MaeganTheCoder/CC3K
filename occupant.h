#ifndef __OCCUPANT__
#define __OCCUPANT__

#include "point.h"
#include <string>

class Game;

class Occupant {
    Point coordinates;
  protected:
    Game *game;
  public:
    Occupant(Game *game, Point coordinates);
    virtual ~Occupant()=0;
    virtual std::string getSymbol()=0;

    Point getCoordinates();
    void setCoordinates(Point coordinates);
    Game *getGame();

    bool isNextTo(Occupant *occupant);
    virtual std::string messageString() =0;
};

#endif
