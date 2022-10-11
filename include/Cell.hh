#ifndef CELL_HH
#define CELL_HH

#include <iostream>

using namespace std;

enum OwnerType { NO_OWNER, PLAYER1, PLAYER2 };

class Cell {
private:
  // Lados del cuadrado (celda).
  enum OwnerType west, east, north, south, boxOwner;

public:
  // En un inicio que no tiene enlaces entre los puntos.
  Cell();
  ~Cell();

  enum OwnerType getBoxOwner(); //*Podría quitarse.
  // true si logra hacer una caja y darle un dueno, false si ya tenia dueno o no
  // hay caja aun.
  bool boxChecker(enum OwnerType owner);
  int availableMovesCount();

  friend class Board;
  friend class Movement;
};

#endif