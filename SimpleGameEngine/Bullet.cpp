#include "Bullet.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "AABBColliderComponent.h"
#include "Assets.h"
#include "Time.h"
#include "Log.h"
#include "FirstPersonActor.h"
#include "Enemy.h"

Bullet::Bullet()
    : Actor(),
    mMeshComponent(nullptr),
    mCollider(nullptr),
    mDirection(Vector3::zero),
    mSpeed(250.0f),
    mLifetime(0.0f),
    mMaxLifetime(5.0f),
    mIsActive(false),
    mShooter(nullptr)
{
    // Create mesh component (small sphere for bullet)
    mMeshComponent = new MeshComponent(this);
    mMeshComponent->SetMesh(Assets::GetMesh("bullet"));
    mMeshComponent->GetMesh()->SetTexture(&Assets::GetTexture("yellow"));

    // Small scale for bullet
    SetScale(Vector3(1.0f, 1.0f, 1.0f));

    // Setup collision
    SetupCollision();

    // Start inactive
    SetActive(false);
}

void Bullet::UpdateActor()
{
    if (!mIsActive) return;

    // Move bullet
    Vector3 currentPos = GetTransform().GetPosition();
    Vector3 movement = mDirection * mSpeed * Time::deltaTime;
    SetPosition(currentPos + movement);

    // Update lifetime
    mLifetime += Time::deltaTime;
    if (mLifetime >= mMaxLifetime)
    {
        Deactivate();
    }
}

void Bullet::Initialize(const Vector3& startPos, const Vector3& direction, Actor* shooter, float speed)
{
    SetPosition(startPos);
    mDirection = Vector3::Normalize(direction);
    mShooter = shooter;
    mSpeed = speed;
    mLifetime = 0.0f;
    mIsActive = true;

    SetActive(true);
    mCollider->SetActive(true);
}

void Bullet::Reset()
{
    mIsActive = false;
    mLifetime = 0.0f;
    mShooter = nullptr;
    mDirection = Vector3::zero;

    SetActive(false);
    mCollider->SetActive(false);

    // Move far away
    SetPosition(Vector3(10000, 10000, 10000));
}

void Bullet::SetupCollision()
{
    mCollider = new AABBColliderComponent(this);
    mCollider->SetDimensions(Vector3(2.0f, 2.0f, 2.0f)); // Small bullet collision

    // Make bullets triggers - they detect hits but don't cause physical collisions
    mCollider->SetTrigger(true);

    mCollider->SetOnCollisionEnter([this](AABBColliderComponent* other) {
        OnHit(other);
        });
}

void Bullet::OnHit(AABBColliderComponent* other)
{
    // Don't hit the shooter
    if (other->GetOwner() == mShooter) return;

    // Check what we hit
    FirstPersonActor* player = dynamic_cast<FirstPersonActor*>(other->GetOwner());
    Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

    if (player && mShooter != player)
    {
        player->TakeDamage(10);
        Deactivate();
    }
    else if (enemy && mShooter != enemy)
    {
        enemy->TakeDamage(25);
        Deactivate();
    }
    else if (!other->IsTrigger())
    {
        // Hit any other solid object (walls, obstacles, etc.) - deactivate bullet
        Deactivate();
    }
    // If it's another trigger (like another bullet), ignore it and keep going
}

void Bullet::Deactivate()
{
    mIsActive = false;
    SetActive(false);
    mCollider->SetActive(false);

    // Move far away
    SetPosition(Vector3(10000, 10000, 10000));
}
