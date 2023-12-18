#pragma once
#include "Components/SquareCollider.h"
#include "Component.h"
#include "Components/Health.h"

class Attack : public Component
{
public:

    Attack() : damageAmount(100), multiplierAmount(1.0f), defaultDamageAmount(100){}
    Attack(int damageAmount, float multiplierAmount);

    void SetDefaultDamage(int defaultDamage);
    int GetCurrentDamage() const;
    float GetCurrentMultiplier() const;
    void MultiplyDamage(float multiplierAmount);
    void Attacking(GameObject* enemy);



    void Update(float deltaTime) override;
    void Swing();

private:
    bool isSwinging = false;
    float swingDuration = 0.5f; // Durée de l'animation de balancement de l'épée
    int damageAmount;
    int defaultDamageAmount;
    float multiplierAmount;
};
