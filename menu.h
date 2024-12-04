#ifndef MENU_H
#define MENU_H

class Menu {
public:
    void handleInput();              // Gère les entrées du menu
    int getSelectedOption();         // Retourne l'option sélectionnée
    bool isStartSelected() const;    // Vérifie si "Start" a été sélectionné
};

#endif // MENU_H
