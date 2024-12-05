#include "GraphicView.h"
#include <iostream>

GraphicView::GraphicView(int width, int height, int cellSize, int iterationSpeed)
    : iterationSpeed(iterationSpeed), paused(false), cellSize(cellSize) {
    window.create(sf::VideoMode(width * cellSize, height * cellSize), "Jeu de la Vie");
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

    // Dessiner la grille
    sf::VertexArray lines(sf::Lines);

    for (int x = 0; x <= window.getSize().x; x += cellSize) {
        lines.append(sf::Vertex(sf::Vector2f(x, 0), sf::Color::Black));
        lines.append(sf::Vertex(sf::Vector2f(x, window.getSize().y), sf::Color::Black));
    }

    for (int y = 0; y <= window.getSize().y; y += cellSize) {
        lines.append(sf::Vertex(sf::Vector2f(0, y), sf::Color::Black));
        lines.append(sf::Vertex(sf::Vector2f(window.getSize().x, y), sf::Color::Black));
    }

    window.draw(lines);
    window.display();
}

void GraphicView::handleInput(Grid& grid) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Pause / Reprendre le jeu
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            paused = !paused;
        }

        // Interaction avec la souris
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int x = event.mouseButton.y / cellSize; // Convertit la position pixel en coordonnées grille
            int y = event.mouseButton.x / cellSize;
            if (x >= 0 && x < grid.getHeight() && y >= 0 && y < grid.getWidth()) {
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
