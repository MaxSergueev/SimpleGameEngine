#include "FirstPersonActor.h"
#include "FPSController.h"
#include "Scene.h"
#include "RigidBodyComponent.h"
#include "HealthComponent.h"
#include "HealthBarComponent.h"
#include "BulletPool.h"
#include "Log.h"

FirstPersonActor::FirstPersonActor(Scene* scene, BulletPool* bulletPool)
    : Camera(), mBulletPool(bulletPool)
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

void FirstPersonActor::Shoot()
{
    if (!mBulletPool) {
        Log::Info("Player has no bullet pool - cannot shoot");
        return;
    }

    // Get shooting position (camera position)
    Vector3 shootPos = GetTransform().GetPosition();

    // Get shooting direction (camera forward direction)
    Vector3 shootDirection = GetTransform().Forward();

    // Fire bullet
    if (mBulletPool->FireBullet(shootPos, shootDirection, this, 400.0f))
    {
        Log::Info("Player fired bullet!");
    }
    else
    {
        Log::Info("No bullets available in pool!");
    }
}

void FirstPersonActor::SetupCollisionCallbacks()
{
    mCollider->SetOnCollisionEnter([this](AABBColliderComponent* other) {
        // Only resolve collision if the other object is not a trigger
        if (!other->IsTrigger()) {
            mRigidBody->ResolveCollision(other);
        }
        });

    mCollider->SetOnCollisionStay([this](AABBColliderComponent* other) {
        // Only resolve collision if the other object is not a trigger
        if (!other->IsTrigger()) {
            mRigidBody->ResolveCollision(other);
        }
        });
}

void FirstPersonActor::HandleDeath()
{
    Log::Info("Player died!");
}



