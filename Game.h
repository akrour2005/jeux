#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "View.h"

class Game {
private:
    Grid* grid;
    View* view;
    int maxIterations;
    int iterationSpeed;

public:
    Game(int width, int height);
    ~Game();

    void initialize(const std::string& inputFile);
    void setView(View* viewType);
    void setMaxIterations(int iterations);
    void setIterationSpeed(int speed);
    void start();
    void updateGrid();
    Grid* getGrid();
};

#endif
