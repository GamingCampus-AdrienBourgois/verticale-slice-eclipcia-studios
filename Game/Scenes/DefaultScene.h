#pragma once

#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "RectangleShapeRenderer.h"
#include "../SFMLEngine/src/Components/RectangleShapeRenderer.cpp"
#include "Scene.h"
#include "SquareCollider.h"


class DefaultScene final : public Scene
{
public:
    DefaultScene() : Scene("DefaultScene")
    {
        int frameCount = 8;
        int currentFrame = 0;
        sf::Clock animationClock;
        float frameDuration = 0.1f;

        // ------------------------------------------------------------------------------------------------
        /*GameObject*player = CreateGameObject("Player", 100, Maths::Vector2<float>(200.f, 200.f), Maths::Vector2<float>(50.f, 75.f), sf::Color::White, *this, "Assets/player.png", 1.0f, 1.0f);*/
        // ------------------------------------------------------------------------------------------------
        GameObject* player = CreateGameObject("Player", 100, 10.0f, Maths::Vector2<float>(200.f, 200.f), Maths::Vector2<float>(50.f, 75.f), sf::Color::White, *this, "Assets/player1.png", 1.0f, 1.0f);
        player->CreateComponent<Player>();
        player->CreateComponent<SquareCollider>();

        GameObject* enemy1 = CreateGameObject("Enemy", 50, 10.0f, Maths::Vector2<float>(400.f, 400.f), Maths::Vector2<float>(100.f, 100.f), sf::Color::Red, *this, "Assets/boss1.png", 1.5f, 1.5f);
        enemy1->CreateComponent<Enemy>();

        GameObject* enemy2 = CreateGameObject("Enemy", 50, 10.0f, Maths::Vector2<float>(1600.f, 400.f), Maths::Vector2<float>(100.f, 100.f), sf::Color::Red, *this, "Assets/boss1.png", 1.5f, 1.5f);
        enemy2->CreateComponent<Enemy>();

        GameObject* enemy3 = CreateGameObject("Enemy", 50, 10.0f, Maths::Vector2<float>(1200.f, 400.f), Maths::Vector2<float>(100.f, 100.f), sf::Color::Red, *this, "Assets/boss1.png", 1.5f, 1.5f);
        enemy3->CreateComponent<Enemy>();

        GameObject* ground = CreatePlatformObject("Ground", Maths::Vector2<float>(0.f, 750.f), Maths::Vector2<float>(1800.f, 60.f), sf::Color(0, 0, 0, 0), *this);
        ground->CreateComponent<SquareCollider>();

        CreateGroundPlatforms();
        // Créer les murs

        // ----------------------------------------------------------------------------------------------------------------------------
        // Mise à jour de l'animation
        //if (animationClock.getElapsedTime().asSeconds() > frameDuration)
        //{
        //    // Passage à la frame suivante
        //    currentFrame = (currentFrame + 1) % frameCount;
        //    frameRect.left = currentFrame * 32; // Ajustez 32 en fonction de la largeur de chaque image
        //    sprite.setTextureRect(frameRect);

        //    // Réinitialisation de l'horloge
        //    animationClock.restart();
        //}
        // ----------------------------------------------------------------------------------------------------------------------------

    }
private:
    void CreateGroundPlatforms()
    {
        // Définir les positions spécifiques pour chaque plateforme
        std::vector<Maths::Vector2<float>> platformPositions = {
            Maths::Vector2<float>(230.f, 420.f),
            Maths::Vector2<float>(700.f, 360.f),
            Maths::Vector2<float>(1180.f, 435.f)/*,
            Maths::Vector2<float>(900.f, 350.f),
            Maths::Vector2<float>(1100.f, 300.f),
            Maths::Vector2<float>(1300.f, 450.f)*/
        };

        // Créer 6 instances de la plateforme ("Platform") aux positions spécifiées
        for (size_t i = 0; i < platformPositions.size(); ++i)
        {
            std::string platformName = "Platform" + std::to_string(i + 1);
            Maths::Vector2<float> platformPosition = platformPositions[i];

            GameObject* platform = CreateGroundPlatform(platformName, platformPosition, Maths::Vector2<float>(185.f, 60.f), sf::Color(0, 0, 0, 0));
            platform->CreateComponent<SquareCollider>();
        }
    }

    GameObject* CreateGroundPlatform(const std::string& name, const Maths::Vector2<float>& position, const Maths::Vector2<float>& size, const sf::Color& color)
    {
        GameObject* platform = CreateGameObject2(name, 0, position, size, color, *this);
        platform->CreateComponent<SquareCollider>();
        return platform;
    }
};

