
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "Game.h"
#include "ConsoleView.h"
#include "GraphicView.h"

int main() {
    int width = 40, height = 40;          // Taille de la grille
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
    if (choice != 1 && choice != 2) {
        std::cerr << "Choix invalide. Le programme va se terminer.\n";
        return 1; // Code d'erreur
    }

    

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

    if (choice == 2) {
        // Mode Graphique
        int iterationSpeed = 200; // Vitesse initiale (en ms)
        bool isPaused = false;   // �tat de pause

        // Fen�tre de Menu
        sf::RenderWindow menuWindow(sf::VideoMode(800, 600), "Menu - Jeu de la Vie");

        // Charger la police
        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\MSI 2023\\OneDrive - Association Cesi Viacesi mail\\Bureau\\AGENCYB.TTF")) {
            std::cerr << "Erreur : Impossible de charger la police.\n";
            return 1;
        }

        // Cr�ation des boutons
        sf::RectangleShape startButton(sf::Vector2f(200, 50));
        startButton.setPosition(300, 150);
        startButton.setFillColor(sf::Color::Green);

        sf::RectangleShape infoButton(sf::Vector2f(200, 50)); // Nouveau bouton
        infoButton.setPosition(300, 250);
        infoButton.setFillColor(sf::Color::Blue);

        sf::RectangleShape quitButton(sf::Vector2f(200, 50));
        quitButton.setPosition(300, 350);
        quitButton.setFillColor(sf::Color::Red);

        // Texte sur les boutons
        sf::Text startText("Commencer", font, 24);
        startText.setPosition(325, 160);
        startText.setFillColor(sf::Color::White);

        sf::Text infoText("En savoir plus", font, 24);
        infoText.setPosition(315, 260);
        infoText.setFillColor(sf::Color::White);

        sf::Text quitText("Quitter", font, 24);
        quitText.setPosition(355, 360);
        quitText.setFillColor(sf::Color::White);

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
                        else if (infoButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            // Afficher la fen�tre d'informations
                            sf::RenderWindow infoWindow(sf::VideoMode(600, 400), "� propos du Jeu de la Vie");

                            while (infoWindow.isOpen()) {
                                sf::Event infoEvent;
                                while (infoWindow.pollEvent(infoEvent)) {
                                    if (infoEvent.type == sf::Event::Closed) {
                                        infoWindow.close();
                                    }
                                }

                                infoWindow.clear(sf::Color::White);

                                // L�gende des commandes
                                sf::RectangleShape pauseSquare(sf::Vector2f(30, 30));
                                pauseSquare.setPosition(50, 50);
                                pauseSquare.setFillColor(sf::Color::Green);

                                sf::RectangleShape quitSquare(sf::Vector2f(30, 30));
                                quitSquare.setPosition(50, 100);
                                quitSquare.setFillColor(sf::Color::Red);

                                sf::RectangleShape speedUpSquare(sf::Vector2f(30, 30));
                                speedUpSquare.setPosition(50, 150);
                                speedUpSquare.setFillColor(sf::Color::Blue);

                                sf::RectangleShape slowDownSquare(sf::Vector2f(30, 30));
                                slowDownSquare.setPosition(50, 200);
                                slowDownSquare.setFillColor(sf::Color::Yellow);

                                sf::Text pauseText("Pause (Vert)", font, 20);
                                pauseText.setPosition(100, 55);
                                pauseText.setFillColor(sf::Color::Black);

                                sf::Text quitText("Quitter (Rouge)", font, 20);
                                quitText.setPosition(100, 105);
                                quitText.setFillColor(sf::Color::Black);

                                sf::Text speedUpText("Augmenter la vitesse (Bleu)", font, 20);
                                speedUpText.setPosition(100, 155);
                                speedUpText.setFillColor(sf::Color::Black);

                                sf::Text slowDownText("Diminuer la vitesse (Jaune)", font, 20);
                                slowDownText.setPosition(100, 205);
                                slowDownText.setFillColor(sf::Color::Black);

                                // L�gende des cellules
                                sf::RectangleShape aliveSquare(sf::Vector2f(30, 30));
                                aliveSquare.setPosition(50, 270);
                                aliveSquare.setFillColor(sf::Color::Black);

                                sf::RectangleShape deadSquare(sf::Vector2f(30, 30));
                                deadSquare.setPosition(50, 320);
                                deadSquare.setFillColor(sf::Color::White);
                                deadSquare.setOutlineThickness(2);
                                deadSquare.setOutlineColor(sf::Color::Black);

                                sf::Text aliveText("Cellule vivante (Noir)", font, 20);
                                aliveText.setPosition(100, 275);
                                aliveText.setFillColor(sf::Color::Black);

                                sf::Text deadText("Cellule morte (Blanc)", font, 20);
                                deadText.setPosition(100, 325);
                                deadText.setFillColor(sf::Color::Black);

                                // Dessiner les �l�ments
                                infoWindow.draw(pauseSquare);
                                infoWindow.draw(quitSquare);
                                infoWindow.draw(speedUpSquare);
                                infoWindow.draw(slowDownSquare);
                                infoWindow.draw(pauseText);
                                infoWindow.draw(quitText);
                                infoWindow.draw(speedUpText);
                                infoWindow.draw(slowDownText);
                                infoWindow.draw(aliveSquare);
                                infoWindow.draw(deadSquare);
                                infoWindow.draw(aliveText);
                                infoWindow.draw(deadText);

                                infoWindow.display();
                            }
                        }
                    }
                }
            }

            // Dessiner les �l�ments du menu
            menuWindow.clear();
            menuWindow.draw(startButton);
            menuWindow.draw(startText);
            menuWindow.draw(infoButton);
            menuWindow.draw(infoText);
            menuWindow.draw(quitButton);
            menuWindow.draw(quitText);
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
