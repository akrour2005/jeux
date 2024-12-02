#include <iostream>
#include <thread>   // Inclus pour std::this_thread
#include <chrono>   // Inclus pour std::chrono
#include "Game.h"
#include "ConsoleView.h"
#include "GraphicView.h"

int main() {
    // Taille de la grille pour la console : 5x10
    int width = 10, height = 5;
    std::string inputFile = "fichier.txt"; // Fichier d'initialisation

    std::cout << "Bienvenue dans le Jeu de la Vie !\n";
    std::cout << "Choisissez le mode d'affichage :\n";
    std::cout << "1. Mode Console\n";
    std::cout << "2. Mode Graphique\n";
    std::cout << "Votre choix : ";

    int choice;
    std::cin >> choice;

    if (choice != 1 && choice != 2) {
        std::cerr << "Choix invalide. Le programme va se terminer.\n";
        return 1; // Code d'erreur
    }

    // Cr�ation du jeu
    Game game(width, height);
    game.initialize(inputFile);

    if (choice == 1) {
        // Mode Console
        int maxIterations, iterationSpeed;

        std::cout << "Entrez le nombre d'it�rations : ";
        std::cin >> maxIterations;
        if (maxIterations <= 0) {
            std::cerr << "Nombre d'it�rations invalide. Le programme va se terminer.\n";
            return 1;
        }

        std::cout << "Entrez la vitesse d'it�ration (en ms) : ";
        std::cin >> iterationSpeed;
        if (iterationSpeed <= 0) {
            std::cerr << "Vitesse d'it�ration invalide. Le programme va se terminer.\n";
            return 1;
        }

        game.setIterationSpeed(iterationSpeed);
        game.setMaxIterations(maxIterations);

        ConsoleView* consoleView = new ConsoleView();
        game.setView(consoleView);

        // Afficher l'�tat initial de la grille
        std::cout << "�tat initial :\n";
        consoleView->display(*game.getGrid());

        // Boucle principale du jeu en mode console
        for (int i = 0; i < maxIterations; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(iterationSpeed));  // Pause entre les it�rations
            game.updateGrid();
            std::cout << "It�ration " << i + 1 << " :\n";
            consoleView->display(*game.getGrid());
        }

        // Nettoyage
        delete consoleView;

    }
    else if (choice == 2) {
        // Mode Graphique
        int iterationSpeed;

        std::cout << "Entrez la vitesse d'it�ration (en ms) : ";
        std::cin >> iterationSpeed;
        if (iterationSpeed <= 0) {
            std::cerr << "Vitesse d'it�ration invalide. Le programme va se terminer.\n";
            return 1;
        }

        // Cr�e une vue graphique
        GraphicView* graphicView = new GraphicView(width, height, 20, iterationSpeed);
        game.setView(graphicView);

        // Boucle principale pour le mode graphique
        while (graphicView->isRunning()) {
            graphicView->handleInput(*game.getGrid());
            if (!graphicView->isPaused()) {
                game.updateGrid();
                graphicView->display(*game.getGrid());
                std::this_thread::sleep_for(std::chrono::milliseconds(iterationSpeed));
            }
        }

        // Nettoyage
        delete graphicView;
    }

    std::cout << "Merci d'avoir jou� ! � bient�t !\n";
    return 0; // Fin du programme
}

