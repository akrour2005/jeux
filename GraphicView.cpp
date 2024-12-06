
#include "GraphicView.h"
#include <iostream>

GraphicView::GraphicView(int width, int height, int cellSize, int iterationSpeed)
    : iterationSpeed(iterationSpeed), paused(false), cellSize(cellSize) {
    // Création de la fenêtre
    window.create(sf::VideoMode(width * cellSize, height * cellSize + 50), "Jeu de la Vie");

    // Chargement de la police pour les boutons
    if (!font.loadFromFile("C:\\Users\\MSI 2023\\OneDrive - Association Cesi Viacesi mail\\Bureau\\AGENCYB.TTF")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }

    createButtons();
}

void GraphicView::createButtons() {
    // Dimensions de la barre des boutons
    buttonBar.setSize(sf::Vector2f(window.getSize().x, 50));
    buttonBar.setFillColor(sf::Color(200, 200, 200));
    buttonBar.setPosition(0, window.getSize().y - 50);

    // Bouton Pause
    pauseButton.setSize(sf::Vector2f(150, 40));
    pauseButton.setPosition(10, window.getSize().y - 45);
    pauseButton.setFillColor(sf::Color::Green);

    pauseText.setFont(font);
    pauseText.setString("Pause");
    pauseText.setCharacterSize(20);
    pauseText.setFillColor(sf::Color::Black);
    pauseText.setPosition(35, window.getSize().y - 40);

    // Bouton Augmenter Vitesse
    speedUpButton.setSize(sf::Vector2f(150, 40));
    speedUpButton.setPosition(170, window.getSize().y - 45);
    speedUpButton.setFillColor(sf::Color::Blue);

    speedUpText.setFont(font);
    speedUpText.setString("+ Vitesse");
    speedUpText.setCharacterSize(20);
    speedUpText.setFillColor(sf::Color::White);
    speedUpText.setPosition(185, window.getSize().y - 40);

    // Bouton Diminuer Vitesse
    slowDownButton.setSize(sf::Vector2f(150, 40));
    slowDownButton.setPosition(330, window.getSize().y - 45);
    slowDownButton.setFillColor(sf::Color::Yellow);

    slowDownText.setFont(font);
    slowDownText.setString("- Vitesse");
    slowDownText.setCharacterSize(20);
    slowDownText.setFillColor(sf::Color::Black);
    slowDownText.setPosition(345, window.getSize().y - 40);

    // Bouton Quitter
    quitButton.setSize(sf::Vector2f(150, 40));
    quitButton.setPosition(490, window.getSize().y - 45);
    quitButton.setFillColor(sf::Color::Red);

    quitText.setFont(font);
    quitText.setString("Quitter");
    quitText.setCharacterSize(20);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(515, window.getSize().y - 40);
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

    // Dessiner les boutons
    window.draw(buttonBar);
    window.draw(pauseButton);
    window.draw(speedUpButton);
    window.draw(slowDownButton);
    window.draw(quitButton);
    window.draw(pauseText);
    window.draw(speedUpText);
    window.draw(slowDownText);
    window.draw(quitText);

    window.display();
}

void GraphicView::handleInput(Grid& grid) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Pause / Reprendre
        if (event.type == sf::Event::MouseButtonPressed) {
            if (pauseButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                paused = !paused;
            }
            else if (speedUpButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                iterationSpeed = std::max(50, iterationSpeed - 50); // Augmente la vitesse
            }
            else if (slowDownButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                iterationSpeed += 50; // Diminue la vitesse
            }
            else if (quitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                window.close(); // Ferme la simulation
            }
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
