#include "Cell.h"

void Cell::toggleState() {
    isAlive = !isAlive;
}

void Cell::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Cell::getState() const {
    return isAlive;
}
