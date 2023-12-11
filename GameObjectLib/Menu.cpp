#include "Menu.h"
#include "Scene.h"

Menu::Menu(sf::RenderWindow& window) : window(window)
{
    if (!font.loadFromFile("assets/PressStart2P.ttf"))
    {
        // G�rez l'erreur si la police ne peut pas �tre charg�e
    }

    if (!backgroundTexture.loadFromFile("assets/background.gif"))
    {
        // G�rer l'erreur si la texture du fond ne peut pas �tre charg�e
    }

    int buttonWidth = 200;
    int buttonHeight = 50;
    int buttonSpacing = 20;

    playText.setFont(font);
    playText.setString("Jouer");
    playText.setCharacterSize(20);
    playText.setFillColor(sf::Color::Red);
    playText.setPosition(100, 100);

    optionsText.setFont(font);
    optionsText.setString("Options");
    optionsText.setCharacterSize(20);
    optionsText.setFillColor(sf::Color::Blue);
    optionsText.setPosition(100, 100 + buttonHeight + buttonSpacing);

    creditsText.setFont(font);
    creditsText.setString("Cr�dits");
    creditsText.setCharacterSize(20);
    creditsText.setFillColor(sf::Color::Yellow);
    creditsText.setPosition(100, 100 + 2 * (buttonHeight + buttonSpacing));

    quitText.setFont(font);
    quitText.setString("Quitter");
    quitText.setCharacterSize(20);
    quitText.setFillColor(sf::Color::Green);
    quitText.setPosition(100, 100 + 3 * (buttonHeight + buttonSpacing));

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);
}

Menu::~Menu()
{
    // Lib�rez les ressources si n�cessaire
}

int Menu::run()
{
    while (window.isOpen())
    {
        handleInput();
        draw();
    }

    // Retournez la s�lection du joueur (1 pour Jouer, 2 pour Options, 3 pour Cr�dits, 4 pour Quitter)
    return 0; // Mettez la valeur appropri�e
}

void Menu::draw()
{
    window.clear();

    // Dessinez le fond du menu
    window.draw(backgroundSprite);

    // Dessinez tous les �l�ments du menu
    window.draw(playText);
    window.draw(optionsText);
    window.draw(creditsText);
    window.draw(quitText);

    window.display();
}

void Menu::handleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (playText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    // Le joueur a cliqu� avec le bouton gauche sur "Jouer", d�marrer le jeu
                    Scene scene;
                    scene.Run(window);
                }
                // Ajoutez des conditions similaires pour les autres options (Options, Cr�dits, etc.)
            }
        }
    }
}
