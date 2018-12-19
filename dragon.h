#ifndef __DRAGON__
#define __DRAGON__

#include "enemy.h"
#include "point.h"
#include <memory>

class DragonHorde;
class Action;

class Dragon : public Enemy {
   DragonHorde *guard; 
 public:
    Dragon(Game *game, Point coordinates);
    ~Dragon();
    std::string getSymbol() override;

    static std::string symbol;
    std::string messageString() override;
    Action* createAction() override;
    void setGuard(DragonHorde* treasure);
    DragonHorde* getGuard();
};

#endif

