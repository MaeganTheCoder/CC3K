#include "verticalwall.h"

VerticalWall::VerticalWall(Point coordinate): Tile(coordinate) {
 symbol = "|";
 isOccupiableByPlayer=false;
 isOccupiableByEnemy=false;
}
