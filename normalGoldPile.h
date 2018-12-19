#ifndef __NORMALGOLDPILE__
#define __NORMALGOLDPILE__

#include "treasure.h"
#include "point.h"
#include <string>

class NormalGoldPile : public Treasure {
  public:
    NormalGoldPile(Game *game, Point coordinate);

    static std::string symbol;
    std::string messageString() override;
};

#endif
