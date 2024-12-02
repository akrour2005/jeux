#include "Grid.h"
#include "AliveCell.h"
#include "DeadCell.h"
#include <fstream>
#include <iostream>

Grid::Grid(int w, int h) : width(w), height(h) {
    cells.resize(height, std::vector<Cell*>(width, nullptr));
}

Grid::~Grid() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete cells[i][j];
        }
    }
}

void Grid::initializeGrid(const std::string& inputFile) {
    std::ifstream file(inputFile);
    if (!file) {
        std::cerr << "Erreur: impossible d'ouvrir le fichier " << inputFile << std::endl;
        return;
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            char state;
            file >> state;
            if (state == '1') {
                cells[i][j] = new AliveCell();
            }
            else {
                cells[i][j] = new DeadCell();
            }
            cells[i][j]->setPosition(i, j);
        }
    }
    file.close();
}

void Grid::updateGrid() {
    std::vector<std::vector<Cell*>> newCells(height, std::vector<Cell*>(width, nullptr));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int liveNeighbors = countLiveNeighbors(i, j);
            bool currentState = cells[i][j]->getState();

            // Règles de Conway
            if (currentState) {  // Cellule vivante
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newCells[i][j] = new DeadCell();  // La cellule meurt
                }
                else {
                    newCells[i][j] = new AliveCell();  // La cellule reste vivante
                }
            }
            else {  // Cellule morte
                if (liveNeighbors == 3) {
                    newCells[i][j] = new AliveCell();  // La cellule devient vivante
                }
                else {
                    newCells[i][j] = new DeadCell();   // La cellule reste morte
                }
            }
        }
    }

    // Remplacez les anciennes cellules par les nouvelles
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete cells[i][j];  // Libérez la mémoire des anciennes cellules
            cells[i][j] = newCells[i][j];  // Remplacez par les nouvelles cellules
        }
    }
}

int Grid::countLiveNeighbors(int x, int y) {
    int liveNeighbors = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && ny >= 0 && nx < height && ny < width) {
                liveNeighbors += cells[nx][ny]->getState() ? 1 : 0;
            }
        }
    }
    return liveNeighbors;
}

void Grid::saveState(const std::string& outputFile) {
    std::ofstream file(outputFile);
    if (!file) {
        std::cerr << "Erreur: impossible d'ouvrir le fichier " << outputFile << std::endl;
        return;
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file << (cells[i][j]->getState() ? '1' : '0') << " ";
        }
        file << "\n";
    }
    file.close();
}

void Grid::toggleCellState(int x, int y) {
    if (x >= 0 && x < height && y >= 0 && y < width) {
        cells[x][y]->toggleState();
    }
}

bool Grid::getCellState(int x, int y) const {
    return cells[x][y]->getState();
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}
