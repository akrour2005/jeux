#include "InteractionHandler.h"
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// G�rer les clics de souris
void InteractionHandler::handleMouseClick(int x, int y, Grid& grid) {
    // V�rifier si la cellule est dans les limites de la grille
    if (x >= 0 && y >= 0 && x < grid.getHeight() && y < grid.getWidth()) {
        // Basculer l'�tat de la cellule � la position donn�e
        grid.toggleCellState(x, y);
        std::cout << "Cellule (" << x << ", " << y << ") toggle." << std::endl;
    }
}

// G�rer le redimensionnement de la fen�tre
void InteractionHandler::handleWindowResize(int width, int height) {
    // Redimensionner la fen�tre graphique en fonction des nouvelles dimensions
    std::cout << "Redimensionner la fen�tre � : " << width << "x" << height << std::endl;
    // Vous pouvez mettre ici le code pour ajuster les dimensions dans la classe `GraphicView`
    // Par exemple, mettre � jour la fen�tre SFML pour s'adapter aux nouvelles dimensions
}

// G�rer les changements de vitesse d'it�ration
void InteractionHandler::handleSpeedChange(int speed) {
    // Modifier la vitesse d'it�ration en fonction de l'input
    std::cout << "Vitesse d'it�ration chang�e � : " << speed << " ms" << std::endl;
    // Vous pouvez ajuster la vitesse dans le `Game` ou `GraphicView`
}
