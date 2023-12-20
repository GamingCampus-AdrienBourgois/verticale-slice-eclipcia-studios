#pragma once
#include "Component.h"
#include "InputModule.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "RectangleShapeRenderer.h"
#include <iostream>
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

        if (InputModule::GetKey(sf::Keyboard::D) && canMoveRight)
        {
            position.x += speed * _delta_time;
        }
        if (InputModule::GetKey(sf::Keyboard::Q) && canMoveLeft)
        {
            position.x -= speed * _delta_time;
        }

        // Obtient tous les GameObjects nommés "Enemy"
        std::vector<GameObject*> enemies = GetEnemies();

        // Detecte si la touche d'attaque est appuyee
        if (InputModule::GetKeyDown(sf::Keyboard::Space))
        {
            
            // Parcourt tous les ennemis
            for (GameObject* enemy : enemies)
            {
                Maths::Vector2<float> enemyPosition = enemy->GetPosition();
                float distanceX = std::abs(position.x - enemyPosition.x);
                float distanceY = std::abs(position.y - enemyPosition.y);

                // Si la distance entre le joueur et l'ennemie est bonne, inflige des degats
                if (distanceX <= distanceThreshold && distanceY <= distanceThreshold)
                {
                    DealDamage(enemy);
                }
            }
            
        }

        // Gere les mouvements verticaux (gravite et sauts)
        velocity.y += gravity * _delta_time;

        if (InputModule::GetKey(sf::Keyboard::Z) && isGrounded)
        {
            velocity.y = -jumpForce;
        }

        position.y += velocity.y * _delta_time;

        const float windowWidth = 1920.0f;
        const float windowHeight = 1080.0f;
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

        // Parcourt tous les ennemis
        
        // Verifie s'il y a des collisions avec les ennemies
        if (CheckEnemyCollision(enemies))
        {
            for (GameObject* enemy : enemies)
            {

                Maths::Vector2<float> enemyPosition = enemy->GetPosition();

                // S'il y a collision, le joueur est pousse vers en arriere ou en avant en fonction de sa position par rapport a l'ennemi
                if (position.x > enemyPosition.x)
                {
                    position.x += pushBackAmount;
                    // Met le joueur à sa nouvelle position
                    GetOwner()->SetPosition(position);
                    // Inflige 10 de degats au joueur
                    enemy->GetComponent<Attack>()->Attacking(GetOwner());
                }
                else
                {
                    position.x -= pushBackAmount;
                    // Met le joueur à sa nouvelle position
                    GetOwner()->SetPosition(position);
                    // Inflige 10 de degats au joueur
                    enemy->GetComponent<Attack>()->Attacking(GetOwner());
                }

            }
            
        }

        CheckPlatformsCollisions();

        CheckGroundCollisions();        

        CheckDeath();

        // Met à jour la position du Sprite en se basant sur la position du joueur
        sprite.setPosition(GetOwner()->GetPosition().x, GetOwner()->GetPosition().y);

    }

    void Render(sf::RenderWindow* _window)  override
    {
        // Dessine le Sprite
        _window->draw(sprite);
    }

private:
    
    float speed = 300.0f; // Vitesse de deplacement
    float gravity = 2000.0f; // Gravite
    float jumpForce = 1100.0f; // Force de saut
    float pushBackAmount = 50.0f; // Distance auquel le joueur est repousse quand il y a contact avec un ennemi
    Maths::Vector2<float> velocity = { 0.0f, 0.0f }; // Velocite pour le saut et la gravite
    bool isGrounded = true; // Renvoie si le joueur touche le sol
    //bool isCollidingWithPlatform = false; // Renvoie si le joueur touche une plateforme
    bool attacking;
    const float distanceThreshold = 200.0f; // Distance maximale pour attaquer un ennemie
    bool canMoveLeft = true;
    bool canMoveRight = true;
   
    // Verifie les collisions avec les ennemies
    bool CheckEnemyCollision(std::vector<GameObject*> enemies)
    {
        for (GameObject* enemy : enemies)
        {
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
        return false;
    }

    // Fonction pour vérifier les collisions avec le sol ou les plateformes
    bool CheckGroundCollisions()
    {
        SquareCollider* playerCollider = GetOwner()->GetComponent<SquareCollider>();

        // Vérifier la collision avec le sol
        GameObject* ground = GetOwner()->GetScene()->FindGameObject("Ground");

        if (ground)
        {
            SquareCollider* groundCollider = ground->GetComponent<SquareCollider>();

            if (playerCollider && groundCollider && SquareCollider::IsColliding(*playerCollider, *groundCollider))
            {
                // Collision avec le sol
                velocity.y = 0.0f;
                isGrounded = true;
                //isCollidingWithPlatform = false; // Réinitialiser le drapeau de collision avec la plateforme
                return true;
            }
        }

        // Le joueur n'est pas en collision avec le sol ou une plateforme
        isGrounded = false;
        /*isCollidingWithPlatform = false;*/
        return false;
    }

    bool CheckPlatformsCollisions()
    {
        SquareCollider* playerCollider = GetOwner()->GetComponent<SquareCollider>();

        if (!playerCollider)
            return false;

        for (GameObject* platform : GetOwner()->GetScene()->GetGameObjects())
        {
            if (platform->GetName() == "Platform")
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
                        if (playerCollider->GetRight() > platformCollider->GetLeft())
                        {
                            canMoveRight = false;
                            return true;
                        }
                        else if (playerCollider->GetLeft() > platformCollider->GetRight())
                        {
                            canMoveLeft = false;
                            return true;
                        }
                    }
                    else
                    {
                        // Ajuster la position verticale
                        if (playerCollider->GetBottom() < platformCollider->GetTop())
                        {
                            /*GetOwner()->Move(0.0f, -overlapY);*/
                            velocity.y = 0.0f;  // Arrêter la chute si le joueur frappe le dessous de la plateforme
                            isGrounded = true;
                            /*isCollidingWithPlatform = true;*/
                        }
                        else
                        {
                            velocity.y = 0.0f;
                            /*GetOwner()->Move(0.0f, overlapY);*/
                        }
                    }
                }
            }
        }

        // Si le joueur n'est en collision avec aucune plateforme, mettre à jour le drapeau.

        isGrounded = false;
        canMoveLeft = true;
        canMoveRight = true;
        return false;


        // Réinitialiser le drapeau pour la prochaine itération.
    }







    // Fonction pour inflige des degats a l'ennemie
    void DealDamage(GameObject* enemy)
    {
        // ------------------------------------------------ Changer pour avoir l'ennemie le plus proche / ennemie vise ------------------------------------------------
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

    // Fonction pour obtenir tous les GameObjects nommés "Enemy" dans la scène
    std::vector<GameObject*> GetEnemies()
    {
        std::vector<GameObject*> enemies;

        for (GameObject* gameObject : GetOwner()->GetScene()->GetGameObjects())
        {
            if (gameObject->GetName() == "Enemy")
            {
                enemies.push_back(gameObject);
            }
        }

        return enemies;
    }

};