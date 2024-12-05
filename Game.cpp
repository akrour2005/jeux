#include "Game.h"
#include <thread>
#include <chrono>
#include <iostream>

Game::Game(int width, int height) {
    grid = new Grid(width, height);  // Allocation de m�moire pour la grille
    view = nullptr;  // Initialiser le pointeur de vue � nullptr
    maxIterations = 0;
    iterationSpeed = 0;
}

Game::~Game() {
    // V�rifier si view est non nul avant de le supprimer
    if (view) {
        delete view;
        view = nullptr; // �viter tout acc�s futur � un objet d�j� supprim�
    }

    // Lib�rer la m�moire de grid
    delete grid;
    grid = nullptr; // S'assurer qu'on ne tente pas de r�utiliser grid apr�s suppression
}

void Game::initialize(const std::string& inputFile) {
    grid->initializeGrid(inputFile);  // Initialiser la grille � partir du fichier
}

void Game::setView(View* viewType) {
    view = viewType;  // Assigner une vue
}

void Game::setMaxIterations(int iterations) {
    maxIterations = iterations;  // D�finir le nombre d'it�rations
}

void Game::setIterationSpeed(int speed) {
    iterationSpeed = speed;  // D�finir la vitesse d'it�ration
}

void Game::start() {
    if (!view) {
        std::cerr << "Vue non d�finie !" << std::endl;
        return;
    }

    for (int i = 0; i < maxIterations; ++i) {
        std::cout << "It�ration " << i + 1 << " :\n";
        view->display(*grid);  // Afficher la grille
        grid->updateGrid();  // Mettre � jour la grille
        std::this_thread::sleep_for(std::chrono::milliseconds(iterationSpeed));  // Attendre un certain temps
    }
}

void Game::updateGrid() {
    grid->updateGrid();  // Mettre � jour la grille
}

Grid* Game::getGrid() {
    return grid;  // Retourner la grille
}
