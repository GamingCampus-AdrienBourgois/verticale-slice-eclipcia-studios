#include "GameObject.h"

void GameObject::AddComponent(Component* _component)
{
	_component->SetOwner(this);
	components.push_back(_component);
}

void GameObject::RemoveComponent(Component* _component)
{
	components.erase(std::remove(components.begin(), components.end(), _component), components.end());
}

void GameObject::Update(float dt, int windowHeight) const
{
	for (Component* const& component : components)
	{
		component->Update(dt);
	}
}

void GameObject::Render(sf::RenderWindow* _window) const
{
	for (Component* const& component : components)
	{
		component->Render(_window);
	}
}

void GameObject::SetMoveRight(bool state)
{
	moveRight = state;
	UpdateVelocity();
}

void GameObject::SetMoveLeft(bool state)
{
	moveLeft = state;
	UpdateVelocity();
}

void GameObject::SetMoveUp(bool state)
{
	moveUp = state;
	UpdateVelocity();
}

void GameObject::SetMoveDown(bool state)
{
	moveDown = state;
	UpdateVelocity();
}

void GameObject::UpdateVelocity()
{
	float horizontalVelocity = (moveRight ? 10.f : 0.f) - (moveLeft ? 10.f : 0.f);
	velocity.x = horizontalVelocity * 100.f;

	// Ne modifiez la v�locit� verticale que si le saut n'est pas en cours
	if (!isJumping)
	{
		float verticalVelocity = (moveDown ? 1.f : 0.f) - (moveUp ? 1.f : 0.f);
		velocity.y = verticalVelocity * 100.f;
	}

	// Si aucune touche de mouvement n'est enfonc�e, r�initialisez la v�locit� � z�ro
	if (!moveRight && !moveLeft && !moveDown && !moveUp)
	{
		velocity = Maths::Vector2f(0.f, velocity.y);
	}
}

void GameObject::Jump()
{
	// V�rifier si l'objet est au sol et ne saute pas d�j�
	if (isGrounded && !isJumping)
	{
		velocity.y = -jumpSpeed; // Ajustez la valeur en fonction de la hauteur du saut souhait�e
		isGrounded = false; // Marquer l'objet comme �tant en l'air apr�s le saut
		isJumping = true; // Indiquer que le saut est en cours
	}
}

void GameObject::Update(float dt, int windowHeight)
{
	// Appliquer la gravit�
	velocity.y += gravity * dt;

	// Mise � jour de la position en fonction de la v�locit�
	position += velocity * dt;

	// Mise � jour de isGrounded (l'objet est au sol si sa position est en bas de la fen�tre)
	isGrounded = (position.y >= windowHeight - 65.f); // Assurez-vous d'ajuster en fonction de la taille de votre objet

	// R�initialiser isJumping si l'objet est au sol
	if (isGrounded)
	{
		position.y = windowHeight - 65.f; // Ajustez la position pour rester au sol
		velocity.y = 0.0f; // Arr�ter le mouvement vertical lorsque l'objet est au sol
		isJumping = false; // R�initialiser l'�tat de saut
	}


	// Restreindre la vitesse de chute maximale
	if (velocity.y > maxFallSpeed)
	{
		velocity.y = maxFallSpeed;
	}

	// Restreindre la vitesse horizontale
	if (velocity.x > maxHorizontalSpeed)
	{
		velocity.x = maxHorizontalSpeed;
	}
	else if (velocity.x < -maxHorizontalSpeed)
	{
		velocity.x = -maxHorizontalSpeed;
	}
}