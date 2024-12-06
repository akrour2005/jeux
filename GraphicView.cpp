#include "GraphicView.h"
#include <iostream>

GraphicView::GraphicView(int width, int height, int cellSize, int iterationSpeed)
    : iterationSpeed(iterationSpeed), paused(false), cellSize(cellSize) {
    // Création de la fenêtre
    window.create(sf::VideoMode(width * cellSize, height * cellSize), "Jeu de la Vie");

    // Chargement de la police (si elle n'est plus nécessaire, tu peux aussi la supprimer)
    if (!font.loadFromFile("C:\\Users\\MSI 2023\\OneDrive - Association Cesi Viacesi mail\\Bureau\\AGENCYB.TTF")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }
}

void GraphicView::display(const Grid& grid) {
    window.clear();

    // Affichage des cellules
    for (int i = 0; i < grid.getHeight(); ++i) {
        for (int j = 0; j < grid.getWidth(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1)); // Espacement entre cellules
            cell.setPosition(j * cellSize, i * cellSize);

            if (grid.getCellState(i, j)) {
                cell.setFillColor(sf::Color::Black); // Cellule vivante
            }
            else {
                cell.setFillColor(sf::Color::White); // Cellule morte
            }

            window.draw(cell);
        }
    }

    window.display();
}

void GraphicView::handleInput(Grid& grid) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Interaction avec la grille (clic gauche pour inverser l'état d'une cellule)
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int x = event.mouseButton.y / cellSize;
            int y = event.mouseButton.x / cellSize;
            if (x < grid.getHeight() && y < grid.getWidth()) {
                grid.toggleCellState(x, y);
            }
        }
    }
}

bool GraphicView::isRunning() const {
    return window.isOpen();
}

bool GraphicView::isPaused() const {
    return paused;
}
