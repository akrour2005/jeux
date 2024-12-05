#include "menu.h"

Menu::Menu(float width, float height) {
    // Charger une police
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Impossible de charger la police.");
    }

    // Option Start
    startOption.setFont(font);
    startOption.setString("Start");
    startOption.setCharacterSize(50);
    startOption.setFillColor(sf::Color::Red); // L'option sélectionnée est rouge
    startOption.setPosition(sf::Vector2f(width / 2 - 50, height / 2 - 100));

    // Option Quitter
    quitOption.setFont(font);
    quitOption.setString("Quitter");
    quitOption.setCharacterSize(50);
    quitOption.setFillColor(sf::Color::White); // Les autres options sont blanches
    quitOption.setPosition(sf::Vector2f(width / 2 - 50, height / 2));

    selectedIndex = 0; // L'option Start est sélectionnée par défaut
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(startOption);
    window.draw(quitOption);
}

void Menu::moveUp() {
    if (selectedIndex > 0) {
        quitOption.setFillColor(sf::Color::White);
        startOption.setFillColor(sf::Color::Red);
        selectedIndex = 0;
    }
}

void Menu::moveDown() {
    if (selectedIndex < 1) {
        startOption.setFillColor(sf::Color::White);
        quitOption.setFillColor(sf::Color::Red);
        selectedIndex = 1;
    }
}

int Menu::getSelectedOption() const {
    return selectedIndex; // 0 pour "Start", 1 pour "Quitter"
}
