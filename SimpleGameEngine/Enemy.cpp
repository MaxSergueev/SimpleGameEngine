#include "Enemy.h"
#include "Scene.h"
#include "MeshComponent.h"
#include "AABBColliderComponent.h"
#include "HealthComponent.h"
#include "Assets.h"
#include "Log.h"
#include "FirstPersonActor.h"
#include "Time.h"

Enemy::Enemy(Scene* scene, const Vector3& position)
    : Actor(),
    mMeshComponent(nullptr),
    mCollider(nullptr),
    mHealthComponent(nullptr),
    mMovementSpeed(30.0f),
    mPatrolDirection(Vector3(1.0f, 0.0f, 0.0f)),
    mPatrolCounter(0),
    mPatrolDistance(200.0f)
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

    Log::Info("Enemy created at position: " +
        std::to_string(position.x) + ", " +
        std::to_string(position.y) + ", " +
        std::to_string(position.z));
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

        // Log direction change
        Log::Info("Enemy changed patrol direction");
    }
}

bool Enemy::TakeDamage(int amount)
{
    return mHealthComponent->TakeDamage(amount);
}

void Enemy::SetupCollision()
{
    // Create collision component
    mCollider = new AABBColliderComponent(this);
    mCollider->SetDimensions(Vector3(10, 10, 10));

    mCollider->SetOnCollisionEnter([this](AABBColliderComponent* other) {
		// Check collision with player
        FirstPersonActor* player = dynamic_cast<FirstPersonActor*>(other->GetOwner());
        if (player) {
            Log::Info("Enemy collided with player!");
            // dmg player here
        }
        });
}

void Enemy::HandleDeath()
{
    Log::Info("Enemy died!");

    // Just hide the enemy instead of deleting it
    SetActive(false);
    SetPosition(Vector3(10000, 10000, 10000)); // Move far away

    // Disable collision
    if (mCollider) {
        mCollider->SetActive(false);
    }

    //// Remove from scene first
    //GetScene().RemoveActor(this);

    //// Then delete self
    //delete this;
}


