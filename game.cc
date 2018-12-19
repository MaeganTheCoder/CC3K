#include "dragonHorde.h"
#include "game.h"
#include "action.h"
#include "floor.h"
#include "enemy.h"
#include "playerCharacter.h"
#include "log.h"
#include "merchant.h"
#include "dragon.h"
#include "merchantHorde.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

const int MaxFloors = 5;

Game::Game(): floorNum{0}, hasReachedEnd{false}, hasDied{false}, isQuit{false}, isReset{false} {
  pc = new PlayerCharacter(this, Point(0, 0));
  latestMessage = "Player character has spawned.";
  srand(time(NULL));
  LOG("Creating Game");
}

Game::~Game() {
  LOG("Destroying Game");
  delete currentFloor;
}

void Game::loadDefaultMap() {
  LOG("START - Loading default map...");
  fromFile=false;
  createFloor(Game::defaultMapVector, true);

  LOG("FINISH - Loading default map...");
}

void Game::loadMapFromFile(std::string filename) {
  LOG("loading map from file...");
  fromFile=true;
  fstream file {filename};
  string row;
  vector<string> contents1, contents2, contents3, contents4, contents5;
  int counter=0;
  while (getline(file,row)) {
    if (counter<25) contents1.emplace_back(row);
    else if (counter<50) contents2.emplace_back(row);
    else if (counter<75) contents3.emplace_back(row);
    else if (counter<100) contents4.emplace_back(row);
    else if (counter<125) contents5.emplace_back(row);
    counter++;
  } 
  contents.emplace_back(contents1);
  contents.emplace_back(contents2);
  contents.emplace_back(contents3);
  contents.emplace_back(contents4);
  contents.emplace_back(contents5);
  
  createFloor(contents[0], false);

  LOG("FINISH - Loading given map...");  
}

void Game::run() {
  LOG("run was called");
  while (!isGameFinished()) {
    LOG("!isGameFinished");
    if (isReset) {
     LOG("isreset"); 
     reset();
    }
    LOG("try to print");
    print();
    LOG("printed");
    executeTurn();
  }

  handleEndGame();
}

void Game::handleEndGame() {
  if (hasReachedEnd) {
    print();
    cout << "Congratulations!  Your score is " << pc->calculateScore() << "." << endl;
  }
  if (hasDied) {
    print();
    cout << "You died.  Your score is " << pc->calculateScore() << "." << endl;
  } 
}

void Game::executeTurn() {
  LOG("Executing turn...");
  ostringstream oss;

  executeCharacterTurn(pc, oss);
 
  if (currentFloor->getHasReachedStairs()) {
    moveToNextFloor();
    return;
  }
  if (isQuit || isReset) {
    return;
  }

  enemiesTakeAction(oss);

  latestMessage = oss.str();
  //LOG("Finished Executing turn...");
}

void Game::moveToNextFloor() {
  LOG("move to next floor was called");
  if (floorNum == MaxFloors) {
    hasReachedEnd = true;
    return;
  }
 
  delete currentFloor;
  LOG("curfloor deleted");
  currentFloor = nullptr;
  LOG("curfloor set to nullptr");
  LOG(floorNum);
  if (fromFile) {
   LOG("first condition");
   createFloor(contents[floorNum], false);
  } else {
   LOG("else condition");
   createFloor(Game::defaultMapVector, true);
  }
  pc->resetStats();
}

void Game::createFloor(vector<string> map, bool doPopulate) {
  floorNum++;

  currentFloor = new Floor(floorNum, pc, this); 
  currentFloor->createFloor(map);

  if (doPopulate) {
    currentFloor->populate();
  } else {
    currentFloor->linkDragons();
  }
  latestMessage = "Player Character has spawned.";
}

void Game::enemiesTakeAction(ostringstream &oss) {
  vector<Enemy *> enemiesToAct;
   LOG("enemies to act size:" << enemiesToAct.size());
   LOG(currentFloor->getRowCount() << " " << currentFloor->getColCount());
  for (int row = 0; row < (int)currentFloor->getRowCount(); ++row) {
    for (int col = 0; col < (int)currentFloor->getColCount(); ++col) {
      Tile *tile = currentFloor->getTile(row, col);
      Enemy *enemy = tile->occupant == nullptr ? nullptr : dynamic_cast<Enemy *>(tile->occupant);
      if (enemy) {
        enemiesToAct.emplace_back(enemy);
      }
    }
  }
  LOG("enemies to act size:" << enemiesToAct.size());
  for (auto enemy : enemiesToAct) {
    if (!hasDied) {
      executeCharacterTurn(enemy, oss);
    }
    else {
      return;
    }
  }
}

