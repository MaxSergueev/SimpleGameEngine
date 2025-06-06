#pragma once
#include <vector>
#include "Bullet.h"
#include "Vector3.h"

class Scene;

/**
 * @brief Object pool manager for bullet projectiles to optimize performance
 *
 * BulletPool implements the object pool design pattern for bullet management,
 * pre-allocating a fixed number of bullet objects to avoid runtime allocation
 * and deallocation costs. It provides efficient bullet firing by reusing
 * inactive bullets in a round-robin fashion, significantly improving performance
 * in scenarios with frequent projectile creation.
 */
class BulletPool
{
public:
    /**
     * @brief Constructs bullet pool with specified capacity
     * @param scene Pointer to the scene that will contain the bullets
     * @param poolSize Number of bullets to pre-allocate (default: 50)
     */
    BulletPool(Scene* scene, int poolSize = 50);

    /**
     * @brief Destructor - bullets are cleaned up by the scene
     */
    ~BulletPool();

    /**
     * @brief Fires a bullet from the pool if one is available
     * @param startPos Starting position for the bullet
     * @param direction Normalized direction vector for bullet travel
     * @param shooter Actor that fired the bullet (won't be damaged by it)
     * @param speed Movement speed in units per second (default: 500.0f)
     * @return True if bullet was successfully fired, false if pool is exhausted
     */
    bool FireBullet(const Vector3& startPos, const Vector3& direction, Actor* shooter, float speed = 500.0f);

    /**
     * @brief Updates all active bullets in the pool
     * @note Currently unused as bullets update themselves through the scene
     */
    void Update();

    /**
     * @brief Gets the number of currently active bullets
     * @return Count of bullets that are currently in flight
     */
    int GetActiveBulletCount() const;

private:
    std::vector<Bullet*> mBullets;  ///< Pre-allocated bullet objects
    Scene* mScene;                  ///< Scene containing the bullets
    int mPoolSize;                  ///< Total number of bullets in pool
    int mNextBulletIndex;           ///< Index for round-robin bullet selection

    /**
     * @brief Finds the next available inactive bullet in the pool
     * @return Pointer to available bullet, or nullptr if pool is exhausted
     */
    Bullet* GetAvailableBullet();
};
