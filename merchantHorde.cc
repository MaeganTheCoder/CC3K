#include "merchantHorde.h"
#include "treasure.h"
#include "point.h"
#include <string>
using namespace std;

MerchantHorde::MerchantHorde(Game *game, Point coordinate): Treasure(game, coordinate) {
  goldValue = 4;
}

string MerchantHorde::messageString() {
  return "Merchant Horde";
}

string MerchantHorde::symbol = "8";

