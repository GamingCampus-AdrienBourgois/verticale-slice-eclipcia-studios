#pragma once
#include "Components/SquareCollider.h"
#include "Component.h"
#include "Components/Health.h"

class Attack : public Component
{
public:

    Attack() : damageAmount(100), damageMultiplier(1.0f), defaultDamageAmount(100){}
    Attack(float damageAmount, float multiplierAmount);

    void SetDefaultDamage(float defaultDamage);
    void SetCurrentDamage(float newDamage);
    void SetDamageMultiplier(float newMultiplier);
    float GetCurrentDamage() const;
    float GetCurrentMultiplier() const;
    void MultiplyDamage(float damageMultiplier);
    void Attacking(GameObject* enemy);



    void Update(float deltaTime) override;
    void Swing();

private:
    bool isSwinging = false;
    float swingDuration = 0.5f; // Durée de l'animation de balancement de l'épée
    int damageAmount;
    float defaultDamageAmount;
    float damageMultiplier;
};
