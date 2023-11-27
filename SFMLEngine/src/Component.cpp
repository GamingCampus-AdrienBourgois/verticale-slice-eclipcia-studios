#include "Component.h"

Component::Component(GameObject* _owner)
{
	this->owner = _owner;
}

void Component::Update(float _delta_time) {}

void Component::Render(sf::RenderWindow* _window) {}
