#pragma once

#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "RectangleShapeRenderer.h"
#include "Scene.h"
#include "SquareCollider.h"

class DefaultScene final : public Scene
{
public:
	DefaultScene() : Scene("DefaultScene")
	{
		GameObject* player = CreateGameObject("Player", 100, Maths::Vector2<float>(200.f, 200.f), Maths::Vector2<float>(10.f, 25.f), sf::Color::White, *this);
		player->CreateComponent<Player>();
		player->CreateComponent<SquareCollider>();

		GameObject* enemy1 = CreateGameObject("Enemy", 50, Maths::Vector2<float>(400.f, 400.f), Maths::Vector2<float>(20.f, 20.f), sf::Color::Red, *this);
		enemy1->CreateComponent<Enemy>();

		GameObject* enemy2 = CreateGameObject("Enemy", 50, Maths::Vector2<float>(0.f, 400.f), Maths::Vector2<float>(20.f, 20.f), sf::Color::Red, *this);
		enemy2->CreateComponent<Enemy>();

		GameObject* ground = CreatePlatformObject("Ground", Maths::Vector2<float>(0.f, 500.f), Maths::Vector2<float>(1600.f, 20.f), sf::Color::Green, *this);
		ground->CreateComponent<SquareCollider>();

	}

};
