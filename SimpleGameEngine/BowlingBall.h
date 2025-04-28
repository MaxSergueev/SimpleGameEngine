#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "AABBColliderComponent.h"

class BowlingBall : public Actor
{
private:
    MeshComponent* mMeshComponent;
    MoveComponent* mMoveComponent;
    AABBColliderComponent* mColliderComponent;
    float mSpeed;

public:
    BowlingBall(Scene* scene, const Vector3& position = Vector3(0, 5, 0));
    ~BowlingBall() override = default;

    // Getters for components
    MeshComponent* GetMeshComponent() const { return mMeshComponent; }
    MoveComponent* GetMoveComponent() const { return mMoveComponent; }
    AABBColliderComponent* GetColliderComponent() const { return mColliderComponent; }

    // Ball-specific methods
    void Roll(const Vector2& direction);
    void Stop();
    void SetSpeed(float speed) { mSpeed = speed; }
    float GetSpeed() const { return mSpeed; }
};


