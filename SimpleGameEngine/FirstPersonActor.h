#pragma once
#include "Camera.h"
#include "AABBColliderComponent.h"

class RigidBodyComponent;
class HealthComponent;
class HealthBarComponent;
class BulletPool;

/**
 * @brief First-person player character with camera, physics, health, and combat
 *
 * FirstPersonActor extends Camera to provide a complete first-person player
 * implementation with rigid body physics, health management, visual health bar,
 * collision handling, and shooting capabilities.
 */
class FirstPersonActor : public Camera
{
public:
    /**
     * @brief Constructs a first-person actor with all necessary components
     * @param scene The scene to add this actor to
     * @param bulletPool Bullet pool for shooting functionality (optional)
     */
    FirstPersonActor(Scene* scene, BulletPool* bulletPool = nullptr);

    /**
     * @brief Default destructor
     */
    ~FirstPersonActor() override = default;

    /**
     * @brief Applies damage to the player
     * @param amount The amount of damage to apply
     * @return True if the player is still alive after taking damage
     */
    bool TakeDamage(int amount);

    /**
     * @brief Gets the player's health component
     * @return Pointer to the health component
     */
    HealthComponent* GetHealthComponent() const { return mHealthComponent; }

    /**
     * @brief Fires a bullet in the camera's forward direction
     */
    void Shoot();

    /**
     * @brief Sets the bullet pool for shooting functionality
     * @param bulletPool The bullet pool to use for shooting
     */
    void SetBulletPool(BulletPool* bulletPool) { mBulletPool = bulletPool; }

private:
    AABBColliderComponent* mCollider;       ///< Collision detection component
    RigidBodyComponent* mRigidBody;         ///< Physics and movement component
    HealthComponent* mHealthComponent;      ///< Health and damage management
    HealthBarComponent* mHealthBarComponent; ///< Visual health bar display
    BulletPool* mBulletPool;                ///< Reference to bullet pool for shooting

    /**
     * @brief Configures collision callbacks for physics resolution
     */
    void SetupCollisionCallbacks();

    /**
     * @brief Handles player death event
     */
    void HandleDeath();
};