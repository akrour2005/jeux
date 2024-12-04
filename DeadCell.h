#ifndef DEADCELL_H
#define DEADCELL_H

#include "Cell.h"

class DeadCell : public Cell {
public:
    DeadCell();
    bool nextState(int liveNeighbors) override;
};

#endif
#pragma once