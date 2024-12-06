#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "View.h"
#include <string>

class Game {
private:
    Grid* grid;
    View* view;
    int maxIterations;
    int iterationSpeed;

public:
    // Constructeur
    Game(int width, int height);

    // Destructeur
    ~Game();

    // Initialiser la grille � partir d'un fichier
    void initialize(const std::string& inputFile);

    // D�finir la vue (interface de rendu)
    void setView(View* viewType);

    // D�finir le nombre maximal d'it�rations
    void setMaxIterations(int iterations);

    // D�finir la vitesse de l'it�ration (en ms)
    void setIterationSpeed(int speed);

    // D�marrer le jeu
    void start();

    // Mettre � jour la grille
    void updateGrid();

    // Obtenir la grille
    Grid* getGrid();
};

#endif