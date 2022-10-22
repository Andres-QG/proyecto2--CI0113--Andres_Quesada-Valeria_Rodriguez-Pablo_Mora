#ifndef MOVEMENT_HH
#define MOVEMENT_HH

#include "Board.hh"
/*TODO: Revisar necesidad de EMPTY*/
enum Directions { WEST, EAST, NORTH, SOUTH, EMPTY };

// Clase "Jugada".
class Movement {
private:
  // xPos y yPos son indices en la matriz
  int xPos, yPos;
  Directions lineDirection;

public:
  Movement(int xPos, int yPos, Directions lineDirection);
  ~Movement();
  int getXPos();
  int getYPos();
  Directions getLineDirection();
  // Juega esa jugada en el tablero.
  void play(Board &currentBoard, OwnerType owner);
  /*TODO: Quitar tras adaptar Minimax.*/
  OwnerType playAndAssignOwner(Board &currentBoard, OwnerType owner);
  // revisa si se puede hacer una jugada.
  bool isValid(Board *currentBoard);
};

#endif