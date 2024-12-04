#pragma once
#ifndef INTERACTIONHANDLER_H
#define INTERACTIONHANDLER_H

class Grid;

class InteractionHandler {
public:
    // Méthodes pour gérer les interactions utilisateur
    void handleMouseClick(int x, int y, Grid& grid);
    void handleWindowResize(int width, int height);
    void handleSpeedChange(int speed);
};

#endif