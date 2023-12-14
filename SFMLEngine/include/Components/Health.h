#pragma once

class Health
{
public:
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
