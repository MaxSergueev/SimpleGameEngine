#pragma once
#include "Component.h"
#include <functional>

class HealthComponent : public Component
{
public:
    HealthComponent(Actor* pOwner, int maxHealth = 100, int updateOrder = 100);
    ~HealthComponent() override = default;

    // Health-related methods
    int GetHealth() const { return mHealth; }
    int GetMaxHealth() const { return mMaxHealth; }
    float GetHealthPercentage() const { return static_cast<float>(mHealth) / mMaxHealth; }
    bool IsAlive() const { return mHealth > 0; }

    // Take damage and return true if still alive after damage
    bool TakeDamage(int amount);

    // Heal the actor
    void Heal(int amount);

    // Reset health to max
    void ResetHealth() { mHealth = mMaxHealth; }

    // Callback setters
    void SetOnDamageCallback(std::function<void(int)> callback) { mOnDamageCallback = callback; }
    void SetOnDeathCallback(std::function<void()> callback) { mOnDeathCallback = callback; }

private:
    int mHealth;
    int mMaxHealth;

    // Callbacks for damage and death events
    std::function<void(int)> mOnDamageCallback;
    std::function<void()> mOnDeathCallback;
};

