#include "menu.h"
#include <iostream>

bool startSelected = false;  // Variable pour savoir si "Start" a été sélectionné

void Menu::handleInput() {
    std::cout << "Sélectionnez une option:\n";
    std::cout << "1. Start\n";
    std::cout << "2. Quitter\n";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        startSelected = true;
    }
    else if (choice == 2) {
        exit(0);  // Quitter le programme si l'utilisateur choisit de quitter
    }
    else {
        std::cout << "Choix invalide.\n";
    }
}

int Menu::getSelectedOption() {
    return startSelected ? 1 : 0; // Si Start est sélectionné, retourne 1
}

bool Menu::isStartSelected() const {
    return startSelected;
}
