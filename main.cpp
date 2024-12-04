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
        std::cerr << "Erreur : choix invalide. Veuillez red�marrer le jeu.\n";
        return 1; // Fin du programme
    }

    // Initialisation du jeu
    Game game(width, height);
    try {
        game.initialize(inputFile);
        std::cout << "Chargement de la grille � partir du fichier : " << inputFile << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors de l'initialisation de la grille : " << e.what() << "\n";
        return 1;
    }

    Menu menu;  // Cr�er l'instance du menu
    if (choice == 1) {
        // Mode Console
        int maxIterations, iterationSpeed;

        std::cout << "\n--- Mode Console s�lectionn� ---\n";
        std::cout << "Entrez le nombre maximum d'it�rations : ";
        std::cin >> maxIterations;
        if (maxIterations <= 0) {
            std::cerr << "Erreur : le nombre d'it�rations doit �tre sup�rieur � 0.\n";
            return 1;
        }

        std::cout << "Entrez la vitesse d'it�ration (en millisecondes) : ";
        std::cin >> iterationSpeed;
        if (iterationSpeed <= 0) {
            std::cerr << "Erreur : la vitesse doit �tre sup�rieure � 0.\n";
            return 1;
        }

        game.setIterationSpeed(iterationSpeed);
        game.setMaxIterations(maxIterations);

        ConsoleView* consoleView = new ConsoleView();
        game.setView(consoleView);

        std::cout << "---------------------------------------------\n";
        std::cout << "      Jeu de la Vie - Mode Console\n";
        std::cout << "---------------------------------------------\n";
        std::cout << "�tat initial de la grille :\n";
        consoleView->display(*game.getGrid());

        // Boucle principale
        for (int i = 0; i < maxIterations; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(iterationSpeed));
            game.updateGrid();
            std::cout << "It�ration " << i + 1 << " :\n";
            consoleView->display(*game.getGrid());
        }

        std::cout << "---------------------------------------------\n";
        std::cout << " Simulation termin�e ! Merci d'avoir jou�.\n";
        std::cout << "---------------------------------------------\n";

        delete consoleView;

    }
    else if (choice == 2) {
        // Mode Graphique
        int iterationSpeed;

        std::cout << "\n--- Mode Graphique s�lectionn� ---\n";
        std::cout << "Entrez la vitesse d'it�ration (en millisecondes) : ";
        std::cin >> iterationSpeed;
        if (iterationSpeed <= 0) {
            std::cerr << "Erreur : la vitesse doit �tre sup�rieure � 0.\n";
            return 1;
        }

        GraphicView* graphicView = new GraphicView(width, height, 20, iterationSpeed);
        game.setView(graphicView);

        std::cout << "---------------------------------------------\n";
        std::cout << "     Jeu de la Vie - Mode Graphique\n";
        std::cout << "    Appuyez sur 'Start' pour commencer.\n";
        std::cout << "---------------------------------------------\n";

        // Afficher le menu tant que l'utilisateur n'a pas s�lectionn� "Start"
        while (!menu.isStartSelected()) {
            menu.handleInput(); // G�re les entr�es de l'utilisateur (s�lectionne 'Start' ou 'Quitter')
        }

        // Une fois que "Start" est s�lectionn�, commencer la simulation graphique
        std::cout << "D�marrage de la simulation...\n";

        while (graphicView->isRunning()) {
            graphicView->handleInput(*game.getGrid());
            if (!graphicView->isPaused()) {
                game.updateGrid();
                graphicView->display(*game.getGrid());
                std::this_thread::sleep_for(std::chrono::milliseconds(iterationSpeed));
            }
        }

        std::cout << "---------------------------------------------\n";
        std::cout << " Simulation termin�e ! Merci d'avoir jou�.\n";
        std::cout << "---------------------------------------------\n";

        delete graphicView;
    }

    return 0;
}
