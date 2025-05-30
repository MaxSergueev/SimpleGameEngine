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
    // Add to scene
    scene->AddActor(this);

    // Set initial position
    SetPosition(position);
    SetScale(Vector3(10.0f, 10.0f, 10.0f));

    // Create mesh component
    mMeshComponent = new MeshComponent(this);
    mMeshComponent->SetMesh(Assets::GetMesh("sphere"));
    mMeshComponent->GetMesh()->SetTexture(&Assets::GetTexture("purple"));

    // Create health component
    mHealthComponent = new HealthComponent(this, 100);
    mHealthComponent->SetOnDeathCallback([this]() {
        HandleDeath();
        });

    // Setup collision
    SetupCollision();

}

void Enemy::UpdateActor()
{
    // Only update if active
    if (GetState() != ActorState::Active) return;

    // Simple patrol behavior based on distance traveled
    Vector3 currentPos = GetTransform().GetPosition();
    Vector3 movement = mPatrolDirection * mMovementSpeed * Time::deltaTime;

    // Move the enemy
    SetPosition(currentPos + movement);

    // Increment patrol counter by distance moved this frame
    mPatrolCounter += movement.Length();

    // Check if we've moved far enough to turn around
    if (mPatrolCounter >= mPatrolDistance) {
        // Reset counter and reverse direction
        mPatrolCounter = 0;
        mPatrolDirection = -1 * mPatrolDirection;
    }

    // Update shooting behavior
    UpdateShooting();
}

void Enemy::UpdateShooting()
{
    if (!mBulletPool) {
        return; // Can't shoot without bullet pool
    }

    // Update shoot timer
    mShootTimer += Time::deltaTime;

    // Debug logging

    // Check timer condition
    bool timerReady = mShootTimer >= mShootCooldown;

    // Check if we can see player
    bool canSeePlayer = CanShootAtPlayer();

    // Check if we can shoot
    if (timerReady && canSeePlayer)
    {
        ShootAtPlayer();
        mShootTimer = 0.0f; // Reset timer
    }
    else
    {

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

    // Check if player is within range
    float distance = (playerPos - enemyPos).Length();

    if (distance > mShootRange) {
        return false;
    }

    // Get player's collider
    AABBColliderComponent* playerCollider = player->GetComponentOfType<AABBColliderComponent>();
    if (!playerCollider) {
        return false;
    }

    // Check line of sight to target (player)
    bool hasLineOfSight = LineTrace::HasLineOfSightToTarget(&GetScene(), enemyPos, playerPos, mCollider, playerCollider);

    if (!hasLineOfSight) {
        // Debug: Let's see what's actually blocking us
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

    // Calculate direction to player
    Vector3 shootDirection = Vector3::Normalize(playerPos - enemyPos);

    // Add some randomness for 1/3 chance to missfire
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 3);

    if (dis(gen) == 1) // 1/3 chance to missfire
    { 
        return;
    }

    // Fire bullet
    if (mBulletPool->FireBullet(enemyPos, shootDirection, this, 400.0f))
    {
    }
}

FirstPersonActor* Enemy::FindPlayer()
{
    // Search through all actors in the scene to find the player
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
    // Create collision component
    mCollider = new AABBColliderComponent(this);
    mCollider->SetDimensions(Vector3(20.0f, 20.0f, 20.0f));

    mCollider->SetOnCollisionEnter([this](AABBColliderComponent* other) {
        // Check if we collided with player using dynamic_cast
        FirstPersonActor* player = dynamic_cast<FirstPersonActor*>(other->GetOwner());
        if (player) {
            // You could implement damage to player here
        }
        });
}

void Enemy::HandleDeath()
{

    // Instead of deleting, just deactivate and move far away
    SetActive(false);
    SetPosition(Vector3(10000, 10000, 10000));

    // Disable collision
    if (mCollider) {
        mCollider->SetActive(false);
    }
}



