#include "menu.h"

Menu::Menu(float width, float height) {
    // Charger une police
    if (!font.loadFromFile("C:\\Users\\MSI 2023\\OneDrive - Association Cesi Viacesi mail\\Bureau\\AGENCYB.TTF")) {
        throw std::runtime_error("Impossible de charger la police.");
    }

    // Charger une image pour l'arrière-plan
    if (!backgroundTexture.loadFromFile("C:\\Users\\MSI 2023\\jeux-de-la-vie\\jeux de la vie\\aa.jpg")) {
        throw std::runtime_error("Impossible de charger l'image de fond.");
    }
    background.setTexture(backgroundTexture);

    // Option Start
    startOption.setFont(font);
    startOption.setString("Start");
    startOption.setCharacterSize(50);
    startOption.setFillColor(sf::Color::Red); // L'option sélectionnée est rouge
    startOption.setPosition(sf::Vector2f(width / 2 - 50, height / 2 - 150));

    // Option En savoir plus
    infoOption.setFont(font);
    infoOption.setString("En savoir plus");
    infoOption.setCharacterSize(50);
    infoOption.setFillColor(sf::Color::White); // Les autres options sont blanches
    infoOption.setPosition(sf::Vector2f(width / 2 - 150, height / 2 - 50));

    // Option Quitter
    quitOption.setFont(font);
    quitOption.setString("Quitter");
    quitOption.setCharacterSize(50);
    quitOption.setFillColor(sf::Color::White); // Les autres options sont blanches
    quitOption.setPosition(sf::Vector2f(width / 2 - 50, height / 2 + 50));

    selectedIndex = 0; // L'option Start est sélectionnée par défaut
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(background);     // Affiche l'arrière-plan
    window.draw(startOption);    // Affiche le bouton Start
    window.draw(infoOption);     // Affiche le bouton En savoir plus
    window.draw(quitOption);     // Affiche le bouton Quitter
}

void Menu::moveUp() {
    if (selectedIndex > 0) {
        if (selectedIndex == 1) infoOption.setFillColor(sf::Color::White);
        if (selectedIndex == 2) quitOption.setFillColor(sf::Color::White);
        --selectedIndex;
    }
    if (selectedIndex == 0) startOption.setFillColor(sf::Color::Red);
    if (selectedIndex == 1) infoOption.setFillColor(sf::Color::Red);
}

void Menu::moveDown() {
    if (selectedIndex < 2) {
        if (selectedIndex == 0) startOption.setFillColor(sf::Color::White);
        if (selectedIndex == 1) infoOption.setFillColor(sf::Color::White);
        ++selectedIndex;
    }
    if (selectedIndex == 1) infoOption.setFillColor(sf::Color::Red);
    if (selectedIndex == 2) quitOption.setFillColor(sf::Color::Red);
}

int Menu::getSelectedOption() const {
    return selectedIndex; // 0 pour Start, 1 pour En savoir plus, 2 pour Quitter
}
