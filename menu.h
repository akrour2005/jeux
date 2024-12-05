#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
private:
    sf::Font font;
    sf::Text startOption;
    sf::Text quitOption;
    int selectedIndex;

public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);  // Affiche le menu
    void moveUp();                        // Déplace la sélection vers le haut
    void moveDown();                      // Déplace la sélection vers le bas
    int getSelectedOption() const;        // Retourne l'option sélectionnée
};

#endif // MENU_H
