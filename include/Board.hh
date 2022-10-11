#ifndef BOARD_HH
#define BOARD_HH

#include "Cell.hh"
#include "Movement.hh"
#include <vector>

class Board {
private:
  // matriz
  vector<vector<Cell>> boxes;
  int player1Score, player2Score;

public:
  // size puede ser el numero de columnas (o filas) de puntos.
  Board(int size);
  ~Board();
  // Recorre el vector para darle los puntos de cada caja que posee cada
  // jugador.
  void scoreUpdater();
  // Puntuacion individual (puede ser opcional dependiendo de quien la ocupe).
  int getScoreP1();
  int getScoreP2();
  // Cantidad de filas(que es igual a la de cols).
  int getBoardSize();
  // xPos y yPos son indices en el tablero.
  Cell *getCell(int xPos, int yPos);
  // jugadas disponibles.
  vector<Movement> getAvailableMoves();
};

#endif