#pragma once
#include "Actor.h"
#include "Vector3.h"

class MeshComponent;
class AABBColliderComponent;

class Bullet : public Actor
{
public:
    Bullet();
    ~Bullet() override = default;

    void UpdateActor() override;

    // Initialize bullet with starting position, direction, and shooter
    void Initialize(const Vector3& startPos, const Vector3& direction, Actor* shooter, float speed = 500.0f);

    // Reset bullet for reuse in pool
    void Reset();

    // Check if bullet is active
    bool IsActive() const { return mIsActive; }

    // Get the shooter
    Actor* GetShooter() const { return mShooter; }

private:
    // Components
    MeshComponent* mMeshComponent;
    AABBColliderComponent* mCollider;

    // Bullet properties
    Vector3 mDirection;
    float mSpeed;
    float mLifetime;
    float mMaxLifetime;
    bool mIsActive;
    Actor* mShooter;

    void SetupCollision();
    void OnHit(AABBColliderComponent* other);
    void Deactivate();
};

