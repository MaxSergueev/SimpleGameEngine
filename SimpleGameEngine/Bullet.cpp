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
    mMeshComponent = new MeshComponent(this);
    mMeshComponent->SetMesh(Assets::GetMesh("bullet"));
    mMeshComponent->GetMesh()->SetTexture(&Assets::GetTexture("yellow"));

    SetScale(Vector3(1.0f, 1.0f, 1.0f));

    SetupCollision();

    SetActive(false);
}

void Bullet::UpdateActor()
{
    if (!mIsActive) return;

    Vector3 currentPos = GetTransform().GetPosition();
    Vector3 movement = mDirection * mSpeed * Time::deltaTime;
    SetPosition(currentPos + movement);

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

    SetPosition(Vector3(10000, 10000, 10000));
}

void Bullet::SetupCollision()
{
    mCollider = new AABBColliderComponent(this);
    mCollider->SetDimensions(Vector3(2.0f, 2.0f, 2.0f));

    mCollider->SetTrigger(true);

    mCollider->SetOnCollisionEnter([this](AABBColliderComponent* other) {
        OnHit(other);
        });
}

void Bullet::OnHit(AABBColliderComponent* other)
{
    if (other->GetOwner() == mShooter) return;

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
        Deactivate();
    }
}

void Bullet::Deactivate()
{
    mIsActive = false;
    SetActive(false);
    mCollider->SetActive(false);

    SetPosition(Vector3(10000, 10000, 10000));
}