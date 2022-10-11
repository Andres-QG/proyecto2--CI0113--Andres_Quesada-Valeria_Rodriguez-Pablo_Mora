#include "Cell.hh"

Cell::Cell()
    : west(NO_OWNER), east(NO_OWNER), north(NO_OWNER), south(NO_OWNER),
      boxOwner(NO_OWNER) {}

Cell::~Cell() {}

bool Cell::boxChecker(enum OwnerType owner) {
  if (east != NO_OWNER && north != NO_OWNER && south != NO_OWNER &&
      west != NO_OWNER && boxOwner == NO_OWNER) {
    boxOwner = owner;
    return true;
  }
  return false;
}

int Cell::availableMovesCount() {
  int count = 0;
  if (east == NO_OWNER) {
    count++;
  }
  if (west == NO_OWNER) {
    count++;
  }
  if (north == NO_OWNER) {
    count++;
  }
  if (south == NO_OWNER) {
    count++;
  }
  return count;
}