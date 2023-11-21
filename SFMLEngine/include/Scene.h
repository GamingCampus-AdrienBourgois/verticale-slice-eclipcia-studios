#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"

class Scene
{
public:
	explicit Scene(const std::string& _name);
	virtual ~Scene() = default;

	void Update(float _delta_time) const;

	void Render(sf::RenderWindow* _window) const;

	std::string GetName() const;

	GameObject* CreateGameObject(const std::string& _name);

private:
	std::string name;
	std::vector<GameObject*> gameObjects;
};
