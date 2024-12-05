#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "Game.h"
#include "ConsoleView.h"
#include "GraphicView.h"

int main() {
    int width = 20, height = 20;          // Taille de la grille
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

        // Boucle principale pour les it�rations
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
        int iterationSpeed = 200; // Vitesse initiale (en ms)
        bool isPaused = false;   // �tat de pause

        // Fen�tre de Menu
        sf::RenderWindow menuWindow(sf::VideoMode(800, 600), "Menu - Jeu de la Vie");

        // Cr�ation des boutons
        sf::RectangleShape startButton(sf::Vector2f(200, 50));
        startButton.setPosition(300, 200);
        startButton.setFillColor(sf::Color::Green);

        sf::RectangleShape quitButton(sf::Vector2f(200, 50));
        quitButton.setPosition(300, 300);
        quitButton.setFillColor(sf::Color::Red);

        // Boucle de menu
        bool startClicked = false;
        while (menuWindow.isOpen() && !startClicked) {
            sf::Event event;
            while (menuWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    menuWindow.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            std::cout << "D�marrage de la simulation...\n";
                            startClicked = true; // Fermer la fen�tre menu et lancer la simulation
                        }
                        else if (quitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            menuWindow.close(); // Quitter le jeu
                            return 0;
                        }
                    }
                }
            }

            // Dessiner les �l�ments du menu
            menuWindow.clear();
            menuWindow.draw(startButton);
            menuWindow.draw(quitButton);
            menuWindow.display();
        }

        if (startClicked) {
            // Cr�er et afficher la fen�tre de simulation apr�s avoir cliqu� sur Start
            sf::RenderWindow window(sf::VideoMode(800, 600), "Jeu de la Vie - Mode Graphique");

            GraphicView* graphicView = new GraphicView(width, height, 20, iterationSpeed);
            game.setView(graphicView);

            // Boucle principale pour les it�rations graphiques
            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Up) {
                            iterationSpeed = std::max(50, iterationSpeed - 50); // Augmente la vitesse
                        }
                        else if (event.key.code == sf::Keyboard::Down) {
                            iterationSpeed += 50; // Diminue la vitesse
                        }
                        else if (event.key.code == sf::Keyboard::Space) {
                            isPaused = !isPaused; // Met en pause ou reprend
                        }
                    }
                }

                if (!isPaused) {
                    game.updateGrid();
                    window.clear();
                    graphicView->display(*game.getGrid());
                    window.display();
                    sf::sleep(sf::milliseconds(iterationSpeed)); // Attente en fonction de la vitesse
                }
            }

            delete graphicView; // Lib�rer la m�moire apr�s la simulation
        }

    }

    return 0;
}
