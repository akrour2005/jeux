#ifndef VIEW_H
#define VIEW_H

#include "Grid.h"

class View {
public:
    virtual ~View() {}
    virtual void display(const Grid& grid) = 0;
};

#endif
#pragma once