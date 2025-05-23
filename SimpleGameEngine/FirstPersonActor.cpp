#include "FirstPersonActor.h"
#include "FPSController.h"
#include "Scene.h"
#include "RigidBodyComponent.h"
#include "HealthComponent.h"
#include "HealthBarComponent.h"
#include "Log.h"

FirstPersonActor::FirstPersonActor(Scene* scene)
    : Camera()
{
    scene->AddActor(this);

    mRigidBody = new RigidBodyComponent(this);

    mHealthComponent = new HealthComponent(this, 100);

    mHealthComponent->SetOnDeathCallback([this]() {
        HandleDeath();
        });

    mHealthBarComponent = new HealthBarComponent(this);
    mHealthBarComponent->SetHealthComponent(mHealthComponent);
    mHealthBarComponent->SetPosition(Vector3(-5500, 4000, 9500));
    mHealthBarComponent->SetSize(Vector3(4, 0.5, 1));
    mHealthBarComponent->SetBackgroundTexture("purple");
    mHealthBarComponent->SetForegroundTexture("yellow");

    mCollider = GetComponentOfType<AABBColliderComponent>();

    SetupCollisionCallbacks();

    FPSController* controller = new FPSController(this);
    controller->OnStart();
}

bool FirstPersonActor::TakeDamage(int amount)
{
        return mHealthComponent->TakeDamage(amount);
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

void FirstPersonActor::HandleDeath()
{
    Log::Info("Player died!");
}





