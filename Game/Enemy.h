#pragma once
#include "Component.h"
#include "InputModule.h"

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

		//CheckEnemyCollisions();
	}

private:

	float speed = 40.0f;
	float gravity = 500.0f;
	float jumpForce = 200.0f;
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

	//void CheckEnemyCollisions()
	//{
	//	SquareCollider* squareColliderA = GetOwner()->GetComponent<SquareCollider>();

	//	std::vector<GameObject*> enemies = GetOwner()->GetScene()->FindGameObject("Enemy");

	//	for (GameObject* enemy : enemies)
	//	{
	//		if (enemy != GetOwner()) // Avoid self-collision check
	//		{
	//			SquareCollider* squareColliderB = enemy->GetComponent<SquareCollider>();

	//			if (squareColliderA && squareColliderB && SquareCollider::IsColliding(*squareColliderA, *squareColliderB))
	//			{
	//				// Resolve the collision by pushing the enemies away from each other
	//				ResolveCollision(GetOwner(), enemy);
	//			}
	//		}
	//	}
	//}

	//void ResolveCollision(GameObject* objA, GameObject* objB)
	//{
	//	// Calculate the direction from objA to objB
	//	Maths::Vector2<float> collisionDir = objB->GetPosition() - objA->GetPosition();
	//	float distance = Maths::Vector2<float>::Magnitude(collisionDir);

	//	// Calculate the minimum translation distance needed to separate the objects
	//	float overlap = (objA->GetComponent<SquareCollider>()->GetWidth() + objB->GetComponent<SquareCollider>()->GetWidth()) - distance;

	//	// Normalize the collision direction
	//	collisionDir.Normalize();

	//	// Calculate the separation vector
	//	Maths::Vector2<float> separation = collisionDir * overlap * 0.5f;

	//	// Move the objects away from each other
	//	objA->SetPosition(objA->GetPosition() - separation);
	//	objB->SetPosition(objB->GetPosition() + separation);
	//}
};
