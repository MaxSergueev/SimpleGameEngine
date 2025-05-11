#pragma once
#include "Camera.h"
#include "AABBColliderComponent.h"

class RigidBodyComponent;

class FirstPersonActor : public Camera
{
public:
    FirstPersonActor(Scene* scene);
    ~FirstPersonActor() override = default;

private:
    AABBColliderComponent* mCollider;
    RigidBodyComponent* mRigidBody;

    void SetupCollisionCallbacks();
};



