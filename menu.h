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
    void moveUp();                        // D�place la s�lection vers le haut
    void moveDown();                      // D�place la s�lection vers le bas
    int getSelectedOption() const;        // Retourne l'option s�lectionn�e
};

#endif // MENU_H