void Game::executeCharacterTurn(Character *character, ostringstream &oss) {
  Action *a = character->createAction();
  LOG("Got action...");
  a->act();
  if (a->involvesPlayerCharacter()) {
    if (!oss.str().empty()) {
      oss << "  ";
    }
    oss << a->getMessage();
  }
  LOG("acted!");
  delete a;
}

void Game::onCharacterDies(Character *character) {
  if (character == pc) {
    LOG("Player has died. :p");
    hasDied = true;
    //pc = nullptr;
  }

  else {
    LOG("Enemy " << character->getSymbol() << " has died.");
    Tile *tile = currentFloor->getTile(character->getCoordinates());
    tile->occupant = nullptr;
    if (dynamic_cast<Merchant*>(character)) {
      tile->occupant = new MerchantHorde(this, tile->getCoordinate());
    } else if ((!(dynamic_cast<Merchant*>(character)) &&
               !(dynamic_cast<Dragon*>(character)))) {
      pc->addGold(1);
    } else if (dynamic_cast<Dragon*>(character)) {
      //set guard dragon to be null in DragonHorde
      LOG("a dragon died, set dragonhorde guarddragon to null");
      Dragon* d = dynamic_cast<Dragon*>(character);
      d->getGuard()->setGuardDragon(nullptr);
    }
    delete character;
  } 

}

void Game::reset() {
  Tile *tile = currentFloor->getTile(pc->getCoordinates());  
  tile->occupant = nullptr;
  delete pc;
  pc = new PlayerCharacter(this, Point(0, 0));
  floorNum--;
  moveToNextFloor();
  isReset = false;
}

bool Game::isGameFinished() {
  return (isReset || isQuit || hasReachedEnd || hasDied);
}

void Game::print() {
  LOG("Printing floor...");
  cout << currentFloor->getFloorAsString() << endl;
  cout << getHudText();
}

string Game::getHudText() {
  LOG("getHudText");
  ostringstream oss;
  ostringstream raceTxtOss;
  ostringstream floorTxtOss;

  raceTxtOss << "Race: " << pc->getRaceName() << " Gold: " << pc->getGold();
  string raceTxt = raceTxtOss.str();

  floorTxtOss << "Floor: " << currentFloor->getFloorNum();
  string floorTxt = floorTxtOss.str();

  int emptySpaceCount = getRemainingWidth(raceTxt.length()) - floorTxt.length();
  oss << raceTxt << string(emptySpaceCount, ' ') << floorTxt << endl;
  oss << "HP: " << pc->getHp() << endl;
  oss << "Atk: " << pc->getAtk() << endl;
  oss << "Def: " << pc->getDef() << endl;
  oss << "Action: " << latestMessage << endl;

  return oss.str();
}

int Game::getRemainingWidth(uint lengthUsed) {
  return currentFloor->getColCount() - lengthUsed;
}

PlayerCharacter *Game::getPlayerCharacter() {
  return pc;
}

Floor *Game::getCurrentFloor() {
  return currentFloor;
}

void Game::setIsReset(bool val) {
  isReset = val;
}

void Game::setIsQuit(bool val) {
  isQuit = val;
}

void Game::setPlayerCharacter(PlayerCharacter *playerCharacter) {
  //LOG("setPlayerCharacter START");
  delete pc;
  pc = playerCharacter;
  //LOG("setPlayerCharacter END");
}

string Game::sMap[] = {
"|-----------------------------------------------------------------------------|",
"|                                                                             |",
"| |--------------------------|        |-----------------------|               |",
"| |..........................|        |.......................|               |",
"| |..........................+########+.......................|-------|       |",
"| |..........................|   #    |...............................|--|    |",
"| |..........................|   #    |..................................|--| |",
"| |----------+---------------|   #    |----+----------------|...............| |",
"|            #                 #############                |...............| |",
"|            #                 #     |-----+------|         |...............| |",
"|            #                 #     |............|         |...............| |",
"|            ###################     |............|   ######+...............| |",
"|            #                 #     |............|   #     |...............| |",
"|            #                 #     |-----+------|   #     |--------+------| |",
"|  |---------+-----------|     #           #          #              #        |",
"|  |.....................|     #           #          #         |----+------| |",
"|  |.....................|     ########################         |...........| |",
"|  |.....................|     #           #                    |...........| |",
"|  |.....................|     #    |------+--------------------|...........| |",
"|  |.....................|     #    |.......................................| |",
"|  |.....................+##########+.......................................| |",
"|  |.....................|          |.......................................| |",
"|  |---------------------|          |---------------------------------------| |",
"|                                                                             |",
"|-----------------------------------------------------------------------------|"
};

vector<string> Game::defaultMapVector = vector<string>(Game::sMap, Game::sMap + sizeof(Game::sMap) / sizeof(Game::sMap[0]));

bool Game::getIsReset() {
  return isReset;
}

