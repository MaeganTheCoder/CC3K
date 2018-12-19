#include "hallway.h"

Hallway::Hallway(Point coordinate): Tile(coordinate) {
 symbol = "#";
 isOccupiableByPlayer = true;
 isOccupiableByEnemy = false;
}
