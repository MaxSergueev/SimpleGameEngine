#pragma once
#include "Actor.h"
#include "Vector3.h"

class MeshComponent;
class AABBColliderComponent;

/**
 * @brief Projectile actor for shooting mechanics in the game engine
 *
 * Bullet represents a projectile that can be fired by actors (players, enemies, etc.).
 * It handles movement, collision detection, damage dealing, and automatic cleanup
 * after a specified lifetime. Bullets are designed to be pooled for performance,
 * allowing reuse without constant allocation/deallocation. They automatically
 * detect hits against players, enemies, and solid objects.
 */
class Bullet : public Actor
{
public:
    /**
     * @brief Default constructor - creates an inactive bullet ready for pooling
     */
    Bullet();

    /**
     * @brief Default destructor
     */
    ~Bullet() override = default;

    /**
     * @brief Updates bullet movement and lifetime each frame
     */
    void UpdateActor() override;

    /**
     * @brief Initializes bullet for firing with specified parameters
     * @param startPos Starting position for the bullet
     * @param direction Normalized direction vector for bullet travel
     * @param shooter Actor that fired this bullet (won't be damaged by it)
     * @param speed Movement speed in units per second (default: 500.0f)
     */
    void Initialize(const Vector3& startPos, const Vector3& direction, Actor* shooter, float speed = 500.0f);

    /**
     * @brief Resets bullet state for reuse in object pool
     */
    void Reset();

    /**
     * @brief Checks if bullet is currently active and moving
     * @return True if bullet is active, false if available for reuse
     */
    bool IsActive() const { return mIsActive; }

    /**
     * @brief Gets the actor that fired this bullet
     * @return Pointer to the shooter actor, or nullptr if not set
     */
    Actor* GetShooter() const { return mShooter; }

private:
    MeshComponent* mMeshComponent;          ///< Visual representation of the bullet
    AABBColliderComponent* mCollider;       ///< Collision detection component

    Vector3 mDirection;     ///< Normalized movement direction
    float mSpeed;           ///< Movement speed in units per second
    float mLifetime;        ///< Time since bullet was fired
    float mMaxLifetime;     ///< Maximum time before auto-destruction
    bool mIsActive;         ///< Whether bullet is currently in use
    Actor* mShooter;        ///< Actor that fired this bullet

    /**
     * @brief Sets up collision detection and response callbacks
     */
    void SetupCollision();

    /**
     * @brief Handles collision with another object
     * @param other The collider component that was hit
     */
    void OnHit(AABBColliderComponent* other);

    /**
     * @brief Deactivates bullet and prepares it for pool reuse
     */
    void Deactivate();
};
