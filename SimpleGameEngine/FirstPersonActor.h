#pragma once
#include "Camera.h"
#include "AABBColliderComponent.h"

class RigidBodyComponent;
class HealthComponent;
class HealthBarComponent;

class FirstPersonActor : public Camera
{
public:
    FirstPersonActor(Scene* scene);
    ~FirstPersonActor() override = default;

    bool TakeDamage(int amount);
    HealthComponent* GetHealthComponent() const { return mHealthComponent; }


private:
    AABBColliderComponent* mCollider;
    RigidBodyComponent* mRigidBody;
    HealthComponent* mHealthComponent;
    HealthBarComponent* mHealthBarComponent;

    void SetupCollisionCallbacks();
    void HandleDeath();
};



