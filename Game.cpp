#include "Game.h"
#include <thread>
#include <chrono>
#include <iostream>

Game::Game(int width, int height) {
    grid = new Grid(width, height);  // Allocation de mémoire pour la grille
    view = nullptr;  // Initialiser le pointeur de vue à nullptr
    maxIterations = 0;
    iterationSpeed = 0;
}

Game::~Game() {
    // Vérifier si view est non nul avant de le supprimer
    if (view) {
        delete view;
        view = nullptr; // Éviter tout accès futur à un objet déjà supprimé
    }

    // Libérer la mémoire de grid
    delete grid;
    grid = nullptr; // S'assurer qu'on ne tente pas de réutiliser grid après suppression
}

void Game::initialize(const std::string& inputFile) {
    grid->initializeGrid(inputFile);  // Initialiser la grille à partir du fichier
}

void Game::setView(View* viewType) {
    view = viewType;  // Assigner une vue
}

void Game::setMaxIterations(int iterations) {
    maxIterations = iterations;  // Définir le nombre d'itérations
}

void Game::setIterationSpeed(int speed) {
    iterationSpeed = speed;  // Définir la vitesse d'itération
}

void Game::start() {
    if (!view) {
        std::cerr << "Vue non définie !" << std::endl;
        return;
    }

    for (int i = 0; i < maxIterations; ++i) {
        std::cout << "Itération " << i + 1 << " :\n";
        view->display(*grid);  // Afficher la grille
        grid->updateGrid();  // Mettre à jour la grille
        std::this_thread::sleep_for(std::chrono::milliseconds(iterationSpeed));  // Attendre un certain temps
    }
}

void Game::updateGrid() {
    grid->updateGrid();  // Mettre à jour la grille
}

Grid* Game::getGrid() {
    return grid;  // Retourner la grille
}
