#include "floor.h"
#include "log.h"
#include "point.h"
#include "tile.h"
#include "floortile.h"
#include "verticalwall.h"
#include "blank.h"
#include "door.h"
#include "hallway.h"
#include "horizontalwall.h"
#include "vampire.h"
#include "werewolf.h"
#include "goblin.h"
#include "merchant.h"
#include "dragon.h"
#include "phoenix.h"
#include "troll.h"
#include "stairs.h"
#include "potion.h"
#include "rhpotion.h"
#include "bapotion.h"
#include "bdpotion.h"
#include "phpotion.h"
#include "wapotion.h"
#include "wdpotion.h"
#include "treasure.h"
#include "normalGoldPile.h"
#include "smallHorde.h"
#include "merchantHorde.h"
#include "dragonHorde.h"
#include "occupantFactory.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

int Floor::MaxEnemies = 20;
int Floor::MaxPotions = 10;
int Floor::MaxTreasures = 10;
int Floor::MaxPlayerCharacters = 1;
int Floor::MaxStairs = 1;

Floor::Floor(int floorNum, PlayerCharacter *pc, Game *game):
    floorNum{floorNum},
    pc{pc},
    game{game},
    hasReachedStairs{false},
    enemyCount{0},
    potionCount{0},
    treasureCount{0},
    pCCount{0},
    stairCount{0}, 
    hasCreatedCharacters{false} {
  LOG("Floor constructor...");
  LOG("Done constructing floor...");
}

Floor::~Floor() {
  LOG("Floor destructor...");
  for (uint row=0; row<getRowCount(); ++row) {
    for (uint col=0; col<getColCount(); ++col) {
      delete tiles.at(row).at(col);
    }
  }
}

Tile* Floor::findDragonHorde(Tile *t) {
  Point dp = t->occupant->getCoordinates();  
  
  Point p = Point(dp.getRow()-1,dp.getCol()-1);
  Tile *t2 = getTile(p);
  if (dynamic_cast<DragonHorde*>(t2->occupant)) {
    return t2;
  }
  p = Point(dp.getRow()-1,dp.getCol());
  t2 = getTile(p);
  if (dynamic_cast<DragonHorde*>(t2->occupant)) {
    return t2;
  }

  p = Point(dp.getRow()-1,dp.getCol()+1);
  t2 = getTile(p);
  if (dynamic_cast<DragonHorde*>(t2->occupant)) {
    return t2;
  }

  p = Point(dp.getRow(),dp.getCol()-1);
  t2 = getTile(p);
  if (dynamic_cast<DragonHorde*>(t2->occupant)) {
    return t2;
  }

  p = Point(dp.getRow(),dp.getCol()+1);
  t2 = getTile(p);
  if (dynamic_cast<DragonHorde*>(t2->occupant)) {
    return t2;
  }

  p = Point(dp.getRow()+1,dp.getCol()-1);
  t2 = getTile(p);
  if (dynamic_cast<DragonHorde*>(t2->occupant)) {
    return t2;
  }

  p = Point(dp.getRow()+1,dp.getCol());
  t2 = getTile(p);
  if (dynamic_cast<DragonHorde*>(t2->occupant)) {
    return t2;
  }

  p = Point(dp.getRow()+1,dp.getCol()+1);
  t2 = getTile(p);
  if (dynamic_cast<DragonHorde*>(t2->occupant)) {
    return t2;
  }

  return nullptr;
}

void Floor::linkDragons() {
 LOG("linkDragons!!");
  for (uint row=0; row<getRowCount(); ++row) {
    for (uint col=0; col<getColCount(); ++col) {  
      if (dynamic_cast<Dragon*>(tiles[row][col]->occupant)) {
       LOG("dynamic cast dragon");
       Dragon* d = dynamic_cast<Dragon*>(tiles[row][col]->occupant);
       Tile *t = findDragonHorde(tiles[row][col]);
       DragonHorde* dg = dynamic_cast<DragonHorde*>(t->occupant);
       d->setGuard(dg);
       dg->setGuardDragon(d);     
      }  
     }
   } 
}

Game *Floor::getGame() {
  return game;
}

void Floor::createFloor(vector<string> data) {
  LOG("Creating floor");
  
  for (uint row = 0; row < data.size(); row++) {
    vector<Tile *> temp = createRowOfTiles(data[row], row);
    tiles.emplace_back(temp); 
  }
 LOG("about to set rooms...");
  setRooms();
 LOG("finished creating floor...");
}

vector<Tile *> Floor::createRowOfTiles(string row, int rowNumber) {
  vector<Tile *> tileRow = vector<Tile *>();
  for (uint col = 0; col < row.length(); col++) {
    tileRow.emplace_back(createTile(row[col], Point(rowNumber, col))); 
  } 

  return tileRow;
}

uint Floor::getRowCount() {
  return tiles.size();
}

uint Floor::getColCount() {
  return tiles[0].size();
}

