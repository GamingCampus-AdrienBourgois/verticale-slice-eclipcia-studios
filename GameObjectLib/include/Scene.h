#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	void Run(sf::RenderWindow& window);

	void Update(float dt, int windowHeight);
	void Render(sf::RenderWindow* _window);

	GameObject* CreateDummyGameObject(const std::string& _name);

	GameObject* CreateGameObject(const std::string& name, float x, float y, float width, float height, const sf::Color color);

	GameObject* CreateBoss(const std::string& name, float x, float y, float width, float height, const sf::Color color);

private:
	std::vector<GameObject*> gameObjects;
};
