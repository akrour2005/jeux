#include "AliveCell.h"

AliveCell::AliveCell() {
    isAlive = true;
}

bool AliveCell::nextState(int liveNeighbors) {
    // Une cellule vivante reste vivante avec 2 ou 3 voisins vivants.
    return liveNeighbors == 2 || liveNeighbors == 3;
}