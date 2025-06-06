#pragma once
#include "Component.h"
#include "Vector3.h"
#include <string>

class Actor;
class HealthComponent;
class SpriteComponent;

/**
 * @brief Visual health bar component that displays health status
 *
 * HealthBarComponent creates a visual representation of an actor's health
 * using two sprite actors (background and foreground). The foreground
 * sprite scales dynamically based on the current health percentage.
 */
class HealthBarComponent : public Component
{
public:
    /**
     * @brief Constructs a health bar component
     * @param pOwner The actor that owns this component
     * @param updateOrder Component update priority (default: 200)
     */
    HealthBarComponent(Actor* pOwner, int updateOrder = 200);

    /**
     * @brief Destructor - cleans up health bar actors
     */
    ~HealthBarComponent() override;

    /**
     * @brief Updates the health bar visual based on current health
     */
    void Update() override;

    /**
     * @brief Sets the health component to monitor for health changes
     * @param healthComponent The health component to track
     */
    void SetHealthComponent(HealthComponent* healthComponent) { mHealthComponent = healthComponent; }

    /**
     * @brief Sets the position of the health bar in world space
     * @param position The new position for the health bar
     */
    void SetPosition(const Vector3& position);

    /**
     * @brief Sets the size dimensions of the health bar
     * @param size The new size for the health bar
     */
    void SetSize(const Vector3& size);

    /**
     * @brief Sets the texture for the health bar background
     * @param textureName Name of the texture asset to use
     */
    void SetBackgroundTexture(const std::string& textureName);

    /**
     * @brief Sets the texture for the health bar foreground
     * @param textureName Name of the texture asset to use
     */
    void SetForegroundTexture(const std::string& textureName);

private:
    HealthComponent* mHealthComponent;      ///< Health component being monitored

    Actor* mBackgroundActor;               ///< Actor for the background sprite
    Actor* mForegroundActor;               ///< Actor for the foreground sprite

    SpriteComponent* mBackgroundSprite;    ///< Background sprite component
    SpriteComponent* mForegroundSprite;    ///< Foreground sprite component

    Vector3 mPosition;                     ///< Current position of the health bar
    Vector3 mSize;                         ///< Current size of the health bar

    float mInitialWidth;                   ///< Original width for scaling calculations
};
