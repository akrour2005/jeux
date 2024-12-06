
#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>

// Inclusion des headers des classes Cell, AliveCell, DeadCell
#include "Cell.h"
#include "AliveCell.h"
#include "DeadCell.h"

class Grid {
private:
    std::vector<std::vector<Cell*>> cells;
    int width, height;

public:
    Grid(int w, int h);
    ~Grid();

    void initializeGrid(const std::string& inputFile);
    void updateGrid();
    int countLiveNeighbors(int x, int y);
    void saveState(const std::string& outputFile);
    void toggleCellState(int x, int y);
    bool getCellState(int x, int y) const;
    int getWidth() const;
    int getHeight() const;
};

#endif
