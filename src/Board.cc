#include "Board.hh"

Board::Board(int size) : player1Score(0), player2Score(0) {
  // size-1 pues, por una matriz de n*n puntos, hay (n-1)*(n-1) cajas.
  // Filas
  boxes.resize(size - 1);
  // Columnas
  for (int i = size - 1; i < size - 1; i++) {
    boxes[i].resize(size - 1);
  }
}

Board::~Board() {
  for (int i = 0; i < boxes.size(); i++) {
    boxes[i].clear();
  }
  boxes.clear();
}

int Board::getScoreP1() { return this->player1Score; }

int Board::getScoreP2() { return this->player2Score; }

void Board::scoreUpdater() {
  int count1 = 0, count2 = 0;
  // Cuenta las cajas de cada uno.
  for (int i = 0; i < boxes.size(); i++) {
    for (int j = 0; j < boxes[i].size(); j++) {
      if (boxes[i][j].getBoxOwner() == PLAYER1) {
        count1++;
      } else if (boxes[i][j].getBoxOwner() == PLAYER2) {
        count2++;
      }
    }
  }
  // Se actualiza.
  player1Score = count1;
  player2Score = count2;
}