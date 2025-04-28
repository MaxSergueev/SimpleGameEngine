#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "AABBColliderComponent.h"
#include "PinPhysicsComponent.h"

class Pin : public Actor
{
private:
    MeshComponent* mMeshComponent;
    MoveComponent* mMoveComponent;
    AABBColliderComponent* mColliderComponent;
    PinPhysicsComponent* mPhysicsComponent;
    bool mIsKnocked;
    float mMass;

public:
    Pin(Scene* scene, const Vector3& position = Vector3(0, 0, 0));
    ~Pin() override = default;

    // Getters for components
    MeshComponent* GetMeshComponent() const { return mMeshComponent; }
    MoveComponent* GetMoveComponent() const { return mMoveComponent; }
    AABBColliderComponent* GetColliderComponent() const { return mColliderComponent; }
    PinPhysicsComponent* GetPhysicsComponent() const { return mPhysicsComponent; }

    // Custom methods
    void SetupCollisionCallbacks();
    void ApplyImpulse(const Vector2& direction, float force);
    bool IsKnocked() const { return mIsKnocked; }
    void SetKnocked(bool knocked) { mIsKnocked = knocked; }
    float GetMass() const { return mMass; }
};




