#pragma once
#include "Actor.h"
#include "Vector3.h"

class MeshComponent;
class AABBColliderComponent;
class HealthComponent;
class BulletPool;
class FirstPersonActor;

/**
 * @brief AI-controlled enemy actor with patrol and combat behavior
 *
 * Enemy provides basic AI functionality including patrol movement,
 * line-of-sight detection, shooting at players, and health management.
 * Enemies can be configured with different patrol patterns and combat parameters.
 */
class Enemy : public Actor
{
public:
    /**
     * @brief Constructs an enemy with specified position and bullet pool
     * @param scene The scene to add this enemy to
     * @param position Initial world position for the enemy
     * @param bulletPool Bullet pool for shooting (optional)
     */
    Enemy(class Scene* scene, const Vector3& position, BulletPool* bulletPool = nullptr);

    /**
     * @brief Default destructor
     */
    ~Enemy() override = default;

    /**
     * @brief Updates enemy AI behavior including patrol and combat
     */
    void UpdateActor() override;

    /**
     * @brief Applies damage to the enemy
     * @param amount The amount of damage to apply
     * @return True if the enemy is still alive after taking damage
     */
    bool TakeDamage(int amount);

    /**
     * @brief Gets the enemy's collision component
     * @return Pointer to the AABB collider component
     */
    AABBColliderComponent* GetCollider() const { return mCollider; }

    /**
     * @brief Gets the enemy's health component
     * @return Pointer to the health component
     */
    HealthComponent* GetHealthComponent() const { return mHealthComponent; }

    /**
     * @brief Sets the patrol movement direction
     * @param direction The new patrol direction vector
     */
    void SetPatrolDirection(const Vector3& direction) { mPatrolDirection = direction; }

private:
    MeshComponent* mMeshComponent;          ///< Visual mesh representation
    AABBColliderComponent* mCollider;       ///< Collision detection component
    HealthComponent* mHealthComponent;      ///< Health and damage management

    float mMovementSpeed;                   ///< Movement speed in units per second
    Vector3 mPatrolDirection;               ///< Current patrol movement direction

    float mPatrolCounter;                   ///< Distance traveled in current patrol direction
    float mPatrolDistance;                  ///< Maximum distance to travel before turning around

    BulletPool* mBulletPool;                ///< Reference to bullet pool for shooting
    float mShootTimer;                      ///< Time since last shot
    float mShootCooldown;                   ///< Minimum time between shots
    float mShootRange;                      ///< Maximum shooting range

    /**
     * @brief Initializes collision detection and callbacks
     */
    void SetupCollision();

    /**
     * @brief Handles enemy death by deactivating and moving out of bounds
     */
    void HandleDeath();

    /**
     * @brief Updates shooting behavior and timer
     */
    void UpdateShooting();

    /**
     * @brief Checks if the enemy can shoot at the player
     * @return True if player is in range and line of sight is clear
     */
    bool CanShootAtPlayer();

    /**
     * @brief Fires a bullet at the player with random miss chance
     */
    void ShootAtPlayer();

    /**
     * @brief Finds the active player in the scene
     * @return Pointer to the player actor, or nullptr if not found
     */
    FirstPersonActor* FindPlayer();
};


