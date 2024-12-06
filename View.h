#ifndef VIEW_H
#define VIEW_H

#include "Grid.h"

class View {
public:
    virtual ~View() {}  // Destructeur virtuel pour garantir la destruction correcte des objets d�riv�s
    virtual void display(const Grid& grid) = 0;  // M�thode virtuelle pure pour afficher la grille
};

#endif  // VIEW_H