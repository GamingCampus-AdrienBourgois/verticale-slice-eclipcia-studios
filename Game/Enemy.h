#pragma once
#include "Component.h"
#include "InputModule.h"
#include "Projectile.h"

class Enemy : public Component
{
public:
	
	
	void Update(const float _delta_time) override
	{
		GameObject* player = GetOwner()->GetScene()->FindGameObject("Player");

		Maths::Vector2<float> enemyPosition = GetOwner()->GetPosition();

		Maths::Vector2<float> playerPosition = player->GetPosition();

		float positionDif = playerPosition.x - enemyPosition.x;

		if (playerPosition.x < enemyPosition.x)
		{
			enemyPosition.x -= speed * _delta_time;
		}
		if (playerPosition.x > enemyPosition.x)
		{
			enemyPosition.x += speed * _delta_time;
		}
		// Handle vertical movement (gravity and jumping)
		velocity.y += gravity * _delta_time; // Apply gravity

		//if (InputModule::GetKey(sf::Keyboard::Z) && isGrounded)
		//{
		//	velocity.y = -jumpForce;
		//}

		enemyPosition.y += velocity.y * _delta_time;

		GetOwner()->SetPosition(enemyPosition);

		CheckGroundCollisions();
		CheckPlayerCollision();


	}


private:
	
	float shootTimer;
	std::vector<GameObject*> projectiles;
	float speed = 120.0f;
	float gravity = 500.0f;

	Maths::Vector2<float> velocity = { 0.0f, 0.0f };
	bool isGrounded = true;

	// Function to check collisions with the ground
	bool CheckGroundCollisions()
	{
		SquareCollider* squareColliderA = GetOwner()->GetComponent<SquareCollider>();

		GameObject* ground = GetOwner()->GetScene()->FindGameObject("Ground");

		if (ground)
		{
			SquareCollider* squareColliderB = ground->GetComponent<SquareCollider>();

			if (squareColliderA && squareColliderB && SquareCollider::IsColliding(*squareColliderA, *squareColliderB))
			{
				// Le joueur est en collision avec le sol

				// Calculer la position de contact sur le sol
				float newY = ground->GetPosition().y - squareColliderB->GetHeight() / 2.0f - squareColliderA->GetHeight() / 2.0f;

				// Arrête la chute
				velocity.y = 0.0f;

				// Le joueur est maintenant considéré comme étant sur le sol
				isGrounded = true;

				return true;
			}
		}

		// Le joueur n'est pas en collision avec le sol
		isGrounded = false;
		return false;
	}
	void CheckPlayerCollision()
	{
		GameObject* player = GetOwner()->GetScene()->FindGameObject("Player");

		if (player)
		{
			SquareCollider* squareColliderEnemy = GetOwner()->GetComponent<SquareCollider>();
			SquareCollider* squareColliderPlayer = player->GetComponent<SquareCollider>();

			if (squareColliderEnemy && squareColliderPlayer && SquareCollider::IsColliding(*squareColliderEnemy, *squareColliderPlayer))
			{
				// Collision detected with player, take appropriate action
				GetOwner()->GetScene()->Shutdown(); // Shutdown the game (replace this with your actual shutdown logic)
			}
		}
	}

};
