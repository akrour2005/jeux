#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include "View.h"
#include "Grid.h"
#include <SFML/Graphics.hpp>

class GraphicView : public View {
private:
    sf::RenderWindow window; // Fenêtre SFML
    int iterationSpeed;      // Vitesse des itérations (en millisecondes)
    int cellSize;            // Taille de chaque cellule (en pixels)
    bool paused;             // État de pause du jeu

public:
    GraphicView(int width, int height, int cellSize, int iterationSpeed);

    void display(const Grid& grid) override; // Affiche la grille
    void handleInput(Grid& grid);            // Gère les interactions utilisateur
    bool isRunning() const;                  // Vérifie si la fenêtre est ouverte
    bool isPaused() const;                   // Vérifie si le jeu est en pause
};

#endif

