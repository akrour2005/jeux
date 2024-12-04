#include "DeadCell.h"

DeadCell::DeadCell() {
    isAlive = false;
}

bool DeadCell::nextState(int liveNeighbors) {
    // Une cellule morte devient vivante avec exactement 3 voisins vivants.
    return liveNeighbors == 3;
}