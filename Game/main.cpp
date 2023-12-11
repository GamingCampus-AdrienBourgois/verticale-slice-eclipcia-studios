#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameObject.h"
#include "Scene.h"

int main()
{
    Scene scene;

    GameObject* player = scene.CreateGameObject("Player", 200.f, 300.f, 20.f, 20.f, sf::Color::White);

    GameObject* enemy = scene.CreateGameObject("Enemy", 400.f, 500.f, 50.f, 50.f, sf::Color::Blue);

    GameObject* enemy2 = scene.CreateGameObject("Enemy", 500.f, 600.f, 25.f, 25.f, sf::Color::Blue);

    GameObject* enemy3 = scene.CreateGameObject("Enemy", 600.f, 700.f, 100.f, 100.f, sf::Color::Blue);

    GameObject* boss = scene.CreateBoss("Boss", 1140.f, 300.f, 200.f, 200.f, sf::Color::Red);

    int windowWidth = 1600;
    int windowHeight = 600;



    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Engine");
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/fond.jpg"))
    {
        // Gérer l'erreur si la texture du fond ne peut pas être chargée
        return 1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    float scaleX = static_cast<float>(windowWidth) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(windowHeight) / backgroundTexture.getSize().y;

    backgroundSprite.setScale(scaleX, scaleY);


    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::D)
                    player->SetMoveRight(true);
                else if (event.key.code == sf::Keyboard::Q)
                    player->SetMoveLeft(true);
                else if (event.key.code == sf::Keyboard::Z)
                    player->Jump(); // Appel à la fonction de saut
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::D)
                    player->SetMoveRight(false);
                else if (event.key.code == sf::Keyboard::Q)
                    player->SetMoveLeft(false);
            }
        }

        float dt = clock.restart().asSeconds();

        scene.Update(dt, windowHeight);
        window.clear(sf::Color::Black);
        window.draw(backgroundSprite);
        

        scene.Render(&window);
        window.display();
    }


    return 0;
}