#include "Grid.h"
#include "AliveCell.h"
#include "DeadCell.h"
#include <fstream>
#include <iostream>
#include <conio.h>

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

#include <conio.h>  // Pour _kbhit() et _getch()

void Grid::updateGrid() {
    // Vérification de l'entrée clavier une seule fois par itération
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 'g' || ch == 'G') {
            // Appel de la fonction pour créer un glider au centre de la grille
            int startX = height / 2;  // Positionner le glider au centre
            int startY = width / 2;
            createGlider(startX, startY);  // Créer un glider à la position spécifiée
        }
        if (ch == 't' || ch == 'T') {
            // Appel de la fonction pour tester la validité de la grille si "t" est pressée
            testGridValidity();
        }
    }

    // Création d'une nouvelle grille pour stocker les mises à jour
    std::vector<std::vector<Cell*>> newCells(height, std::vector<Cell*>(width, nullptr));

    // Parcours de toutes les cellules pour appliquer les règles de Conway
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int liveNeighbors = countLiveNeighbors(i, j);
            bool currentState = cells[i][j]->getState();

            // Application des règles du Jeu de la Vie de Conway
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

    // Remplacer les anciennes cellules par les nouvelles
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete cells[i][j];  // Libérer la mémoire des anciennes cellules
            cells[i][j] = newCells[i][j];  // Remplacer par les nouvelles cellules
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

// Fonction ajoutée pour tester la validité de la grille
void Grid::testGridValidity() {
    // Vérifier que toutes les cellules sont correctement initialisées
    bool valid = true;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (cells[y][x] == nullptr) {
                std::cout << "Erreur: Cellule non initialisée à la position (" << x << ", " << y << ")." << std::endl;
                valid = false;
            }
        }
    }

    // Vérifier la stabilité de la grille (vous pouvez adapter cette logique selon votre besoin)
    // Par exemple, ici on ne compare pas encore avec les grilles précédentes
    std::cout << "La grille est " << (valid ? "valide." : "invalide.") << std::endl;
}


    void Grid::createGlider(int startX, int startY) {
        // Vérifiez si la position permet de créer un glider complet (3x3)
        if (startX + 2 >= height || startY + 2 >= width) {
            std::cerr << "Erreur : impossible de placer le glider à cette position (" << startX << ", " << startY << ")." << std::endl;
            return;
        }

        // Glider configuration : un glider classique à partir de la position (startX, startY)
        cells[startX][startY] = new AliveCell();         // 1
        cells[startX + 1][startY + 1] = new AliveCell(); // 2
        cells[startX + 2][startY] = new AliveCell();     // 3
        cells[startX + 2][startY + 1] = new AliveCell(); // 4
        cells[startX + 1][startY + 2] = new AliveCell(); // 5

        std::cout << "Glider créé à la position (" << startX << ", " << startY << ")." << std::endl;
    }


