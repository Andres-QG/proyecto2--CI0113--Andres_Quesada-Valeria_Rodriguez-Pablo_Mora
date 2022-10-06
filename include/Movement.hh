#ifndef MOVEMENT_HH
#define MOVEMENT_HH

#include "Board.hh"

enum Directions { WEST, EAST, NORTH, SOUTH };

// Clase "Jugada".
class Movement {
private:
  // xPos y yPos son indices en la matriz
  int xPos, yPos, lineDirection;

public:
  Movement();
  Movement(int xPos, int yPos, int lineDirection);
  ~Movement();

  bool play(Board &actualBoard, int playerType);
};

#endif