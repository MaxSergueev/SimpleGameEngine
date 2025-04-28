#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "AABBColliderComponent.h"

class Pin : public Actor
{
private:
    MeshComponent* mMeshComponent;
    MoveComponent* mMoveComponent;
    AABBColliderComponent* mColliderComponent;

public:
    Pin(Scene* scene, const Vector3& position = Vector3(0, 0, 0));
    ~Pin() override = default;

    // Getters for components if needed
    MeshComponent* GetMeshComponent() const { return mMeshComponent; }
    MoveComponent* GetMoveComponent() const { return mMoveComponent; }
    AABBColliderComponent* GetColliderComponent() const { return mColliderComponent; }

    // Custom methods if needed
    void SetupCollisionCallbacks();
};


