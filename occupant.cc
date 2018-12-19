#include "occupant.h"
#include "point.h"
#include <string>
using namespace std;

Occupant::Occupant(Game *game, Point coordinates): coordinates{coordinates}, game{game}  {

}

Occupant::~Occupant() { };

Point Occupant::getCoordinates() {
  return coordinates;
}

void Occupant::setCoordinates(Point coordinate) {
  coordinates = coordinate;
}

Game *Occupant::getGame() {
  return game;
}

bool Occupant::isNextTo(Occupant *occupant) {
  Point op = occupant->getCoordinates();

  Point p = Point(coordinates.getRow()-1,coordinates.getCol()-1);
  if (op == p) {
    return true;
  }

  p = Point(coordinates.getRow()-1,coordinates.getCol());
  if (op == p) {
    return true;
  }

  p = Point(coordinates.getRow()-1,coordinates.getCol()+1);
  if (op == p) {
    return true;
  }

  p = Point(coordinates.getRow(),coordinates.getCol()-1);
  if (op == p) {
    return true;
  }

  p = Point(coordinates.getRow(),coordinates.getCol()+1);
  if (op == p) {
    return true;
  }

  p = Point(coordinates.getRow()+1,coordinates.getCol()-1);
  if (op == p) {
    return true;
  }

  p = Point(coordinates.getRow()+1,coordinates.getCol());
  if (op == p) {
    return true;
  }

  p = Point(coordinates.getRow()+1,coordinates.getCol()+1);
  if (op == p) {
    return true;
  }

  return false;
}
