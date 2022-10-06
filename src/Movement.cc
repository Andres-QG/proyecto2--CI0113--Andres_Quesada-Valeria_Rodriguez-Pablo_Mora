#include "Movement.hh"

Movement::Movement() : xPos(-1), yPos(-1), lineDirection(-1) {}

Movement::Movement(int xPos, int yPos, int lineDirection) {
  this->xPos = xPos;
  this->yPos = yPos;
  this->lineDirection = lineDirection;
}

Movement::~Movement() {}

bool Movement::play(Board &actualBoard, int playerType) {
  switch (lineDirection) {
  case WEST:
    if (actualBoard.boxes[xPos][yPos].west != NO_OWNER) {
      return false;
    }
    actualBoard.boxes[xPos][yPos].west = playerType;
    if (yPos > 0) {
      actualBoard.boxes[xPos][yPos - 1].east = playerType;
    }
    break;
  case EAST:
    if (actualBoard.boxes[xPos][yPos].east != NO_OWNER) {
      return false;
    }
    actualBoard.boxes[xPos][yPos].east = playerType;
    if (yPos < actualBoard.boxes.size() - 1) {
      actualBoard.boxes[xPos][yPos + 1].west = playerType;
    }
    break;
  case NORTH:
    if (actualBoard.boxes[xPos][yPos].north != NO_OWNER) {
      return false;
    }
    actualBoard.boxes[xPos][yPos].north = playerType;
    if (xPos > 0) {
      actualBoard.boxes[xPos - 1][yPos].south = playerType;
    }
    break;
  case SOUTH:
    if (actualBoard.boxes[xPos][yPos].south != NO_OWNER) {
      return false;
    }
    actualBoard.boxes[xPos][yPos].south = playerType;
    if (xPos < actualBoard.boxes.size() - 1) {
      actualBoard.boxes[xPos + 1][yPos].north = playerType;
    }
    break;

  default:
    return false;
  }
  return true;
}