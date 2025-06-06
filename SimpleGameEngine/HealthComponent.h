#pragma once
#include "Component.h"
#include <functional>

/**
 * @brief Component that manages actor health, damage, and healing
 *
 * HealthComponent provides health management functionality including damage
 * application, healing, death detection, and customizable callbacks for
 * damage and death events. It maintains current and maximum health values.
 */
class HealthComponent : public Component
{
public:
    /**
     * @brief Constructs a health component with specified maximum health
     * @param pOwner The actor that owns this component
     * @param maxHealth Maximum health value (default: 100)
     * @param updateOrder Component update priority (default: 100)
     */
    HealthComponent(Actor* pOwner, int maxHealth = 100, int updateOrder = 100);

    /**
     * @brief Default destructor
     */
    ~HealthComponent() override = default;

    /**
     * @brief Gets the current health value
     * @return Current health points
     */
    int GetHealth() const { return mHealth; }

    /**
     * @brief Gets the maximum health value
     * @return Maximum health points
     */
    int GetMaxHealth() const { return mMaxHealth; }

    /**
     * @brief Gets the current health as a percentage of maximum
     * @return Health percentage (0.0 to 1.0)
     */
    float GetHealthPercentage() const { return static_cast<float>(mHealth) / mMaxHealth; }

    /**
     * @brief Checks if the actor is still alive
     * @return True if health is greater than 0
     */
    bool IsAlive() const { return mHealth > 0; }

    /**
     * @brief Applies damage to the actor
     * @param amount The amount of damage to apply (negative values ignored)
     * @return True if the actor is still alive after taking damage
     */
    bool TakeDamage(int amount);

    /**
     * @brief Heals the actor by the specified amount
     * @param amount The amount of health to restore (negative values ignored)
     */
    void Heal(int amount);

    /**
     * @brief Resets health to maximum value
     */
    void ResetHealth() { mHealth = mMaxHealth; }

    /**
     * @brief Sets callback function for damage events
     * @param callback Function to call when damage is taken (receives damage amount)
     */
    void SetOnDamageCallback(std::function<void(int)> callback) { mOnDamageCallback = callback; }

    /**
     * @brief Sets callback function for death events
     * @param callback Function to call when health reaches 0
     */
    void SetOnDeathCallback(std::function<void()> callback) { mOnDeathCallback = callback; }

private:
    int mHealth;                            ///< Current health points
    int mMaxHealth;                         ///< Maximum health points

    std::function<void(int)> mOnDamageCallback;  ///< Callback for damage events
    std::function<void()> mOnDeathCallback;      ///< Callback for death events
};
