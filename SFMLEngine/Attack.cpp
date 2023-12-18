#include "Attack.h"

Attack::Attack(int damageAmount, float multiplierAmount) : damageAmount(damageAmount), multiplierAmount(multiplierAmount), defaultDamageAmount(damageAmount){}

void Attack::SetDefaultDamage(int defaultDamage)
{
    damageAmount = defaultDamage;
}

int Attack::GetCurrentDamage() const
{
    return damageAmount;
}

float Attack::GetCurrentMultiplier() const
{
    return multiplierAmount;
}

void Attack::MultiplyDamage(float multiplierAmount)
{
    damageAmount *= multiplierAmount;
}

void Attack::Attacking(GameObject* enemy)
{
    enemy->GetComponent<Health>()->TakeDamage(damageAmount);
}







void Attack::Update(float deltaTime)
{
    if (isSwinging)
    {
        // Logique de l'animation de balancement de l'épée
        // Par exemple, vous pourriez changer la position de l'épée pour simuler un balancement.
    }
}

void Attack::Swing()
{
    isSwinging = true;

    // Logique supplémentaire pour gérer le balancement de l'épée
}
