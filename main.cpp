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

    if (choice == 2) {
        // Mode Graphique
        int iterationSpeed = 200; // Vitesse initiale (en ms)
        bool isPaused = false;   // État de pause

        // Fenêtre de Menu
        sf::RenderWindow menuWindow(sf::VideoMode(800, 600), "Menu - Jeu de la Vie");

        // Charger la police
        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\MSI 2023\\OneDrive - Association Cesi Viacesi mail\\Bureau\\AGENCYB.TTF")) {
            std::cerr << "Erreur : Impossible de charger la police.\n";
            return 1;
        }

        // Création des boutons
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
                            std::cout << "Démarrage de la simulation...\n";
                            startClicked = true; // Fermer la fenêtre menu et lancer la simulation
                        }
                        else if (quitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            menuWindow.close(); // Quitter le jeu
                            return 0;
                        }
                        else if (infoButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            // Afficher la fenêtre d'informations
                            sf::RenderWindow infoWindow(sf::VideoMode(600, 400), "À propos du Jeu de la Vie");

                            while (infoWindow.isOpen()) {
                                sf::Event infoEvent;
                                while (infoWindow.pollEvent(infoEvent)) {
                                    if (infoEvent.type == sf::Event::Closed) {
                                        infoWindow.close();
                                    }
                                }

                                infoWindow.clear(sf::Color::White);

                                sf::Text infoText1("Le Jeu de la Vie est une simulation", font, 20);
                                infoText1.setPosition(50, 50);
                                infoText1.setFillColor(sf::Color::Black);

                                sf::Text infoText2("inventee par John Conway.", font, 20);
                                infoText2.setPosition(50, 100);
                                infoText2.setFillColor(sf::Color::Black);

                                sf::Text infoText3("Chaque cellule vit, meurt ou se reproduit", font, 20);
                                infoText3.setPosition(50, 150);
                                infoText3.setFillColor(sf::Color::Black);

                                sf::Text infoText4("selon ses voisins.", font, 20);
                                infoText4.setPosition(50, 200);
                                infoText4.setFillColor(sf::Color::Black);

                                infoWindow.draw(infoText1);
                                infoWindow.draw(infoText2);
                                infoWindow.draw(infoText3);
                                infoWindow.draw(infoText4);

                                infoWindow.display();
                            }
                        }
                    }
                }
            }

            // Dessiner les éléments du menu
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
            // Créer et afficher la fenêtre de simulation après avoir cliqué sur Start
            sf::RenderWindow window(sf::VideoMode(800, 600), "Jeu de la Vie - Mode Graphique");

            GraphicView* graphicView = new GraphicView(width, height, 20, iterationSpeed);
            game.setView(graphicView);

            // Boucle principale pour les itérations graphiques
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

            delete graphicView; // Libérer la mémoire après la simulation
        }
    }

    return 0;
}
