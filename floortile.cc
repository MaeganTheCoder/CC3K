#include "floortile.h"

FloorTile::FloorTile(Point coordinate): Tile(coordinate) {
 symbol = "."; 
 isOccupiableByPlayer=true;
 isOccupiableByEnemy=true;
}
