#pragma once
#include <string>
#include <vector>

#include "Component.h"
#include "Maths/Vector2.h"

class Component;

class GameObject
{
public:
	GameObject() = default;
	~GameObject();

	std::string GetName() const { return name; }
	Maths::Vector2<float> GetPosition() const { return position; }
	float GetRotation() const { return rotation; }
	Maths::Vector2<float> GetScale() const { return scale; }

	void SetName(const std::string& _name) { name = _name; }
	void SetPosition(const Maths::Vector2<float>& _position) { position = _position; }
	void SetRotation(const float _rotation) { rotation = _rotation; }
	void SetScale(const Maths::Vector2<float>& _scale) { scale = _scale; }

	template<typename T>
	T* CreateComponent();

	template<typename T>
	T* GetComponent();

	void AddComponent(Component* _component);
	void RemoveComponent(Component* _component);

	void Update(float _delta_time) const;
	void Render(sf::RenderWindow* _window) const;

private:
	std::string name = "GameObject";

	Maths::Vector2<float> position = Maths::Vector2f::Zero;
	float rotation = 0.0f;
	Maths::Vector2<float> scale = Maths::Vector2f::One;

	std::vector<Component*> components;
};

template<typename T>
T* GameObject::CreateComponent()
{
	T* component = new T();
	component->SetOwner(this);
	components.push_back(component);
	return component;
}

template<typename T>
T* GameObject::GetComponent()
{
	for (Component* component : components)
	{
		T* result = dynamic_cast<T*>(component);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}