Tile *Floor::createTile(char c, Point coordinates) {
  if (c == '.')  return new FloorTile(coordinates);
  else if (c=='|') return new VerticalWall(coordinates);
  else if (c=='-') return new HorizontalWall(coordinates);
  else if (c==' ') return new Blank(coordinates);
  else if (c=='+') return new Door(coordinates);
  else if (c=='#') return new Hallway(coordinates);

  Tile *tile = new FloorTile(coordinates);
  Occupant *occupant = nullptr;
  if (c=='@') {
    LOG("IM A PC");
    pc->setCoordinates(tile->getCoordinate());
    occupant = pc;
  } else if (c=='V') {
    LOG("IM A VAMPIRE");
    occupant = new Vampire(game, coordinates);
  } else if (c=='W') {
    LOG("IM A WEREWOLF");
    occupant = new Werewolf(game, coordinates);
  } else if (c=='N') {
    LOG("IM A GOBLIN");
    occupant = new Goblin(game, coordinates);
  } else if (c=='M') {
    LOG("IM A MERCHANT");
    occupant = new Merchant(game, coordinates);
  } else if (c=='D') {
    LOG("IM A DRAGON");
    occupant = new Dragon(game, coordinates);
  } else if (c=='X') {
    LOG("IM A PHOENIX");
    occupant = new Phoenix(game, coordinates);
  } else if (c=='T') {
    LOG("IM A TROLL");
    occupant = new Troll(game, coordinates);
  } else if (c=='\\') {
    LOG("IM A STAIRTHING");
    occupant = new Stairs(game, coordinates);
  } else if (c=='0') {
    LOG("IM A RHPotion");
    occupant = new RHPotion(game, coordinates);
  } else if (c=='1') {
    LOG("IM A BAPotion");
    occupant = new BAPotion(game, coordinates);
  } else if (c=='2') {
    LOG("IM A BDPotion");
    occupant = new BDPotion(game, coordinates);
  } else if (c=='3') {
    LOG("IM A PHPotion");
    occupant = new PHPotion(game, coordinates);
  } else if (c=='4') {
    LOG("IM A WAPotion");
    occupant = new WAPotion(game, coordinates);
  } else if (c=='5') {
    LOG("IM A WDPotion");
    occupant = new WDPotion(game, coordinates);
  } else if (c=='6') {
    LOG("IM A GOLD");
    occupant = new NormalGoldPile(game, coordinates);
  } else if (c=='7') {
    LOG("IM A SMALLHORDE");
    occupant = new SmallHorde(game, coordinates);
  } else if (c=='8') {
    LOG("IM A MERCHANTHORDE");
    occupant = new MerchantHorde(game, coordinates);
  } else if (c=='9') {
    LOG("IM A !!DRAGON!!HORDE");
    occupant = new DragonHorde(game, coordinates);
  } else {
    LOG("NOT A RECOGNIZED SYMBOL");
    return nullptr;
  } 
  hasCreatedCharacters = true;
  tile->occupant = occupant;
  return tile;
}

int Floor::getFloorNum() {
  return floorNum;
}

string Floor::getFloorAsString() {
  LOG("Called getFloorAsString...");
  ostringstream oss;
  LOG(tiles.size() << tiles[0].size());
  for (uint row=0; row<getRowCount(); ++row) {
    // we want a newline except at the beginning and end
    if (row != 0) {
     oss << endl;
    }
    for (uint col=0; col<getColCount(); ++col) {
      oss << tiles.at(row).at(col)->getSymbol() << "\033[0m"; 
    }
    if (row == 0) oss << "   If it's your first turn, you can choose your race!";
    if (row == 1) oss << "   h - human, o - orc, e - elf, d - dwarf"; 
    if (row == 3) oss << "   Commands:";
    if (row == 4) oss << "   no,so,ea,we,ne,nw,se,sw: move in the given direction";
    if (row == 5) oss << "   u <direction>: use potion in the given direction";
    if (row == 6) oss << "   r: restart";
    if (row == 7) oss << "   q: quit";
  } 

  return oss.str();
}

bool Floor::getHasReachedStairs() {
  return hasReachedStairs;
}

void Floor::setHasReachedStairs(bool val) {
  hasReachedStairs = val;
}

