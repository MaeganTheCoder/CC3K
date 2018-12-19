#ifndef __GAME__
#define __GAME__

#include "playerCharacter.h"
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class Enemy;
//forward declaration
class Floor;

class Game {
    static std::string sMap[];
    static std::vector<std::string> defaultMapVector;
    int floorNum;
    bool fromFile;
    bool hasReachedEnd;
    bool hasDied;
    bool isQuit;
    bool isReset;
    std::string latestMessage;
    std::vector<std::vector<std::string>> contents;
    Floor* currentFloor;    
    PlayerCharacter* pc;

    int getRemainingWidth(uint lengthUsed);
    std::string getHudText();
    bool isGameFinished();
    void executeTurn();
    void enemiesTakeAction(std::ostringstream &oss);
    void executeCharacterTurn(Character *character, std::ostringstream &oss);
    void createFloor(std::vector<std::string> map, bool doPopulate);
    void handleEndGame();
    void moveToNextFloor();
    void reset();
  public:
    Game();
    ~Game();

    void run();
    void print();
    void loadDefaultMap();
    void loadMapFromFile(std:: string filename);
    void onCharacterDies(Character *character);

    PlayerCharacter *getPlayerCharacter();
    Floor *getCurrentFloor();
    void setPlayerCharacter(PlayerCharacter *playerCharacter);
    void setIsQuit(bool val);
    void setIsReset(bool val);
    bool getIsReset();
};

#endif
