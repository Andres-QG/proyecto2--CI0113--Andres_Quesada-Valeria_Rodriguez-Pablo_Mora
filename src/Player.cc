#include "Player.hh"
#include <cstdlib>

Movement PlayerEasy::rehearsedPlay(Board &board) {
  vector<Movement> avblMoves = board.getAvblMoves();
  // Numero al azar de 0 a n-1
  int randNum = (rand() % (avblMoves.size()));
  return avblMoves[randNum];
}