void Floor:: setRooms() {
 for (auto t : tiles) {
   ostringstream oss;
   for (auto t2 : t) {
     oss << t2->getSymbol();
   }
   LOG(oss.str());
 }
 //rooms should only include floortiles
 //rooms need to be hardcoded
 vector<Tile*> roomtiles1, roomtiles2, roomtiles3, roomtiles4, roomtiles5;
 //roomtiles1
 LOG("setting roomtiles1");
 for (uint i=3; i<7 ;++i) {
  for (uint j=3; j<29; ++j) {
   roomtiles1.emplace_back(tiles.at(i).at(j));
  }
 }
 //roomtiles2
LOG("setting roomtiles2");
 for (uint i=3; i<5; ++i) {
  for (uint j=39; j<62; ++j ) {
   roomtiles2.emplace_back(tiles.at(i).at(j));
  }
 }
 for (uint j=39; j<70; ++j) {
  roomtiles2.emplace_back(tiles.at(5).at(j));
 }
 for (uint j=39; j<73; ++j) {
  roomtiles2.emplace_back(tiles.at(6).at(j));
 } 
 for (uint i=7; i<13; ++i) {
  for (uint j=61; j<76; ++j ) {
   roomtiles2.emplace_back(tiles.at(i).at(j));
  }
 }
 //roomtiles3
LOG("setting roomtiles3");
 for (uint i=10; i<13; ++i) {
  for (uint j=38; j<50; ++j) {
   roomtiles3.emplace_back(tiles.at(i).at(j));
  }
 }
 //roomtiles4
LOG("setting roomtiles4");
 for (uint i=15; i<22; ++i) {
  for (uint j=4; j<25; ++j) {
   roomtiles4.emplace_back(tiles.at(i).at(j));
  }
 }
 //roomtiles5
LOG("setting roomtiles5");
 for (uint i=16; i<19; ++i) {
  for (uint j=65; j<76; ++j) {
   roomtiles5.emplace_back(tiles.at(i).at(j));
  }
 }
 for (uint i=19; i<22; ++i) {
  for (uint j=37; j<76; ++j) {
   roomtiles5.emplace_back(tiles.at(i).at(j));
  }
 }
 LOG("creating new rooms");
 Room* room1 = new Room(this, 1, roomtiles1);
 Room* room2 = new Room(this, 2, roomtiles2);
 Room* room3 = new Room(this, 3, roomtiles3);
 Room* room4 = new Room(this, 4, roomtiles4);
 Room* room5 = new Room(this, 5, roomtiles5);
 LOG("put in vector");
 rooms.emplace_back(room1); 
 rooms.emplace_back(room2);
 rooms.emplace_back(room3);
 rooms.emplace_back(room4);
 rooms.emplace_back(room5); 
}

void Floor:: populate() {
 OccupantFactory of = OccupantFactory(game, rooms); 
 while (pCCount < Floor::MaxPlayerCharacters) {
  playerCharacter = of.placePlayerCharacter();
  pCCount++;
 }
 while (stairCount < Floor::MaxStairs) {
  of.placeStairs();
  stairCount++;
 }
 while (potionCount < Floor::MaxPotions) {
  of.placePotion();
  potionCount++;
 }
 while (treasureCount < Floor::MaxTreasures) {
  Treasure *t = of.placeTreasure();
  treasureCount++;
  if (dynamic_cast<DragonHorde*>(t)) {
   // we also created a dragon!
   enemyCount++;
  }
 }
 while (enemyCount < Floor::MaxEnemies) {
  of.placeEnemy();
  enemyCount++;
 }
}

PlayerCharacter *Floor::getPlayerCharacter() {
  return playerCharacter;
}

vector<Occupant *> Floor::getNeighbourOccupants(Tile *tile) {
  vector<Occupant *> occupants;
  Tile *adjacentTile;

  adjacentTile = getTile(Point(tile->getCoordinate(), Direction::nw));
  if (adjacentTile->occupant != nullptr) {
    occupants.emplace_back(adjacentTile->occupant);
  }
  adjacentTile = getTile(Point(tile->getCoordinate(), Direction::n));
  if (adjacentTile->occupant != nullptr) {
    occupants.emplace_back(adjacentTile->occupant);
  }
  adjacentTile = getTile(Point(tile->getCoordinate(), Direction::ne));
  if (adjacentTile->occupant != nullptr) {
    occupants.emplace_back(adjacentTile->occupant);
  }
  adjacentTile = getTile(Point(tile->getCoordinate(), Direction::w));
  if (adjacentTile->occupant != nullptr) {
    occupants.emplace_back(adjacentTile->occupant);
  }
  adjacentTile = getTile(Point(tile->getCoordinate(), Direction::e));
  if (adjacentTile->occupant != nullptr) {
    occupants.emplace_back(adjacentTile->occupant);
  }
  adjacentTile = getTile(Point(tile->getCoordinate(), Direction::sw));
  if (adjacentTile->occupant != nullptr) {
    occupants.emplace_back(adjacentTile->occupant);
  }
  adjacentTile = getTile(Point(tile->getCoordinate(), Direction::s));
  if (adjacentTile->occupant != nullptr) {
    occupants.emplace_back(adjacentTile->occupant);
  }
  adjacentTile = getTile(Point(tile->getCoordinate(), Direction::se));
  if (adjacentTile->occupant != nullptr) {
    occupants.emplace_back(adjacentTile->occupant);
  }

  return occupants;
}

Tile *Floor::getTile(Point coordinates) {
  return getTile(coordinates.getRow(), coordinates.getCol());
}

Tile *Floor::getTile(int row,  int col) {
  if (row < 0 || row >= (int)getRowCount() ||
      col < 0 || col >= (int)getColCount()) {
    LOG("Floor::getTile" << row << "," << col << ") -- OUT OF RANGE");
    return nullptr;
  }
  return tiles[row][col];
}
