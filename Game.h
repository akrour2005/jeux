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

    // Initialiser la grille à partir d'un fichier
    void initialize(const std::string& inputFile);

    // Définir la vue (interface de rendu)
    void setView(View* viewType);

    // Définir le nombre maximal d'itérations
    void setMaxIterations(int iterations);

    // Définir la vitesse de l'itération (en ms)
    void setIterationSpeed(int speed);

    // Démarrer le jeu
    void start();

    // Mettre à jour la grille
    void updateGrid();

    // Obtenir la grille
    Grid* getGrid();
};

#endif