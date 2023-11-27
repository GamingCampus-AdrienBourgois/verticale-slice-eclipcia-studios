#include "GameObject.h"

GameObject::~GameObject()
{
	for (Component*& component : components)
		delete component;

	components.clear();
}

void GameObject::AddComponent(Component* _component)
{
	_component->SetOwner(this);
	components.push_back(_component);
}

void GameObject::RemoveComponent(Component* _component)
{
	components.erase(std::remove(components.begin(), components.end(), _component), components.end());
}

void GameObject::Update(const float _delta_time) const
{
	for (Component* const& component : components)
	{
		component->Update(_delta_time);
	}
}

void GameObject::Render(sf::RenderWindow* _window) const
{
	for (Component* const& component : components)
	{
		component->Render(_window);
	}
}
