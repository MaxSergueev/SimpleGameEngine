#pragma once
#include "Camera.h"
#include "AABBColliderComponent.h"

class RigidBodyComponent;
class HealthComponent;
class HealthBarComponent;
class BulletPool;

class FirstPersonActor : public Camera
{
public:
    FirstPersonActor(Scene* scene, BulletPool* bulletPool = nullptr);
    ~FirstPersonActor() override = default;

    bool TakeDamage(int amount);
    HealthComponent* GetHealthComponent() const { return mHealthComponent; }

    void Shoot();
    void SetBulletPool(BulletPool* bulletPool) { mBulletPool = bulletPool; }

private:
    AABBColliderComponent* mCollider;
    RigidBodyComponent* mRigidBody;
    HealthComponent* mHealthComponent;
    HealthBarComponent* mHealthBarComponent;
    BulletPool* mBulletPool;

    void SetupCollisionCallbacks();
    void HandleDeath();
};



