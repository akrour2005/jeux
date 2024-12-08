


#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "Game.h"
#include "ConsoleView.h"
#include "GraphicView.h"
#include <fstream>

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
        // R�pertoire pour sauvegarder les fichiers de sortie
        std::string outputDir = "C:\\Users\\MSI 2023\\jeux-de-la-vie\\jeux de la vie\\fichier_out\\";

        // Boucle principale du jeu en mode console
        for (int i = 0; i < maxIterations; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(iterationSpeed));  // Pause entre les it�rations
            game.updateGrid();
            std::cout << "It�ration " << i + 1 << " :\n";
            consoleView->display(*game.getGrid());

            // Sauvegarder l'�tat de la grille dans un fichier texte
            std::ofstream outFile(outputDir + "iteration_" + std::to_string(i + 1) + ".txt");
            if (outFile.is_open()) {
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        outFile << (game.getGrid()->getCellState(x, y) ? 'O' : '.'); // Par exemple : 'O' pour vivant, '.' pour mort
                    }
                    outFile << "\n";
                }
                outFile.close();
            }
            else {
                std::cerr << "Erreur : Impossible de sauvegarder l'it�ration " << i + 1 << ".\n";
            }
        }

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

                                // D�couper la fen�tre en deux parties
                                // Partie sup�rieure (r�gles du jeu)
                                sf::RectangleShape topSection(sf::Vector2f(600, 200)); // Partie haute
                                topSection.setPosition(0, 0);
                                topSection.setFillColor(sf::Color(220, 220, 220)); // Gris clair
                                infoWindow.draw(topSection);

                                // Partie inf�rieure (carr�s des cellules et commandes)
                                sf::RectangleShape bottomSection(sf::Vector2f(600, 200)); // Partie basse
                                bottomSection.setPosition(0, 200);
                                bottomSection.setFillColor(sf::Color(240, 240, 240)); // Gris plus clair
                                infoWindow.draw(bottomSection);

                                // Texte des r�gles du Jeu de la Vie (partie haute, centr�)
                                sf::Text rulesText("R�gles du Jeu de la Vie :\n\n"
                                    "1. Une cellule vivante avec moins de 2 voisins meurt.\n"
                                    "2. Une cellule vivante avec 2 ou 3 voisins reste vivante.\n"
                                    "3. Une cellule vivante avec plus de 3 voisins meurt.\n"
                                    "4. Une cellule morte avec exactement 3 voisins devient vivante.\n", font, 18);
                                rulesText.setPosition(150, 50); // Centrer le texte
                                rulesText.setFillColor(sf::Color::Black);
                                infoWindow.draw(rulesText);

                                // L�gende des cellules (partie basse - bas � gauche)
                                sf::RectangleShape aliveSquare(sf::Vector2f(30, 30));
                                aliveSquare.setPosition(50, 230); // Ajust� pour �tre un peu plus haut
                                aliveSquare.setFillColor(sf::Color::Black);

                                sf::RectangleShape deadSquare(sf::Vector2f(30, 30));
                                deadSquare.setPosition(50, 270); // Ajust� pour �tre un peu plus haut
                                deadSquare.setFillColor(sf::Color::White);
                                deadSquare.setOutlineThickness(2);
                                deadSquare.setOutlineColor(sf::Color::Black);

                                sf::Text aliveText("Cellule vivante (Noir)", font, 20);
                                aliveText.setPosition(90, 235); // Ajust� pour �tre plus haut
                                aliveText.setFillColor(sf::Color::Black);

                                sf::Text deadText("Cellule morte (Blanc)", font, 20);
                                deadText.setPosition(90, 275); // Ajust� pour �tre plus haut
                                deadText.setFillColor(sf::Color::Black);

                                // L�gende des commandes (partie basse - bas au centre)
                                sf::RectangleShape pauseSquare(sf::Vector2f(30, 30));
                                pauseSquare.setPosition(250, 230); // Ajust� pour se rapprocher du centre et plus haut
                                pauseSquare.setFillColor(sf::Color::Green);

                                sf::RectangleShape quitSquare(sf::Vector2f(30, 30));
                                quitSquare.setPosition(250, 270); // Ajust� pour se rapprocher du centre et plus haut
                                quitSquare.setFillColor(sf::Color::Red);

                                sf::RectangleShape speedUpSquare(sf::Vector2f(30, 30));
                                speedUpSquare.setPosition(250, 310); // Ajust� pour se rapprocher du centre et plus haut
                                speedUpSquare.setFillColor(sf::Color::Blue);

                                sf::RectangleShape slowDownSquare(sf::Vector2f(30, 30));
                                slowDownSquare.setPosition(250, 350); // Ajust� pour se rapprocher du centre et plus haut
                                slowDownSquare.setFillColor(sf::Color::Yellow);

                                sf::Text pauseText("Pause (Vert)", font, 20);
                                pauseText.setPosition(290, 235); // Ajust� pour se rapprocher du centre et plus haut
                                pauseText.setFillColor(sf::Color::Black);

                                sf::Text quitText("Quitter (Rouge)", font, 20);
                                quitText.setPosition(290, 275); // Ajust� pour se rapprocher du centre et plus haut
                                quitText.setFillColor(sf::Color::Black);

                                sf::Text speedUpText("Augmenter la vitesse (Bleu)", font, 20);
                                speedUpText.setPosition(290, 315); // Ajust� pour se rapprocher du centre et plus haut
                                speedUpText.setFillColor(sf::Color::Black);

                                sf::Text slowDownText("Diminuer la vitesse (Jaune)", font, 20);
                                slowDownText.setPosition(290, 355); // Ajust� pour se rapprocher du centre et plus haut
                                slowDownText.setFillColor(sf::Color::Black);

                                // Dessiner les �l�ments de la l�gende
                                infoWindow.draw(aliveSquare);
                                infoWindow.draw(deadSquare);
                                infoWindow.draw(aliveText);
                                infoWindow.draw(deadText);

                                infoWindow.draw(pauseSquare);
                                infoWindow.draw(quitSquare);
                                infoWindow.draw(speedUpSquare);
                                infoWindow.draw(slowDownSquare);
                                infoWindow.draw(pauseText);
                                infoWindow.draw(quitText);
                                infoWindow.draw(speedUpText);
                                infoWindow.draw(slowDownText);

                                // Afficher la fen�tre
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

            // Taille des boutons
            sf::Vector2f buttonSize(200, 50); // Taille plus grande pour les boutons

            // Positionner les boutons au centre de la fen�tre
            float windowWidth = window.getSize().x;
            float windowHeight = window.getSize().y;
            float buttonSpacing = 20; // Espace entre les boutons

            // Cr�ation des rectangles pour les boutons suppl�mentaires avec des tailles plus grandes
            sf::RectangleShape pauseSquare(buttonSize);
            pauseSquare.setPosition((windowWidth - buttonSize.x) / 2, (windowHeight - buttonSize.y) / 2 - 2 * (buttonSize.y + buttonSpacing));  // Position du bouton Pause
            pauseSquare.setFillColor(sf::Color::Green);

            sf::RectangleShape quitSquare(buttonSize);
            quitSquare.setPosition((windowWidth - buttonSize.x) / 2, (windowHeight - buttonSize.y) / 2 + buttonSpacing);  // Position du bouton Quitter
            quitSquare.setFillColor(sf::Color::Red);

            sf::RectangleShape speedUpSquare(buttonSize);
            speedUpSquare.setPosition((windowWidth - buttonSize.x) / 2, (windowHeight - buttonSize.y) / 2 + 2 * (buttonSize.y + buttonSpacing));  // Position du bouton Augmenter la vitesse
            speedUpSquare.setFillColor(sf::Color::Blue);

            sf::RectangleShape slowDownSquare(buttonSize);
            slowDownSquare.setPosition((windowWidth - buttonSize.x) / 2, (windowHeight - buttonSize.y) / 2 + 3 * (buttonSize.y + buttonSpacing));  // Position du bouton Diminuer la vitesse
            slowDownSquare.setFillColor(sf::Color::Yellow);

            // Texte pour les boutons
            sf::Text pauseText("Pause", font, 20);
            pauseText.setPosition(pauseSquare.getPosition() + sf::Vector2f((buttonSize.x - pauseText.getGlobalBounds().width) / 2, (buttonSize.y - pauseText.getGlobalBounds().height) / 2));
            pauseText.setFillColor(sf::Color::Black);

            sf::Text quitText("Quitter", font, 20);
            quitText.setPosition(quitSquare.getPosition() + sf::Vector2f((buttonSize.x - quitText.getGlobalBounds().width) / 2, (buttonSize.y - quitText.getGlobalBounds().height) / 2));
            quitText.setFillColor(sf::Color::Black);

            sf::Text speedUpText("Vitesse+", font, 20);
            speedUpText.setPosition(speedUpSquare.getPosition() + sf::Vector2f((buttonSize.x - speedUpText.getGlobalBounds().width) / 2, (buttonSize.y - speedUpText.getGlobalBounds().height) / 2));
            speedUpText.setFillColor(sf::Color::Black);

            sf::Text slowDownText("Vitesse-", font, 20);
            slowDownText.setPosition(slowDownSquare.getPosition() + sf::Vector2f((buttonSize.x - slowDownText.getGlobalBounds().width) / 2, (buttonSize.y - slowDownText.getGlobalBounds().height) / 2));
            slowDownText.setFillColor(sf::Color::Black);


            // Boucle principale pour les it�rations graphiques
            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    else if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            // V�rifier si l'un des boutons est cliqu�
                            if (pauseSquare.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                isPaused = !isPaused; // Mettre en pause ou reprendre
                            }
                            else if (quitSquare.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                window.close(); // Quitter la simulation
                            }
                            else if (speedUpSquare.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                iterationSpeed = std::max(50, iterationSpeed - 50); // Augmenter la vitesse
                            }
                            else if (slowDownSquare.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                iterationSpeed += 50; // Diminuer la vitesse
                            }
                        }
                    }
                    else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Up) {
                            iterationSpeed = std::max(50, iterationSpeed - 50); // Augmenter la vitesse
                        }
                        else if (event.key.code == sf::Keyboard::Down) {
                            iterationSpeed += 50; // Diminuer la vitesse
                        }
                        else if (event.key.code == sf::Keyboard::Space) {
                            isPaused = !isPaused; // Mettre en pause ou reprendre
                        }
                    }
                }

                if (!isPaused) {
                    game.updateGrid();
                    window.clear();
                    graphicView->display(*game.getGrid());

                    // Dessiner les boutons
                    window.draw(pauseSquare);
                    window.draw(quitSquare);
                    window.draw(speedUpSquare);
                    window.draw(slowDownSquare);
                    window.draw(pauseText);
                    window.draw(quitText);
                    window.draw(speedUpText);
                    window.draw(slowDownText);

                    window.display();
                    sf::sleep(sf::milliseconds(iterationSpeed)); // Attente en fonction de la vitesse
                }
            }

            delete graphicView; // Lib�rer la m�moire apr�s la simulation
        }

    }
    return 0;
}