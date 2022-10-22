#ifndef CELL_HH
#define CELL_HH

#include <iostream>
#include <vector>

using namespace std;

/*TODO: Revisar necesidad de no valid.*/
enum OwnerType { NO_OWNER, PLAYER1, PLAYER2, NO_VALID };

class Cell {
private:
  // Lados del cuadrado (celda).
  OwnerType west, east, north, south, boxOwner;

public:
  // En un inicio que no tiene enlaces entre los puntos.
  Cell();
  ~Cell();

  OwnerType getBoxOwner();
  // 0-w, 1-s, 2-n, 3-s.
  OwnerType *getLine(int direction);
  // true si logra hacer una caja y darle un dueno, false si ya tenia dueno o no
  // hay caja aun.
  bool boxChecker(OwnerType owner);
  int availableMovesCount();

  friend class Board;
  friend class Movement;
};

#endif