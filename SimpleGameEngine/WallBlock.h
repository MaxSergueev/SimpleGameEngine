#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "AABBColliderComponent.h"

class WallBlock : public Actor
{
private:
    MeshComponent* mMeshComponent;
    AABBColliderComponent* mColliderComponent;

public:
    WallBlock(Scene* scene, const Vector3& position = Vector3(0, 0, 0));
    ~WallBlock() override = default;

    // Getters for components
    MeshComponent* GetMeshComponent() const { return mMeshComponent; }
    AABBColliderComponent* GetColliderComponent() const { return mColliderComponent; }

    // Custom methods
    void SetupCollisionCallbacks();
};

