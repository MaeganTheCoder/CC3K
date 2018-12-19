#include "game.h"
#include "log.h"
#include <memory>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
  LOG("STARTING");

  //srand(time(NULL));
  srand(101);

  try {
    Game *game = new Game();
    if (argc-1 == 0) { //no commant line arguments must populate floor randomly
      game->loadDefaultMap();
    } else { //command line argument, read in floor
      string filename = argv[1];
      game->loadMapFromFile(filename);
    }
    LOG("game about to run");
    game->run();
    while (game->getIsReset() == true) {
     delete game;
     game = new Game;
     game->loadDefaultMap();
     game->run();
    }
    delete game;
    cout << "Do you want to play again?" <<endl;
    string answer;
    while (cin >> answer) {
     if (answer == "yes") {
      LOG("answer is yes");
      game = new Game(); 
      LOG("game = new Game);");
      game->loadDefaultMap();
      game->run();
      LOG("called game->run();");
      delete game;
      cout <<"Do you want to play again?" <<endl;
     } else break;
    }
  } catch (exception e) {
    LOG("EXCEPTION: " << e.what());
  }
  LOG("DONE");
}
