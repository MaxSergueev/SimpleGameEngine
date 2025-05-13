#include "HealthComponent.h"
#include "Actor.h"
#include "Log.h"

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
    // Ensure damage is positive
    if (amount < 0) amount = 0;

    // Apply damage
    mHealth -= amount;

    // Clamp health to minimum of 0
    if (mHealth < 0) mHealth = 0;

    // Log damage taken
    Log::Info("Entity took " + std::to_string(amount) +
        " damage. Health: " + std::to_string(mHealth));

    // Call damage callback if set
    if (mOnDamageCallback) {
        mOnDamageCallback(amount);
    }

    // Check if actor died from this damage
    if (mHealth <= 0 && mOnDeathCallback)
    {
        mOnDeathCallback();
        return false;
    }

    return true;
}

void HealthComponent::Heal(int amount)
{
    // Ensure healing is positive
    if (amount < 0) amount = 0;

    // Apply healing
    mHealth += amount;

    // Clamp health to maximum
    if (mHealth > mMaxHealth) mHealth = mMaxHealth;

    Log::Info("Entity healed for " + std::to_string(amount) +
        ". Health: " + std::to_string(mHealth));
}

