#include "AABBColliderComponent.h"
#include "Actor.h"
#include "Scene.h"
#include <algorithm>

AABBColliderComponent::AABBColliderComponent(Actor* pOwner)
    : Component(pOwner)
    , mMin(Vector3::infinity)
    , mMax(Vector3::negInfinity)
    , mOffset(Vector3::zero)
    , mDimensions(Vector3(1.0f, 1.0f, 1.0f))
    , mIsTrigger(false)
    , mIsActive(true)
{
    // Register with collision system
    Scene::ActiveScene->AddCollider(this);
}

AABBColliderComponent::~AABBColliderComponent()
{
    // Unregister from collision system
    Scene::ActiveScene->RemoveCollider(this);
}

void AABBColliderComponent::UpdateWorldBounds()
{
    // Get the actor's world transform
    mOwner->GetTransform().ComputeWorldTransform();
    Matrix4Row worldTransform = mOwner->GetWorldTransform();

    // Calculate center position with offset
    Vector3 center = mOwner->GetTransform().GetPosition() + mOffset;

    // Calculate half extents
    Vector3 halfExtents = mDimensions * 0.5f;

    // Calculate world space min and max
    mMin = center - halfExtents;
    mMax = center + halfExtents;
}

void AABBColliderComponent::SetDimensions(const Vector3& dimensions)
{
    mDimensions = dimensions;
    UpdateWorldBounds();
}

void AABBColliderComponent::SetOffset(const Vector3& offset)
{
    mOffset = offset;
    UpdateWorldBounds();
}

bool AABBColliderComponent::Intersects(const AABBColliderComponent* other) const
{
    // AABB intersection test
    return (mMin.x <= other->mMax.x && mMax.x >= other->mMin.x) &&
        (mMin.y <= other->mMax.y && mMax.y >= other->mMin.y) &&
        (mMin.z <= other->mMax.z && mMax.z >= other->mMin.z);
}

void AABBColliderComponent::OnCollisionEnter(AABBColliderComponent* other)
{
    // Add to current collisions
    mCurrentCollisions.push_back(other);

    // Call callback if set
    if (mOnCollisionEnter)
    {
        mOnCollisionEnter(other);
    }
}

void AABBColliderComponent::OnCollisionStay(AABBColliderComponent* other)
{
    if (mOnCollisionStay)
    {
        mOnCollisionStay(other);
    }
}

void AABBColliderComponent::OnCollisionExit(AABBColliderComponent* other)
{
    // Remove from current collisions
    auto it = std::find(mCurrentCollisions.begin(), mCurrentCollisions.end(), other);
    if (it != mCurrentCollisions.end())
    {
        mCurrentCollisions.erase(it);
    }

    // Call callback if set
    if (mOnCollisionExit)
    {
        mOnCollisionExit(other);
    }
}

void AABBColliderComponent::Update()
{
    if (mIsActive)
    {
        UpdateWorldBounds();
    }
}

bool AABBColliderComponent::IsCollidingWith(AABBColliderComponent* other) const
{
    return std::find(mCurrentCollisions.begin(), mCurrentCollisions.end(), other) != mCurrentCollisions.end();
}

