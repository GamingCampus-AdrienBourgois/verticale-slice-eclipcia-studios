#include "Attack.h"

Attack::Attack(float damageAmount, float multiplierAmount) : damageAmount(damageAmount), damageMultiplier(multiplierAmount), defaultDamageAmount(damageAmount){}

// Met les degats par defaut
void Attack::SetDefaultDamage(float defaultDamage)
{
    damageAmount = defaultDamage;
}

// Met a jour le nombre de degats
void Attack::SetCurrentDamage(float newDamage)
{
    damageAmount = newDamage;
}

// Met a jour le multiplicateur de degats
void Attack::SetDamageMultiplier(float newMultiplier)
{
    damageMultiplier = newMultiplier;
}

// Recupere le nombre de degats actuel et le renvoie
float Attack::GetCurrentDamage() const
{
    return damageAmount;
}

// Recupere le multiplicateur de degats actuel et le renvoie
float Attack::GetCurrentMultiplier() const
{
    return damageMultiplier;
}

// Met a jour le nombre de degats en fonction du multiplicateur de degats
void Attack::MultiplyDamage(float multiplierAmount)
{
    damageAmount *= multiplierAmount;
}

// Inflige des degats au GameObject cible(ennemie), l'ennemie peut etre le joueur ou un ennemie
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
