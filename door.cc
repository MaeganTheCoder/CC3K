#include "door.h"

Door::Door(Point coordinate): Tile(coordinate) {
 symbol = "+";
 isOccupiableByPlayer = true;
 isOccupiableByEnemy = false;
}
