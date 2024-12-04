#include "ConsoleView.h"
#include <iostream>

void ConsoleView::display(const Grid& grid) {
    for (int i = 0; i < grid.getHeight(); ++i) {
        for (int j = 0; j < grid.getWidth(); ++j) {
            std::cout << (grid.getCellState(i, j) ? "1" : "0") << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void ConsoleView::displayIteration(const Grid& grid, int iteration) {
    std::cout << "Iteration " << iteration << ":\n";
    display(grid);
}