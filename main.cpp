#include <iostream>
#include <thread>
#include <chrono>
#include "Game.h"
#include "ConsoleView.h"
#include "GraphicView.h"
#include "menu.h"

int main() {
    int width = 20, height = 20; // Taille de la grille
    std::string inputFile = "fichier.txt"; // Fichier d'initialisation

    std::cout << "---------------------------------------------\n";
    std::cout << "           BIENVENUE DANS LE JEU DE LA VIE!\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "Choisissez votre mode d'affichage :\n";
    std::cout << "  1. Mode Console : une vue simple et rapide.\n";
    std::cout << "  2. Mode Graphique : une vue interactive.\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "Entrez votre choix (1 ou 2) : ";

    int choice;
    std::cin >> choice;

    if (choice != 1 && choice != 2) {
        std::cerr << "Erreur : choix invalide. Veuillez redémarrer le jeu.\n";
        return 1; // Fin du programme
    }

    // Initialisation du jeu
    Game game(width, height);
    try {
        game.initialize(inputFile);
        std::cout << "Chargement de la grille à partir du fichier : " << inputFile << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors de l'initialisation de la grille : " << e.what() << "\n";
        return 1;
    }

    Menu menu;  // Créer l'instance du menu
    if (choice == 1) {
        // Mode Console
        int maxIterations, iterationSpeed;

        std::cout << "\n--- Mode Console sélectionné ---\n";
        std::cout << "Entrez le nombre maximum d'itérations : ";
        std::cin >> maxIterations;
        if (maxIterations <= 0) {
            std::cerr << "Erreur : le nombre d'itérations doit être supérieur à 0.\n";
            return 1;
        }

        std::cout << "Entrez la vitesse d'itération (en millisecondes) : ";
        std::cin >> iterationSpeed;
        if (iterationSpeed <= 0) {
            std::cerr << "Erreur : la vitesse doit être supérieure à 0.\n";
            return 1;
        }

        game.setIterationSpeed(iterationSpeed);
        game.setMaxIterations(maxIterations);

        ConsoleView* consoleView = new ConsoleView();
        game.setView(consoleView);

        std::cout << "---------------------------------------------\n";
        std::cout << "      Jeu de la Vie - Mode Console\n";
        std::cout << "---------------------------------------------\n";
        std::cout << "État initial de la grille :\n";
        consoleView->display(*game.getGrid());

        // Boucle principale
        for (int i = 0; i < maxIterations; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(iterationSpeed));
            game.updateGrid();
            std::cout << "Itération " << i + 1 << " :\n";
            consoleView->display(*game.getGrid());
        }

        std::cout << "---------------------------------------------\n";
        std::cout << " Simulation terminée ! Merci d'avoir joué.\n";
        std::cout << "---------------------------------------------\n";

        delete consoleView;

    }
    else if (choice == 2) {
        // Mode Graphique
        int iterationSpeed;

        std::cout << "\n--- Mode Graphique sélectionné ---\n";
        std::cout << "Entrez la vitesse d'itération (en millisecondes) : ";
        std::cin >> iterationSpeed;
        if (iterationSpeed <= 0) {
            std::cerr << "Erreur : la vitesse doit être supérieure à 0.\n";
            return 1;
        }

        GraphicView* graphicView = new GraphicView(width, height, 20, iterationSpeed);
        game.setView(graphicView);

        std::cout << "---------------------------------------------\n";
        std::cout << "     Jeu de la Vie - Mode Graphique\n";
        std::cout << "    Appuyez sur 'Start' pour commencer.\n";
        std::cout << "---------------------------------------------\n";

        // Afficher le menu tant que l'utilisateur n'a pas sélectionné "Start"
        while (!menu.isStartSelected()) {
            menu.handleInput(); // Gère les entrées de l'utilisateur (sélectionne 'Start' ou 'Quitter')
        }

        // Une fois que "Start" est sélectionné, commencer la simulation graphique
        std::cout << "Démarrage de la simulation...\n";

        while (graphicView->isRunning()) {
            graphicView->handleInput(*game.getGrid());
            if (!graphicView->isPaused()) {
                game.updateGrid();
                graphicView->display(*game.getGrid());
                std::this_thread::sleep_for(std::chrono::milliseconds(iterationSpeed));
            }
        }

        std::cout << "---------------------------------------------\n";
        std::cout << " Simulation terminée ! Merci d'avoir joué.\n";
        std::cout << "---------------------------------------------\n";

        delete graphicView;
    }

    return 0;
}
