#include "InteractionHandler.h"
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Gérer les clics de souris
void InteractionHandler::handleMouseClick(int x, int y, Grid& grid) {
    // Vérifier si la cellule est dans les limites de la grille
    if (x >= 0 && y >= 0 && x < grid.getHeight() && y < grid.getWidth()) {
        // Basculer l'état de la cellule à la position donnée
        grid.toggleCellState(x, y);
        std::cout << "Cellule (" << x << ", " << y << ") toggle." << std::endl;
    }
}

// Gérer le redimensionnement de la fenêtre
void InteractionHandler::handleWindowResize(int width, int height) {
    // Redimensionner la fenêtre graphique en fonction des nouvelles dimensions
    std::cout << "Redimensionner la fenêtre à : " << width << "x" << height << std::endl;
    // Vous pouvez mettre ici le code pour ajuster les dimensions dans la classe `GraphicView`
    // Par exemple, mettre à jour la fenêtre SFML pour s'adapter aux nouvelles dimensions
}

// Gérer les changements de vitesse d'itération
void InteractionHandler::handleSpeedChange(int speed) {
    // Modifier la vitesse d'itération en fonction de l'input
    std::cout << "Vitesse d'itération changée à : " << speed << " ms" << std::endl;
    // Vous pouvez ajuster la vitesse dans le `Game` ou `GraphicView`
}
