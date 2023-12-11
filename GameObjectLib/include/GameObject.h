#pragma once
#include <string>
#include <vector>

#include "Maths/Vector2.h"
#include "Components/Component.h"

class Component;

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	std::string GetName() const { return name; }
	Maths::Vector2<float> GetPosition() const { return position; }

	void SetName(const std::string& _name) { name = _name; }
	void SetPosition(const Maths::Vector2<float>& _position) { position = _position; }

	void AddComponent(Component* _component);

	template<typename T>
	T* CreateComponent()
	{
		T* component = new T();
		component->SetOwner(this);
		components.push_back(component);
		return component;
	}

	template<typename T>
	T* GetComponent()
	{
		for (Component* component : components) {
			T* typedComponent = dynamic_cast<T*>(component);
			if (typedComponent != nullptr) {
				return typedComponent;
			}
		}
		return nullptr;
	}

	void SetVelocity(const Maths::Vector2f& _velocity) { velocity = _velocity; }

	void Move(const Maths::Vector2f& offset) { position += offset; }

	void SetMoveRight(bool state);

	void SetMoveLeft(bool state);

	void SetMoveUp(bool state);

	void SetMoveDown(bool state);

	void UpdateVelocity();

	void Jump();

	void SetGrounded(bool grounded) { isGrounded = grounded; }

	void SetGravity(float value) { gravity = value; }

	void Update(float dt, int windowHeight);

	void RemoveComponent(Component* _component);
	void Update(float dt, int windowHeight) const;
	void Render(sf::RenderWindow* _window) const;


private:
	std::string name = "GameObject";
	Maths::Vector2<float> position = Maths::Vector2f::Zero;
	std::vector<Component*> components;
	Maths::Vector2f velocity;
	bool moveRight, moveLeft, moveUp, moveDown, isJumping, isGrounded;
	float groundLevel; // Ajouter la position du sol (ajuster en fonction de votre jeu)
	float gravity = 500.0f;          // Ajustez la valeur en fonction de la gravité souhaitée
	float jumpSpeed = 200.0f;        // Ajustez la valeur en fonction de la vitesse de saut souhaitée
	float maxFallSpeed = 500.0f;      // Ajustez la valeur en fonction de la vitesse maximale de chute souhaitée
	float maxHorizontalSpeed = 200.0f; // Ajustez la valeur en fonction de la vitesse horizontale maximale souhaitée
};
