#include "point.h"
#include <string>
#include <sstream>
using namespace std;

Point::Point(int row, int col): row{row}, col{col} {

}

Point::Point(Point p, Direction d): row{p.getRow()}, col{p.getCol()} {
  switch (d) {
    case Direction::nw:
      row--;
      col--;
      break;
    case Direction::n:
      row--;
      break;
    case Direction::ne:
      row--;
      col++;
      break;
    case Direction::w:
      col--;
      break;
    case Direction::e:
      col++;
      break;
    case Direction::sw:
      row++;
      col--;
      break;
    case Direction::s:
      row++;
      break;
    case Direction::se:
      row++;
      col++;
      break;
    default:
      break;
  }
}

int Point::getRow() {
  return row;
}

int Point::getCol() {
  return col;
}

string Point::print() {
  ostringstream iss;
  iss << "(" << row << "," << col << ")";
  return iss.str();
}

bool operator==(Point &p1, Point &p2) {
  return p1.getRow() == p2.getRow() && p1.getCol() == p2.getCol();
}
