#include "HealthComponent.h"
#include "Actor.h"

HealthComponent::HealthComponent(Actor* pOwner, int maxHealth, int updateOrder)
    : Component(pOwner, updateOrder),
    mHealth(maxHealth),
    mMaxHealth(maxHealth),
    mOnDamageCallback(nullptr),
    mOnDeathCallback(nullptr)
{
}

bool HealthComponent::TakeDamage(int amount)
{
    if (amount < 0) amount = 0;

    mHealth -= amount;

    if (mHealth < 0) mHealth = 0;

    if (mOnDamageCallback) {
        mOnDamageCallback(amount);
    }

    if (mHealth <= 0 && mOnDeathCallback)
    {
        mOnDeathCallback();
        return false;
    }

    return true;
}

void HealthComponent::Heal(int amount)
{
    if (amount < 0) amount = 0;

    mHealth += amount;

    if (mHealth > mMaxHealth) mHealth = mMaxHealth;
}
