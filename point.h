#ifndef __POINT__
#define __POINT__

#include "direction.h"
#include <string>

class Point {
  int row;
  int col;
  public:
    Point(int row, int col);
    Point(Point p, Direction d);
    int getRow();
    int getCol();
    std::string print();
};

bool operator==(Point &p1, Point &p2);

#endif
