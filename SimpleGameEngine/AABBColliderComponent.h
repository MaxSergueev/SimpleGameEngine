#pragma once
#include "Component.h"
#include "Vector3.h"
#include <functional>
#include <vector>

class AABBColliderComponent : public Component
{
private:
    Vector3 mMin;
    Vector3 mMax;
    Vector3 mOffset;
    Vector3 mDimensions;
    bool mIsTrigger;
    bool mIsActive;

    // Callback for collision events
    std::function<void(AABBColliderComponent*)> mOnCollisionEnter;
    std::function<void(AABBColliderComponent*)> mOnCollisionStay;
    std::function<void(AABBColliderComponent*)> mOnCollisionExit;

    std::vector<AABBColliderComponent*> mCurrentCollisions;

public:
    AABBColliderComponent(class Actor* pOwner);
    virtual ~AABBColliderComponent();

    void UpdateWorldBounds();

    void SetDimensions(const Vector3& dimensions);

    void SetOffset(const Vector3& offset);

    void SetTrigger(bool isTrigger) { mIsTrigger = isTrigger; }

    void SetActive(bool isActive) { mIsActive = isActive; }

    const Vector3& GetMin() const { return mMin; }
    const Vector3& GetMax() const { return mMax; }

    bool Intersects(const AABBColliderComponent* other) const;

    // Set collision callbacks
    void SetOnCollisionEnter(std::function<void(AABBColliderComponent*)> callback) { mOnCollisionEnter = callback; }
    void SetOnCollisionStay(std::function<void(AABBColliderComponent*)> callback) { mOnCollisionStay = callback; }
    void SetOnCollisionExit(std::function<void(AABBColliderComponent*)> callback) { mOnCollisionExit = callback; }

    // Handle collision events
    void OnCollisionEnter(AABBColliderComponent* other);
    void OnCollisionStay(AABBColliderComponent* other);
    void OnCollisionExit(AABBColliderComponent* other);

    // Override Component update
    void Update() override;

    bool IsCollidingWith(AABBColliderComponent* other) const;
    const std::vector<AABBColliderComponent*>& GetCurrentCollisions() const { return mCurrentCollisions; }

    bool IsTrigger() const { return mIsTrigger; }
    bool IsActive() const { return mIsActive; }

    class Actor* GetOwner() const { return mOwner; }
};
