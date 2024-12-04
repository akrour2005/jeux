#include "Game.h"
#include <thread>
#include <chrono>
#include <iostream>

Game::Game(int width, int height) {
    grid = new Grid(width, height);
    view = nullptr;
    maxIterations = 0;
    iterationSpeed = 0;
}

Game::~Game() {
    delete grid;
    delete view;
}

void Game::initialize(const std::string& inputFile) {
    grid->initializeGrid(inputFile);
}

void Game::setView(View* viewType) {
    view = viewType;
}

void Game::setMaxIterations(int iterations) {
    maxIterations = iterations;
}

void Game::setIterationSpeed(int speed) {
    iterationSpeed = speed;
}

void Game::start() {
    if (!view) {
        std::cerr << "Vue non définie !" << std::endl;
        return;
    }

    for (int i = 0; i < maxIterations; ++i) {
        std::cout << "Iteration " << i + 1 << ":\n";
        view->display(*grid);  // Affichage des cellules sous forme de 1 et 0
        grid->saveState("iteration_" + std::to_string(i + 1) + ".txt");  // Sauvegarde de l'état
        grid->updateGrid();  // Mise à jour de la grille selon les règles de Conway
        std::this_thread::sleep_for(std::chrono::milliseconds(iterationSpeed));  // Attente avant la prochaine itération
    }
}

void Game::updateGrid() {
    grid->updateGrid();
}

Grid* Game::getGrid() {
    return grid;
}