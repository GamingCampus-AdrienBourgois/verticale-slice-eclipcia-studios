#pragma once

#include "Component.h"

class Health : public Component
{
public:
    // Constructeur par défaut
    Health() : maxHealth(100), currentHealth(100) {}

    Health(int maxHealth);

    void SetDefaultHealth(int defaultHealth);
    void TakeDamage(int damage);
    void Heal(int heal);
    int GetCurrentHealth() const;
    int GetMaxHealth() const;
    bool IsDead() const;

private:
    int maxHealth;
    int currentHealth;
};
