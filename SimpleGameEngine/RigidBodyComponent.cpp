#include "RigidBodyComponent.h"
#include "Actor.h"
#include "AABBColliderComponent.h"

RigidBodyComponent::RigidBodyComponent(Actor* owner)
    : Component(owner), mVelocity(Vector3::zero), mAcceleration(Vector3::zero),
    mMass(1.0f), mUseGravity(false), mCollider(nullptr)
{
    mCollider = owner->GetComponentOfType<AABBColliderComponent>();

    if (!mCollider) {
        mCollider = new AABBColliderComponent(owner);
        mCollider->SetDimensions(Vector3(45.0f, 45.0f, 45.0f));
    }
}

void RigidBodyComponent::Update()
{
    if (mUseGravity) {
        mAcceleration.y = -9.8f;
    }

    mVelocity += mAcceleration * 0.016f;

    Vector3 newPosition = mOwner->GetTransform().GetPosition() + mVelocity * 0.016f;
    mOwner->SetPosition(newPosition);

    mAcceleration = Vector3::zero;
}

void RigidBodyComponent::AddForce(const Vector3& force)
{
    mAcceleration += force * (1.0f / mMass);
}

void RigidBodyComponent::ResolveCollision(AABBColliderComponent* other)
{
    Vector3 penetration = CalculatePenetration(other);

    if (penetration.LengthSq() < 0.0001f) {
        return;
    }

    Vector3 normal = CalculateCollisionNormal(other);

    Vector3 position = mOwner->GetTransform().GetPosition();
    position += penetration;
    mOwner->SetPosition(position);

    float velocityAlongNormal = Vector3::Dot(mVelocity, normal);

    if (velocityAlongNormal < 0) {
        Vector3 reflectionComponent = normal * (velocityAlongNormal * 2.0f);
        mVelocity = mVelocity - reflectionComponent;

        float friction = 0.8f;
        mVelocity = mVelocity * friction;
    }
}

Vector3 RigidBodyComponent::CalculatePenetration(AABBColliderComponent* other)
{
    Vector3 myMin = mCollider->GetMin();
    Vector3 myMax = mCollider->GetMax();
    Vector3 otherMin = other->GetMin();
    Vector3 otherMax = other->GetMax();

    float overlapX = std::min(myMax.x - otherMin.x, otherMax.x - myMin.x);
    float overlapY = std::min(myMax.y - otherMin.y, otherMax.y - myMin.y);
    float overlapZ = std::min(myMax.z - otherMin.z, otherMax.z - myMin.z);

    Vector3 penetration = Vector3::zero;

    if (overlapX < overlapY && overlapX < overlapZ) {
        penetration.x = (myMin.x + myMax.x > otherMin.x + otherMax.x) ? overlapX : -overlapX;
    }
    else if (overlapY < overlapX && overlapY < overlapZ) {
        penetration.y = (myMin.y + myMax.y > otherMin.y + otherMax.y) ? overlapY : -overlapY;
    }
    else {
        penetration.z = (myMin.z + myMax.z > otherMin.z + otherMax.z) ? overlapZ : -overlapZ;
    }

    return penetration;
}

Vector3 RigidBodyComponent::CalculateCollisionNormal(AABBColliderComponent* other)
{
    Vector3 myCenter = (mCollider->GetMin() + mCollider->GetMax()) * 0.5f;
    Vector3 otherCenter = (other->GetMin() + other->GetMax()) * 0.5f;

    Vector3 direction = myCenter - otherCenter;

    if (direction.LengthSq() > 0.0001f) {
        direction.Normalize();
    }
    else {
        direction = Vector3(0, 1, 0);
    }

    return direction;
}
