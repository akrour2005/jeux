#ifndef VIEW_H
#define VIEW_H

#include "Grid.h"

class View {
public:
    virtual ~View() {}  // Destructeur virtuel pour garantir la destruction correcte des objets dérivés
    virtual void display(const Grid& grid) = 0;  // Méthode virtuelle pure pour afficher la grille
};

#endif  // VIEW_H