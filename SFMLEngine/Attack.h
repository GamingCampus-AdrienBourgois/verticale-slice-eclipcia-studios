#pragma once
#include "Components/SquareCollider.h"
#include "Component.h"

class Sword : public Component
{
public:
    void Update(float deltaTime) override;
    void Swing();

private:
    bool isSwinging = false;
    float swingDuration = 0.5f; // Durée de l'animation de balancement de l'épée
};
