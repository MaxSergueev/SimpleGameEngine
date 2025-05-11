#include "FirstPersonActor.h"
#include "FPSController.h"
#include "Scene.h"
#include "RigidBodyComponent.h"

FirstPersonActor::FirstPersonActor(Scene* scene)
    : Camera()
{
    scene->AddActor(this);

    mRigidBody = new RigidBodyComponent(this);

    mCollider = GetComponentOfType<AABBColliderComponent>();

    SetupCollisionCallbacks();

    FPSController* controller = new FPSController(this);
    controller->OnStart();
}

void FirstPersonActor::SetupCollisionCallbacks()
{
    mCollider->SetOnCollisionEnter([this](AABBColliderComponent* other) {
        // Use rigid body physics to resolve the collision
        mRigidBody->ResolveCollision(other);
        });

    mCollider->SetOnCollisionStay([this](AABBColliderComponent* other) {
        // Continue to resolve the collision while in contact
        mRigidBody->ResolveCollision(other);
        });
}




