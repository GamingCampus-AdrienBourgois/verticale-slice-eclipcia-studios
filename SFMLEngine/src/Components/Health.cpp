#include "Components/Health.h"

Health::Health(int maxHealth) : maxHealth(maxHealth), currentHealth(maxHealth) {}

void Health::SetDefaultHealth(int defaultHealth)
{
    maxHealth = defaultHealth;
    currentHealth = defaultHealth;
}

void Health::TakeDamage(int damage)
{
    currentHealth -= damage;
    if (currentHealth < 0)
    {
        currentHealth = 0;
    }
}

void Health::Heal(int heal)
{
    currentHealth += heal;
    if (currentHealth > maxHealth)
    {
        currentHealth = maxHealth;
    }
}

int Health::GetCurrentHealth() const
{
    return currentHealth;
}

int Health::GetMaxHealth() const
{
    return maxHealth;
}

bool Health::IsDead() const
{
    if (currentHealth <= 0)
        return true;
    else
        return false;
}
