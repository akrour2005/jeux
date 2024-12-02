#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include "View.h"
#include "Grid.h"
#include <SFML/Graphics.hpp>

class GraphicView : public View {
private:
    sf::RenderWindow window; // Fen�tre SFML
    int iterationSpeed;      // Vitesse des it�rations (en millisecondes)
    int cellSize;            // Taille de chaque cellule (en pixels)
    bool paused;             // �tat de pause du jeu

public:
    GraphicView(int width, int height, int cellSize, int iterationSpeed);

    void display(const Grid& grid) override; // Affiche la grille
    void handleInput(Grid& grid);            // G�re les interactions utilisateur
    bool isRunning() const;                  // V�rifie si la fen�tre est ouverte
    bool isPaused() const;                   // V�rifie si le jeu est en pause
};

#endif

