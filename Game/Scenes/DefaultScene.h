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
		GameObject* player = CreateGameObject("Player", Maths::Vector2<float>(200.f, 200.f), Maths::Vector2<float>(25.f, 10.f), sf::Color::Red, *this);
		player->CreateComponent<Player>();
		player->CreateComponent<SquareCollider>();

		GameObject* enemy = CreateGameObject("Enemy", Maths::Vector2<float>(400.f, 400.f), Maths::Vector2<float>(20.f, 20.f), sf::Color::Blue, *this);
		enemy->CreateComponent<Enemy>();

		GameObject* ground = CreateGameObject("Ground", Maths::Vector2<float>(0.f, 500.f), Maths::Vector2<float>(1000.f, 20.f), sf::Color::Green, *this);
		ground->CreateComponent<SquareCollider>();

	}

};
