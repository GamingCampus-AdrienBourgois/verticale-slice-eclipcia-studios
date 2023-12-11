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

	// Ne modifiez la vélocité verticale que si le saut n'est pas en cours
	if (!isJumping)
	{
		float verticalVelocity = (moveDown ? 1.f : 0.f) - (moveUp ? 1.f : 0.f);
		velocity.y = verticalVelocity * 100.f;
	}

	// Si aucune touche de mouvement n'est enfoncée, réinitialisez la vélocité à zéro
	if (!moveRight && !moveLeft && !moveDown && !moveUp)
	{
		velocity = Maths::Vector2f(0.f, velocity.y);
	}
}

void GameObject::Jump()
{
	// Vérifier si l'objet est au sol et ne saute pas déjà
	if (isGrounded && !isJumping)
	{
		velocity.y = -jumpSpeed; // Ajustez la valeur en fonction de la hauteur du saut souhaitée
		isGrounded = false; // Marquer l'objet comme étant en l'air après le saut
		isJumping = true; // Indiquer que le saut est en cours
	}
}

void GameObject::Update(float dt, int windowHeight)
{
	// Appliquer la gravité
	velocity.y += gravity * dt;

	// Mise à jour de la position en fonction de la vélocité
	position += velocity * dt;

	// Mise à jour de isGrounded (l'objet est au sol si sa position est en bas de la fenêtre)
	isGrounded = (position.y >= windowHeight - 65.f); // Assurez-vous d'ajuster en fonction de la taille de votre objet

	// Réinitialiser isJumping si l'objet est au sol
	if (isGrounded)
	{
		position.y = windowHeight - 65.f; // Ajustez la position pour rester au sol
		velocity.y = 0.0f; // Arrêter le mouvement vertical lorsque l'objet est au sol
		isJumping = false; // Réinitialiser l'état de saut
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