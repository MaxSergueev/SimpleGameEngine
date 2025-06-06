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
    Scene::ActiveScene->AddCollider(this);
}

AABBColliderComponent::~AABBColliderComponent()
{
    Scene::ActiveScene->RemoveCollider(this);
}

void AABBColliderComponent::UpdateWorldBounds()
{
    mOwner->GetTransform().ComputeWorldTransform();
    Matrix4Row worldTransform = mOwner->GetWorldTransform();

    Vector3 center = mOwner->GetTransform().GetPosition() + mOffset;
    Vector3 halfExtents = mDimensions * 0.5f;

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
    return (mMin.x <= other->mMax.x && mMax.x >= other->mMin.x) &&
        (mMin.y <= other->mMax.y && mMax.y >= other->mMin.y) &&
        (mMin.z <= other->mMax.z && mMax.z >= other->mMin.z);
}

void AABBColliderComponent::OnCollisionEnter(AABBColliderComponent* other)
{
    mCurrentCollisions.push_back(other);

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
    auto it = std::find(mCurrentCollisions.begin(), mCurrentCollisions.end(), other);
    if (it != mCurrentCollisions.end())
    {
        mCurrentCollisions.erase(it);
    }

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


