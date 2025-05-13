#pragma once
#include "Camera.h"
#include "AABBColliderComponent.h"

class RigidBodyComponent;
class HealthComponent;

class FirstPersonActor : public Camera
{
public:
    FirstPersonActor(Scene* scene);
    ~FirstPersonActor() override = default;

    bool TakeDamage(int amount);

private:
    AABBColliderComponent* mCollider;
    RigidBodyComponent* mRigidBody;
    HealthComponent* mHealthComponent;

    HealthComponent* GetHealthComponent() const { return mHealthComponent; }

    void SetupCollisionCallbacks();
    void HandleDeath();
};



