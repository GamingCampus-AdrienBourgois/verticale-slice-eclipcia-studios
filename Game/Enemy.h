#pragma once
#include "Component.h"
#include "Projectile.h"
#include "include/Components/SquareCollider.h"

class Enemy : public Component
{
public:
	
	
	void Update(const float _delta_time) override
	{
		GameObject* player = GetOwner()->GetScene()->FindGameObject("Player");

		Maths::Vector2<float> enemyPosition = GetOwner()->GetPosition();

		Maths::Vector2<float> playerPosition = player->GetPosition();

		float positionDif = playerPosition.x - enemyPosition.x;

		// Verifie la position du joueur et met a jour la position de l'ennemie pour le suivre
		//if (playerPosition.x < enemyPosition.x)
		//{
		//	enemyPosition.x -= speed * _delta_time;
		//}
		//if (playerPosition.x > enemyPosition.x)
		//{
		//	enemyPosition.x += speed * _delta_time;
		//}

		// Calcule la velocite
		velocity.y += gravity * _delta_time;

		// Applique la gravité
		enemyPosition.y += velocity.y * _delta_time;

		GetOwner()->SetPosition(enemyPosition);

		CheckGroundCollisions();

		CheckDeath();

	}


private:
	
	float shootTimer;
	std::vector<GameObject*> projectiles;
	float speed = 100.0f; // Vitesse de deplacement
	float gravity = 2000.0f; // Gravite

	Maths::Vector2<float> velocity = { 0.0f, 0.0f };
	bool isGrounded = true; // Renvoie si l'ennemie touche le sol

	// Fonction pour verifier si l'ennemie touche le sol
	bool CheckGroundCollisions()
	{
		SquareCollider* squareColliderA = GetOwner()->GetComponent<SquareCollider>();

		GameObject* ground = GetOwner()->GetScene()->FindGameObject("Ground");

		if (ground)
		{
			SquareCollider* squareColliderB = ground->GetComponent<SquareCollider>();

			if (squareColliderA && squareColliderB && SquareCollider::IsColliding(*squareColliderA, *squareColliderB))
			{
				// Calcule la position de contact sur le sol
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

	// Vérifie la mort de l'ennemie
	void CheckDeath()
	{
		if (GetOwner()->GetComponent<Health>()->IsDead() == true)
		{
			// Detruit/Supprime l'ennemie s'il est mort
			GetOwner()->GetScene()->DestroyGameObject(GetOwner());
		}
	}

};
