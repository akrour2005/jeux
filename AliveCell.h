#ifndef ALIVECELL_H
#define ALIVECELL_H

#include "Cell.h"

class AliveCell : public Cell {
public:
    AliveCell();
    bool nextState(int liveNeighbors) override;
};

#endif
#pragma once