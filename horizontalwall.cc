#include "horizontalwall.h"

HorizontalWall::HorizontalWall(Point coordinate): Tile(coordinate) {
 symbol = "-";
 isOccupiableByPlayer=false;
 isOccupiableByEnemy=false;
}
