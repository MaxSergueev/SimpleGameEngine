#pragma once
#include "Actor.h"
#include "Vector3.h"

class MeshComponent;
class AABBColliderComponent;
class HealthComponent;
class BulletPool;
class FirstPersonActor;

class Enemy : public Actor
{
public:
    Enemy(class Scene* scene, const Vector3& position, BulletPool* bulletPool = nullptr);
    ~Enemy() override = default;

    void UpdateActor() override;

    // Damage handling
    bool TakeDamage(int amount);

    // Getters
    AABBColliderComponent* GetCollider() const { return mCollider; }
    HealthComponent* GetHealthComponent() const { return mHealthComponent; }

    void SetPatrolDirection(const Vector3& direction) { mPatrolDirection = direction; }

private:
    // Components
    MeshComponent* mMeshComponent;
    AABBColliderComponent* mCollider;
    HealthComponent* mHealthComponent;

    // Enemy properties
    float mMovementSpeed;
    Vector3 mPatrolDirection;

    // Patrol behavior variables
    float mPatrolCounter;
    float mPatrolDistance;

    // Shooting properties
    BulletPool* mBulletPool;
    float mShootTimer;
    float mShootCooldown;
    float mShootRange;

    // Setup methods
    void SetupCollision();
    void HandleDeath();

    // Shooting methods
    void UpdateShooting();
    bool CanShootAtPlayer();
    void ShootAtPlayer();
    FirstPersonActor* FindPlayer();
};

