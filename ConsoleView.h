#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "View.h"

class ConsoleView : public View {
public:
    void display(const Grid& grid) override; // Affiche une grille
    void displayIteration(const Grid& grid, int iteration); // Affiche une itération spécifique
};

#endif