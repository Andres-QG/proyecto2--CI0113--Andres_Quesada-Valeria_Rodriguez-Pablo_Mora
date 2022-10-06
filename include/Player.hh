#ifndef PLAYER_HH
#define PLAYER_HH

#include "Movement.hh"

enum PlayerType { PLAYER1, PLAYER2 };

// Clase "Jugador"
class Player {
private:
  // Para saber cual color y que posee.
  short id;

public:
  Player() : id(-1) {}
  ~Player() {}
  // Método que tendrán todos los tipos de jugador(COM) independientemente de la
  // dificultad.
  virtual Movement rehearsedPlay(Board &board) = 0;
};

class PlayerEasy : public Player {
public:
  // Elegir al azar.
  Movement rehearsedPlay(Board &board);
};

class PlayerMid : public Player {
public:
  Movement rehearsedPlay(Board &board);
};

// MiniMax
class PlayerHard : public Player {
public:
  Movement rehearsedPlay(Board &board);
};

#endif