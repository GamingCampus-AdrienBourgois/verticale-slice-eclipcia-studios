#pragma once
#include "Component.h"
#include "InputModule.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "RectangleShapeRenderer.h"
#include <iostream>
#include <RectangleShapeRenderer.h>
#include "Attack.h"


class Player : public Component
{

public:

	sf::Texture texture;
	sf::Sprite sprite;
	SpriteRenderer* spriteRenderer = nullptr;
    void Start() override
    {    }

    void Update(const float _delta_time) override
    {

        Maths::Vector2<float> position = GetOwner()->GetPosition();

        if (InputModule::GetKey(sf::Keyboard::D))
        {
            position.x += speed * _delta_time;
        }
        if (InputModule::GetKey(sf::Keyboard::Q))
        {
            position.x -= speed * _delta_time;
        }
        if (InputModule::GetKeyDown(sf::Keyboard::Space))
        {
            DealDamage();
        }

        // Handle vertical movement (gravity and jumping)
        velocity.y += gravity * _delta_time;

        if (InputModule::GetKey(sf::Keyboard::Z) && isGrounded)
        {
            velocity.y = -jumpForce;
        }

        position.y += velocity.y * _delta_time;

        const float windowWidth = 1600.0f;
        const float windowHeight = 800.0f;
        // Ajuster la position horizontale
        if (position.x < 0.0f)
        {
            position.x = 0.0f;
        }
        else if (position.x + GetOwner()->GetComponent<SquareCollider>()->GetWidth() > windowWidth)
        {
            position.x = windowWidth - GetOwner()->GetComponent<SquareCollider>()->GetWidth();
        }

        // Ajuster la position verticale
        if (position.y < 0.0f)
        {
            position.y = 0.0f;
            velocity.y = 0.0f;  // Arrêter la chute si le joueur atteint le haut de la fenêtre
        }

        GetOwner()->SetPosition(position);

        if (CheckEnemyCollision())
        {
            // If there is a collision with the enemy, push the player a bit
            position.x += pushBackAmount;
            GetOwner()->SetPosition(position);
            GetOwner()->GetComponent<Health>()->TakeDamage(10);
        }

        CheckGroundCollisions();
        CheckEnemyCollision();

        CheckDeath();

        // Update the sprite position based on the player's position
        sprite.setPosition(GetOwner()->GetPosition().x, GetOwner()->GetPosition().y);

        //HandlePlatformCollisions();
    }

    void Render(sf::RenderWindow* _window)  override
    {
        // Replace this with your actual rendering code
        _window->draw(sprite);
    }

private:
    
    float speed = 200.0f;
    float gravity = 670.0f;
    float jumpForce = 670.0f;
    float pushBackAmount = 200.0f;
    Maths::Vector2<float> velocity = { 0.0f, 0.0f };
    bool isGrounded = true;
    bool isCollidingWithPlatform = false;
   

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
        for (GameObject* platform : GetOwner()->GetScene()->GetGameObjects())
        {
            if (platform->GetName().find("Platform") != std::string::npos)
            {
                SquareCollider* squareColliderPlatform = platform->GetComponent<SquareCollider>();
                if (squareColliderA && squareColliderPlatform && SquareCollider::IsColliding(*squareColliderA, *squareColliderPlatform))
                {
                    // Player is colliding with a platform
                    float newY = platform->GetPosition().y - squareColliderPlatform->GetHeight() / 2.0f - squareColliderA->GetHeight() / 2.0f;
                    velocity.y = 0.0f;
                    isGrounded = true;
                    return true;
                }
            }
        }
        // Le joueur n'est pas en collision avec le sol
        isGrounded = false;
        return false;
    }

    bool CheckEnemyCollision()
    {
        GameObject* enemy = GetOwner()->GetScene()->FindGameObject("Enemy");

        if (enemy)
        {
            SquareCollider* squareColliderPlayer = GetOwner()->GetComponent<SquareCollider>();
            SquareCollider* squareColliderEnemy = enemy->GetComponent<SquareCollider>();

            if (squareColliderPlayer && squareColliderEnemy && SquareCollider::IsColliding(*squareColliderPlayer, *squareColliderEnemy))
            {
                // Collision detected with enemy, take appropriate action
                return true; // Shutdown the game (replace this with your actual shutdown logic)
            }
        }
    }

    void HandlePlatformCollisions()
    {
        SquareCollider* playerCollider = GetOwner()->GetComponent<SquareCollider>();

        if (!playerCollider)
            return;

        for (GameObject* platform : GetOwner()->GetScene()->GetGameObjects())
        {
            if (platform->GetName().find("Platform") != std::string::npos)
            {
                SquareCollider* platformCollider = platform->GetComponent<SquareCollider>();

                if (platformCollider && SquareCollider::IsColliding(*playerCollider, *platformCollider))
                {
                    // Collision détectée avec une plateforme, ajuster la position du joueur
                    float overlapX = std::min(playerCollider->GetRight(), platformCollider->GetRight()) - std::max(playerCollider->GetLeft(), platformCollider->GetLeft());
                    float overlapY = std::min(playerCollider->GetBottom(), platformCollider->GetBottom()) - std::max(playerCollider->GetTop(), platformCollider->GetTop());

                    // Ajuster la position du joueur en fonction du chevauchement
                    if (overlapX < overlapY)
                    {
                        // Ajuster la position horizontale
                        if (playerCollider->GetLeft() < platformCollider->GetLeft())
                            GetOwner()->Move(-overlapX, 0.0f);
                        else
                            GetOwner()->Move(overlapX, 0.0f);
                    }
                    else
                    {
                        // Ajuster la position verticale
                        if (playerCollider->GetTop() < platformCollider->GetTop())
                        {
                            GetOwner()->Move(0.0f, -overlapY);
                            velocity.y = 0.0f;  // Arrêter la chute si le joueur frappe le dessous de la plateforme
                            isGrounded = true;
                            isCollidingWithPlatform = true;
                        }
                        else
                        {
                            GetOwner()->Move(0.0f, overlapY);
                        }
                    }
                }
            }
        }

        // Si le joueur n'est en collision avec aucune plateforme, mettre à jour le drapeau.
        if (!isCollidingWithPlatform)
        {
            isGrounded = false;
        }

        // Réinitialiser le drapeau pour la prochaine itération.
    }

    bool attacking;

    void DealDamage()
    {
        GameObject* enemy = GetOwner()->GetScene()->FindGameObject("Enemy");
        enemy->GetComponent<Health>()->TakeDamage(10);
    }

    // Vérifie la mort de l'ennemie
    void CheckDeath()
    {
        if (GetOwner()->GetComponent<Health>()->IsDead() == true)
        {
            GetOwner()->Destroy();
        }
    }

};