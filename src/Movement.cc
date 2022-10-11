#include "Movement.hh"

Movement::Movement(int xPos, int yPos, enum Directions lineDirection)
    : xPos(xPos), yPos(yPos), lineDirection(lineDirection) {}

Movement::~Movement() {}

int Movement::getXPos() { return this->xPos; }

int Movement::getYPos() { return this->yPos; }

enum Directions Movement::getLineDirection() { return this->lineDirection; }

// Metodo "Jugar":
bool Movement::play(Board &currentBoard, enum OwnerType owner) {
  switch (lineDirection) {
  case WEST:
    if (currentBoard.getCell(xPos, yPos)->west != NO_OWNER) {
      return false;
    }
    currentBoard.getCell(xPos, yPos)->west = owner;
    if (yPos > 0) {
      currentBoard.getCell(xPos, yPos - 1)->east = owner;
    }
    break;
  case EAST:
    if (currentBoard.getCell(xPos, yPos)->east != NO_OWNER) {
      return false;
    }
    currentBoard.getCell(xPos, yPos)->east = owner;
    if (yPos < currentBoard.getBoardSize()) {
      currentBoard.getCell(xPos, yPos + 1)->west = owner;
    }
    break;
  case NORTH:
    if (currentBoard.getCell(xPos, yPos)->north != NO_OWNER) {
      return false;
    }
    currentBoard.getCell(xPos, yPos)->north = owner;
    if (xPos > 0) {
      currentBoard.getCell(xPos - 1, yPos)->south = owner;
    }
    break;
  case SOUTH:
    if (currentBoard.getCell(xPos, yPos)->south != NO_OWNER) {
      return false;
    }
    currentBoard.getCell(xPos, yPos)->south = owner;
    if (xPos < currentBoard.getBoardSize()) {
      currentBoard.getCell(xPos + 1, yPos)->north = owner;
    }
    break;

  default:
    return false;
  }
  return true;
}