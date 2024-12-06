#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
private:
    sf::Font font;              // Police du texte
    sf::Text startOption;       // Bouton "Start"
    sf::Text infoOption;        // Bouton "En savoir plus"
    sf::Text quitOption;        // Bouton "Quitter"
    sf::Texture backgroundTexture; // Texture pour l'arrière-plan
    sf::Sprite background;      // Sprite pour afficher la texture
    int selectedIndex;          // Index de sélection

public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);  // Affiche le menu
    void moveUp();                        // Déplace la sélection vers le haut
    void moveDown();                      // Déplace la sélection vers le bas
    int getSelectedOption() const;        // Retourne l'option sélectionnée
};

#endif // MENU_H
