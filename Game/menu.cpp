// Menu.cpp
#include "Menu.h"
#include "game.cpp"

Menu::Menu() {
  
    

    if (!font.loadFromFile("Musicals.ttf")) {
        // Gestion des erreurs si la police ne peut pas être chargée
    }

    if (!backgroundTexture.loadFromFile("../Assets/menu_fond.jpg"))
    {
        // Gestion des erreurs si l'image ne peut pas être chargée
        // 
        //IMAGE A CHANGER DANS LE FICHIER ASSET CAR ELLE EST CORROMPUE!!!!!!

    }

    titleText.setFont(font);
    titleText.setString("MUSE BLAST");
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::Black);
    sf::FloatRect titleBounds = titleText.getLocalBounds();

    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(24);
    playText.setFillColor(sf::Color::White);

    optionsText.setFont(font);
    optionsText.setString("Options");
    optionsText.setCharacterSize(24);
    optionsText.setFillColor(sf::Color::White);

    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(24);
    quitText.setFillColor(sf::Color::White);

    playButton.setPosition(
        playButton.getPosition().x + 825.0f, // Position horizontale du bouton
        playButton.getPosition().y + 450.0f // Verticale
    );

    // Bouton Play
    playButton.setSize(sf::Vector2f(250.0f, 50.0f));
    playButton.setFillColor(sf::Color::Black);


    // Bouton Options
    optionsButton.setSize(sf::Vector2f(250.0f, 50.0f));
    optionsButton.setFillColor(sf::Color::Black); // Set the color you desire

    // Bouton Quit
    quitButton.setSize(sf::Vector2f(250.0f, 50.0f));
    quitButton.setFillColor(sf::Color::Black); // Set the color you desire

    // Position du titre
    titleText.setPosition(
        (playButton.getPosition().x + (playButton.getSize().x - titleText.getLocalBounds().width) / 2.0f), 100.0f 
    );

    // Position du texte dans le bouton
    sf::FloatRect textBounds = playText.getLocalBounds();
    playText.setPosition(
        playButton.getPosition().x + (playButton.getSize().x - textBounds.width) / 2.0f,
        playButton.getPosition().y + (playButton.getSize().y - playText.getCharacterSize()) / 2.0f
    );

    // Position the new buttons
    optionsButton.setPosition(
        playButton.getPosition().x, // Same X position as the play button
        playButton.getPosition().y + 150.0f // Adjust Y position as needed
    );

    quitButton.setPosition(
        playButton.getPosition().x, // Same X position as the play button
        optionsButton.getPosition().y + 150.0f // Adjust Y position as needed
    );

    // Position the text in the new buttons
    sf::FloatRect optionsTextBounds = optionsText.getLocalBounds();
    optionsText.setPosition(
        optionsButton.getPosition().x + (optionsButton.getSize().x - optionsTextBounds.width) / 2.0f,
        optionsButton.getPosition().y + (optionsButton.getSize().y - optionsText.getCharacterSize()) / 2.0f
    );

    sf::FloatRect quitTextBounds = quitText.getLocalBounds();
    quitText.setPosition(
        quitButton.getPosition().x + (quitButton.getSize().x - quitTextBounds.width) / 2.0f,
        quitButton.getPosition().y + (quitButton.getSize().y - quitText.getCharacterSize()) / 2.0f
    );
}

Menu::~Menu() {
    // Libérez les ressources si nécessaire
}


void Menu::Show(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            HandleEvents(event, window);
        }

        window.clear();

        if (PlayState == false) {
            // Dessinez le fond d'écran
            sf::RectangleShape backgroundShape;


            backgroundShape.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
            backgroundShape.setTexture(&backgroundTexture);
            window.draw(backgroundShape);

            // Dessinez les éléments du menu
            window.draw(playButton);
            window.draw(playText);
            window.draw(titleText);

            window.draw(optionsButton);
            window.draw(optionsText);
            window.draw(quitButton);
            window.draw(quitText);

            window.display();
        }
    }
}

void Menu::HandleEvents(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        // Vérifiez si le clic de la souris est sur le bouton "Play"
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

        if (playButton.getGlobalBounds().contains(mousePositionF)) {
            // Le bouton "Play" a été cliqué, lancez le jeu
            PlayState = true;
            window.clear();
            window.display();
            Game::render();
            // Ne fermez pas la fenêtre ici, laissez la boucle principale gérer la fermeture
        }
    }
}