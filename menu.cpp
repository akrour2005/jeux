#include "menu.h"
#include <iostream>

bool startSelected = false;  // Variable pour savoir si "Start" a �t� s�lectionn�

void Menu::handleInput() {
    std::cout << "S�lectionnez une option:\n";
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
    return startSelected ? 1 : 0; // Si Start est s�lectionn�, retourne 1
}

bool Menu::isStartSelected() const {
    return startSelected;
}
