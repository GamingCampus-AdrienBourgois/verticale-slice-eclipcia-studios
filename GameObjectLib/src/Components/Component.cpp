#include "Components/Component.h"

Component::Component(GameObject* owner)
{
	this->owner = owner;
}

void Component::Update(float dt) {}

void Component::Render(sf::RenderWindow* _window) {}
