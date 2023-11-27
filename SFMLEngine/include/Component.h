#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"

class GameObject;

class Component
{
public:
	Component() = default;
	explicit Component(GameObject* _owner);
	virtual ~Component() = default;

	virtual void Update(float _delta_time);
	virtual void Render(sf::RenderWindow* _window);

	GameObject* GetOwner() const { return owner; }
	void SetOwner(GameObject* _owner) { owner = _owner; }

private:
	GameObject* owner = nullptr;
};
