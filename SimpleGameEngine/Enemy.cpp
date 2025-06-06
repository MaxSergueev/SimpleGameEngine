#include "Enemy.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "AABBColliderComponent.h"
#include "HealthComponent.h"
#include "Assets.h"
#include "Log.h"
#include "FirstPersonActor.h"
#include "Time.h"
#include "BulletPool.h"
#include "LineTrace.h"
#include <random>

Enemy::Enemy(Scene* scene, const Vector3& position, BulletPool* bulletPool)
    : Actor(),
    mMeshComponent(nullptr),
    mCollider(nullptr),
    mHealthComponent(nullptr),
    mMovementSpeed(30.0f),
    mPatrolDirection(Vector3(1.0f, 0.0f, 0.0f)),
    mPatrolCounter(0),
    mPatrolDistance(100.0f),
    mBulletPool(bulletPool),
    mShootTimer(0.0f),
    mShootCooldown(2.0f),
    mShootRange(1000.0f)
{
    scene->AddActor(this);

    SetPosition(position);
    SetScale(Vector3(10.0f, 10.0f, 10.0f));

    mMeshComponent = new MeshComponent(this);
    mMeshComponent->SetMesh(Assets::GetMesh("sphere"));
    mMeshComponent->GetMesh()->SetTexture(&Assets::GetTexture("purple"));

    mHealthComponent = new HealthComponent(this, 100);
    mHealthComponent->SetOnDeathCallback([this]() {
        HandleDeath();
        });

    SetupCollision();
}

void Enemy::UpdateActor()
{
    if (GetState() != ActorState::Active) return;

    Vector3 currentPos = GetTransform().GetPosition();
    Vector3 movement = mPatrolDirection * mMovementSpeed * Time::deltaTime;

    SetPosition(currentPos + movement);

    mPatrolCounter += movement.Length();

    if (mPatrolCounter >= mPatrolDistance) {
        mPatrolCounter = 0;
        mPatrolDirection = -1 * mPatrolDirection;
    }

    UpdateShooting();
}

void Enemy::UpdateShooting()
{
    if (!mBulletPool) {
        return;
    }

    mShootTimer += Time::deltaTime;

    bool timerReady = mShootTimer >= mShootCooldown;
    bool canSeePlayer = CanShootAtPlayer();

    if (timerReady && canSeePlayer)
    {
        ShootAtPlayer();
        mShootTimer = 0.0f;
    }
}

bool Enemy::CanShootAtPlayer()
{
    FirstPersonActor* player = FindPlayer();
    if (!player) {
        return false;
    }

    Vector3 enemyPos = GetTransform().GetPosition();
    Vector3 playerPos = player->GetTransform().GetPosition();

    float distance = (playerPos - enemyPos).Length();

    if (distance > mShootRange) {
        return false;
    }

    AABBColliderComponent* playerCollider = player->GetComponentOfType<AABBColliderComponent>();
    if (!playerCollider) {
        return false;
    }

    bool hasLineOfSight = LineTrace::HasLineOfSightToTarget(&GetScene(), enemyPos, playerPos, mCollider, playerCollider);

    if (!hasLineOfSight) {
        LineTraceHit hit = LineTrace::TraceLineAgainstColliders(&GetScene(), enemyPos, playerPos, mCollider);
        if (hit.bHit) {
            Actor* blockingActor = hit.hitCollider->GetOwner();
            if (dynamic_cast<Enemy*>(blockingActor)) {
            }
            else {
            }
        }
    }

    return hasLineOfSight;
}

void Enemy::ShootAtPlayer()
{
    FirstPersonActor* player = FindPlayer();
    if (!player)
    {
        return;
    }

    Vector3 enemyPos = GetTransform().GetPosition();
    Vector3 playerPos = player->GetTransform().GetPosition();

    Vector3 shootDirection = Vector3::Normalize(playerPos - enemyPos);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 3);

    if (dis(gen) == 1)
    {
        return;
    }

    if (mBulletPool->FireBullet(enemyPos, shootDirection, this, 400.0f))
    {
    }
}

FirstPersonActor* Enemy::FindPlayer()
{
    const auto& actors = GetScene().GetActors();
    for (Actor* actor : actors)
    {
        FirstPersonActor* player = dynamic_cast<FirstPersonActor*>(actor);
        if (player && player->GetState() == ActorState::Active)
        {
            return player;
        }
    }
    return nullptr;
}

bool Enemy::TakeDamage(int amount)
{
    return mHealthComponent->TakeDamage(amount);
}

void Enemy::SetupCollision()
{
    mCollider = new AABBColliderComponent(this);
    mCollider->SetDimensions(Vector3(20.0f, 20.0f, 20.0f));

    mCollider->SetOnCollisionEnter([this](AABBColliderComponent* other) {
        FirstPersonActor* player = dynamic_cast<FirstPersonActor*>(other->GetOwner());
        if (player) {
        }
        });
}

void Enemy::HandleDeath()
{
    SetActive(false);
    SetPosition(Vector3(10000, 10000, 10000));

    if (mCollider) {
        mCollider->SetActive(false);
    }
}
