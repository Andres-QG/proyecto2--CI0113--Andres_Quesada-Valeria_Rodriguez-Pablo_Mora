#include "Cell.hh"

Cell::Cell()
    : west(NO_OWNER), east(NO_OWNER), north(NO_OWNER), south(NO_OWNER),
      boxOwner(NO_OWNER) {}

Cell::~Cell() {}

bool Cell::boxChecker(short owner) {
  if (this->east != NO_OWNER && this->north != NO_OWNER &&
      this->south != NO_OWNER && this->west != NO_OWNER &&
      this->boxOwner == NO_OWNER) {
    this->boxOwner = owner;
    return true;
  }
  return false;
}