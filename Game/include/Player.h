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

        Maths::Vector2<float> enemyPosition = GetOwner()->GetScene()->FindGameObject("Enemy")->GetPosition();

        if (InputModule::GetKey(sf::Keyboard::D))
        {
            position.x += speed * _delta_time;
        }
        if (InputModule::GetKey(sf::Keyboard::Q))
        {
            position.x -= speed * _delta_time;
        }

        // Detecte si la touche d'attaque est appuyee
        if (InputModule::GetKeyDown(sf::Keyboard::Space))
        {
            const float distanceThreshold = 200.0f; // Distance souhaitée

            float distanceX = std::abs(position.x - enemyPosition.x);
            float distanceY = std::abs(position.y - enemyPosition.y);

            // Si la distance entre le joueur et l'ennemie est bonne, inflige des degats
            if (distanceX <= distanceThreshold && distanceY <= distanceThreshold)
            {
                DealDamage();
            }
        }

        // Gere les mouvements verticaux (gravite et sauts)
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

        // Verifie s'il y a des collisions avec les ennemies
        if (CheckEnemyCollision())
        {
            // S'il y a collision, le joueur est pousse vers en arriere ou en avant en fonction de sa position par rapport a l'ennemi
            if (position.x > enemyPosition.x)
            {
                position.x += pushBackAmount;
            }
            else
            {
                position.x -= pushBackAmount;
            }
            
            // Met le joueur à sa nouvelle position
            GetOwner()->SetPosition(position);

            // ------------------------------------------------ Changer pour avoir l'ennemie le plus proche / ennemie vise ------------------------------------------------
            GameObject* enemy = GetOwner()->GetScene()->FindGameObject("Enemy");

            // Inflige 10 de degats au joueur
            enemy->GetComponent<Attack>()->Attacking(GetOwner());
        }

        CheckGroundCollisions();
        CheckEnemyCollision();

        CheckDeath();

        // Met à jour la position du Sprite en se basant sur la position du joueur
        sprite.setPosition(GetOwner()->GetPosition().x, GetOwner()->GetPosition().y);

        //HandlePlatformCollisions();
    }

    void Render(sf::RenderWindow* _window)  override
    {
        // Dessine le Sprite
        _window->draw(sprite);
    }

private:
    
    float speed = 200.0f; // Vitesse de deplacement
    float gravity = 670.0f; // Gravite
    float jumpForce = 670.0f; // Force de saut
    float pushBackAmount = 200.0f; // Distance auquel le joueur est repousse quand il y a contact avec un ennemi
    Maths::Vector2<float> velocity = { 0.0f, 0.0f }; // Velocite pour le saut et la gravite
    bool isGrounded = true; // Renvoie si le joueur touche le sol
    bool isCollidingWithPlatform = false; // Renvoie si le joueur touche une plateforme
    bool attacking;
   
    // Fonction pour verifier les collisions avec le sol
    bool CheckGroundCollisions()
    {
        SquareCollider* squareColliderA = GetOwner()->GetComponent<SquareCollider>();

        GameObject* ground = GetOwner()->GetScene()->FindGameObject("Ground");

        if (ground)
        {
            SquareCollider* squareColliderB = ground->GetComponent<SquareCollider>();

            // Teste si le joueur est en collision avec le sol
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
        // Parcourt toutes les Object de la scene
        for (GameObject* platform : GetOwner()->GetScene()->GetGameObjects())
        {
            // Verifie si l'object est une plateforme
            if (platform->GetName().find("Platform") != std::string::npos)
            {
                SquareCollider* squareColliderPlatform = platform->GetComponent<SquareCollider>();
                if (squareColliderA && squareColliderPlatform && SquareCollider::IsColliding(*squareColliderA, *squareColliderPlatform))
                {
                    // Le joueur est en collision avec la plateforme
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

    // Verifie les collisions avec les ennemies
    bool CheckEnemyCollision()
    {
        GameObject* enemy = GetOwner()->GetScene()->FindGameObject("Enemy");

        // Verifie s'il y a un ennemie
        if (enemy)
        {
            SquareCollider* squareColliderPlayer = GetOwner()->GetComponent<SquareCollider>();
            SquareCollider* squareColliderEnemy = enemy->GetComponent<SquareCollider>();

            // Verifie si le joueur et l'ennemie sont en collision
            if (squareColliderPlayer && squareColliderEnemy && SquareCollider::IsColliding(*squareColliderPlayer, *squareColliderEnemy))
            {
                return true;
            }
        }
    }

    // ---------------- A REFAIRE ---------------- A REFAIRE ---------------- A REFAIRE ---------------- A REFAIRE ---------------- A REFAIRE ---------------- A REFAIRE ----------------
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

    // Fonction pour inflige des degats a l'ennemie
    void DealDamage()
    {
        // ------------------------------------------------ Changer pour avoir l'ennemie le plus proche / ennemie vise ------------------------------------------------
        GameObject* enemy = GetOwner()->GetScene()->FindGameObject("Enemy");
        GetOwner()->GetComponent<Attack>()->Attacking(enemy);
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