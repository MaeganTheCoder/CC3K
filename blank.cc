#include "blank.h"

Blank::Blank(Point coordinate): Tile(coordinate) {
 symbol = " ";
 isOccupiableByPlayer=false;
 isOccupiableByEnemy=false;
}
