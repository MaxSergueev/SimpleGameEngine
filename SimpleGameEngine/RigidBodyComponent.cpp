#include "RigidBodyComponent.h"
#include "Actor.h"
#include "AABBColliderComponent.h"

RigidBodyComponent::RigidBodyComponent(Actor* owner)
    : Component(owner), mVelocity(Vector3::zero), mAcceleration(Vector3::zero),
    mMass(1.0f), mUseGravity(false), mCollider(nullptr)
{
    // Find the collider component on the owner
    mCollider = owner->GetComponentOfType<AABBColliderComponent>();

    // If no collider exists, create one
    if (!mCollider) {
        mCollider = new AABBColliderComponent(owner);
        mCollider->SetDimensions(Vector3(45.0f, 45.0f, 45.0f));
    }
}

void RigidBodyComponent::Update()
{
    // Apply gravity if enabled
    if (mUseGravity) {
        mAcceleration.y = -9.8f;
    }

    // Update velocity based on acceleration
    mVelocity += mAcceleration * 0.016f;

    // Apply velocity to position
    Vector3 newPosition = mOwner->GetTransform().GetPosition() + mVelocity * 0.016f;
    mOwner->SetPosition(newPosition);

    // Reset acceleration
    mAcceleration = Vector3::zero;
}

void RigidBodyComponent::AddForce(const Vector3& force)
{
    // a = F/m
    mAcceleration += force * (1.0f/mMass) ;
}

void RigidBodyComponent::ResolveCollision(AABBColliderComponent* other)
{
    // Calculate penetration vector
    Vector3 penetration = CalculatePenetration(other);

    // If there's no penetration, return
    if (penetration.LengthSq() < 0.0001f) {
        return;
    }

    // Calculate collision normal
    Vector3 normal = CalculateCollisionNormal(other);

    // Resolve position - move out of collision
    Vector3 position = mOwner->GetTransform().GetPosition();
    position += penetration;
    mOwner->SetPosition(position);

    // Reflect velocity along the normal
    float velocityAlongNormal = Vector3::Dot(mVelocity, normal);

    // Only reflect if moving toward the surface
    if (velocityAlongNormal < 0) {
        // Reflection formula: v' = v - 2(v·n)n
        Vector3 reflectionComponent = normal * (velocityAlongNormal * 2.0f);
        mVelocity = mVelocity - reflectionComponent;

        // Add some friction along the surface
        float friction = 0.8f; // 0.8 = 20% friction
        mVelocity = mVelocity * friction;
    }
}

Vector3 RigidBodyComponent::CalculatePenetration(AABBColliderComponent* other)
{
    // Get the bounds of both colliders
    Vector3 myMin = mCollider->GetMin();
    Vector3 myMax = mCollider->GetMax();
    Vector3 otherMin = other->GetMin();
    Vector3 otherMax = other->GetMax();

    // Calculate overlap in each axis
    float overlapX = std::min(myMax.x - otherMin.x, otherMax.x - myMin.x);
    float overlapY = std::min(myMax.y - otherMin.y, otherMax.y - myMin.y);
    float overlapZ = std::min(myMax.z - otherMin.z, otherMax.z - myMin.z);

    // Find the minimum overlap axis
    Vector3 penetration = Vector3::zero;

    if (overlapX < overlapY && overlapX < overlapZ) {
        // X-axis has minimum overlap
        penetration.x = (myMin.x + myMax.x > otherMin.x + otherMax.x) ? overlapX : -overlapX;
    }
    else if (overlapY < overlapX && overlapY < overlapZ) {
        // Y-axis has minimum overlap
        penetration.y = (myMin.y + myMax.y > otherMin.y + otherMax.y) ? overlapY : -overlapY;
    }
    else {
        // Z-axis has minimum overlap
        penetration.z = (myMin.z + myMax.z > otherMin.z + otherMax.z) ? overlapZ : -overlapZ;
    }

    return penetration;
}

Vector3 RigidBodyComponent::CalculateCollisionNormal(AABBColliderComponent* other)
{
    // Get centers of both colliders
    Vector3 myCenter = (mCollider->GetMin() + mCollider->GetMax()) * 0.5f;
    Vector3 otherCenter = (other->GetMin() + other->GetMax()) * 0.5f;

    // Direction from other to me
    Vector3 direction = myCenter - otherCenter;

    // Normalize to get the collision normal
    if (direction.LengthSq() > 0.0001f) {
        direction.Normalize();
    }
    else {
        // Default normal if centers are too close
        direction = Vector3(0, 1, 0);
    }

    return direction;
}

