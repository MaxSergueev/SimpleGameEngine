#pragma once
#include "Component.h"
#include "Vector3.h"

class AABBColliderComponent;

class RigidBodyComponent : public Component
{
public:
    RigidBodyComponent(class Actor* owner);
    ~RigidBodyComponent() override = default;

    void Update() override;

    // Physics properties
    void SetVelocity(const Vector3& velocity) { mVelocity = velocity; }
    Vector3 GetVelocity() const { return mVelocity; }

    void SetMass(float mass) { mMass = mass; }
    float GetMass() const { return mMass; }

    void SetGravity(bool useGravity) { mUseGravity = useGravity; }
    bool UsesGravity() const { return mUseGravity; }

    void AddForce(const Vector3& force);

    // Collision response
    void ResolveCollision(AABBColliderComponent* other);

private:
    Vector3 mVelocity;
    Vector3 mAcceleration;
    float mMass;
    bool mUseGravity;
    AABBColliderComponent* mCollider;

    // Collision resolution
    Vector3 CalculatePenetration(AABBColliderComponent* other);
    Vector3 CalculateCollisionNormal(AABBColliderComponent* other);
};

